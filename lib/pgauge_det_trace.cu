#include <quda_internal.h>
#include <quda_matrix.h>
#include <tune_quda.h>
#include <gauge_field.h>
#include <gauge_field_order.h>
#include <launch_kernel.cuh>
#include <comm_quda.h>
#include <pgauge_monte.h> 
#include <atomic.cuh>
#include <cub_helper.cuh> 
#include <index_helper.cuh> 

namespace quda {

#ifdef GPU_GAUGE_ALG

template <typename Gauge>
struct KernelArg {
  int threads; // number of active threads required
  int X[4]; // grid dimensions
#ifdef MULTI_GPU
  int border[4]; 
#endif
  Gauge dataOr;
  double2 *value;
  double2 *value_h;
  KernelArg(const Gauge &dataOr, const cudaGaugeField &data)
    : dataOr(dataOr) {
#ifdef MULTI_GPU
    for(int dir=0; dir<4; ++dir){
      if(comm_dim_partitioned(dir)) border[dir] = data.R()[dir];
      else border[dir] = 0;
    }
    for(int dir=0; dir<4; ++dir) X[dir] = data.X()[dir] - border[dir]*2;
#else
    for(int dir=0; dir<4; ++dir) X[dir] = data.X()[dir];
#endif
    threads = X[0]*X[1]*X[2]*X[3];
    value = (double2*)device_malloc(sizeof(double2));
    value_h = (double2*)safe_malloc(sizeof(double2));
  }
  double2 getValue(){return value_h[0];}
};

template<class Cmplx>
 __device__ __host__ inline double2 CmplxToDouble2(const Cmplx b){
  return make_double2(b.x , b.y);
}




template<int blockSize, typename Float, typename Gauge, int NCOLORS, int functiontype>
__global__ void compute_Value(KernelArg<Gauge> arg){
  int idx = threadIdx.x + blockIdx.x*blockDim.x;

  typedef cub::BlockReduce<double2, blockSize> BlockReduce;
  __shared__ typename BlockReduce::TempStorage temp_storage;
  
  double2 val = make_double2(0.0, 0.0);
  if(idx < arg.threads) {
    typedef typename ComplexTypeId<Float>::Type Cmplx;
    int parity = 0;
    if(idx >= arg.threads/2) {
      parity = 1;
      idx -= arg.threads/2;
    }
    int X[4]; 
    #pragma unroll
    for(int dr=0; dr<4; ++dr) X[dr] = arg.X[dr];

    int x[4];
    getCoords(x, idx, X, parity);
  #ifdef MULTI_GPU
    #pragma unroll
    for(int dr=0; dr<4; ++dr) {
      x[dr] += arg.border[dr];
      X[dr] += 2*arg.border[dr];
    }
    idx = linkIndex(x,X);
  #endif
#pragma unroll
    for (int mu = 0; mu < 4; mu++) {
      Matrix<Cmplx,NCOLORS> U;
      arg.dataOr.load((Float*)(U.data), idx, mu, parity);
      if(functiontype == 0) val += CmplxToDouble2(getDeterminant(U));
      if(functiontype == 1) val += CmplxToDouble2(getTrace(U));
    }
  }
  double2 aggregate = BlockReduce(temp_storage).Reduce(val, Summ<double2>());
  if (threadIdx.x == 0) atomicAdd(arg.value, aggregate);
}



template<typename Float, typename Gauge, int NCOLORS, int functiontype>
class CalcFunc : Tunable {
  KernelArg<Gauge> arg;
  TuneParam tp;
  mutable char aux_string[128]; // used as a label in the autotuner
  private:
  unsigned int sharedBytesPerThread() const { return 0; }
  unsigned int sharedBytesPerBlock(const TuneParam &param) const { return 0; }
  //bool tuneSharedBytes() const { return false; } // Don't tune shared memory
  bool tuneGridDim() const { return false; } // Don't tune the grid dimensions.
  unsigned int minThreads() const { return arg.threads; }

  public:
  CalcFunc(KernelArg<Gauge> &arg) : arg(arg) {}
  ~CalcFunc () { 
    host_free(arg.value_h); device_free(arg.value);
  }

  void apply(const cudaStream_t &stream){
    tp = tuneLaunch(*this, getTuning(), getVerbosity());
    cudaMemset(arg.value, 0, sizeof(double2));
    LAUNCH_KERNEL(compute_Value, tp, stream, arg, Float, Gauge, NCOLORS, functiontype);
    cudaMemcpy(arg.value_h, arg.value, sizeof(double2), cudaMemcpyDeviceToHost);
    comm_allreduce_array((double*)arg.value_h, 2);
    const int nNodes = comm_size();
    arg.value_h[0].x  /= (double)(4*arg.threads*nNodes);
    arg.value_h[0].y  /= (double)(4*arg.threads*nNodes);
  }

  TuneKey tuneKey() const {
    std::stringstream vol;
    vol << arg.X[0] << "x";
    vol << arg.X[1] << "x";
    vol << arg.X[2] << "x";
    vol << arg.X[3];
    sprintf(aux_string,"threads=%d,prec=%d",arg.threads, sizeof(Float));
    return TuneKey(vol.str().c_str(), typeid(*this).name(), aux_string);
    
  }
  std::string paramString(const TuneParam &param) const {
    std::stringstream ps;
    ps << "block=(" << param.block.x << "," << param.block.y << "," << param.block.z << ")";
    ps << "shared=" << param.shared_bytes;
    return ps.str();
  }
  void preTune(){}
  void postTune(){}

  long long flops() const { 
    if(NCOLORS==3 && functiontype == 0) return 264LL*arg.threads+2LL*tp.block.x ; 
    if(NCOLORS==3 && functiontype == 1) return 24LL*arg.threads+2LL*tp.block.x ; 
    else return 0; 
  }// Only correct if there is no link reconstruction
  long long bytes() const { return 4LL*NCOLORS * NCOLORS * sizeof(Float)*2*arg.threads + tp.block.x * sizeof(double2); }

}; 





template<typename Float, int NCOLORS, int functiontype, typename Gauge>
double2 computeValue( Gauge dataOr,  cudaGaugeField& data) {
  TimeProfile profileGenericFunc("GenericFunc");
  if (getVerbosity() >= QUDA_SUMMARIZE) profileGenericFunc.TPSTART(QUDA_PROFILE_COMPUTE);
  KernelArg<Gauge> arg(dataOr, data);
  CalcFunc<Float, Gauge, NCOLORS, functiontype> func(arg);
  func.apply(0);
  if(getVerbosity() >= QUDA_SUMMARIZE && functiontype == 0) printfQuda("Determinant: %.16e, %.16e\n", arg.getValue().x, arg.getValue().y);
  if(getVerbosity() >= QUDA_SUMMARIZE && functiontype == 1) printfQuda("Trace: %.16e, %.16e\n", arg.getValue().x, arg.getValue().y);
  checkCudaError();
  cudaDeviceSynchronize();
  if (getVerbosity() >= QUDA_SUMMARIZE){
    profileGenericFunc.TPSTOP(QUDA_PROFILE_COMPUTE);
    double secs = profileGenericFunc.Last(QUDA_PROFILE_COMPUTE);
    double gflops = (func.flops()*1e-9)/(secs);
    double gbytes = func.bytes()/(secs*1e9);
    if(functiontype == 0){
      #ifdef MULTI_GPU
      printfQuda("Determinant: Time = %6.6f s, Gflop/s = %6.1f, GB/s = %6.1f\n", secs, gflops*comm_size(), gbytes*comm_size());
      #else
      printfQuda("Determinant: Time = %6.6f s, Gflop/s = %6.1f, GB/s = %6.1f\n", secs, gflops, gbytes);
      #endif
    }
    if(functiontype == 1){
      #ifdef MULTI_GPU
      printfQuda("Trace: Time = %6.6f s, Gflop/s = %6.1f, GB/s = %6.1f\n", secs, gflops*comm_size(), gbytes*comm_size());
      #else
      printfQuda("Trace: Time = %6.6f s, Gflop/s = %6.1f, GB/s = %6.1f\n", secs, gflops, gbytes);
      #endif
    }
  }
  return arg.getValue();
}



template<typename Float, int functiontype>
double2 computeValue(cudaGaugeField& data) {

  // Switching to FloatNOrder for the gauge field in order to support RECONSTRUCT_12
  // Need to fix this!!
  if(data.isNative()) {
    if(data.Reconstruct() == QUDA_RECONSTRUCT_NO) {
    //printfQuda("QUDA_RECONSTRUCT_NO\n");
      typedef typename gauge_mapper<Float,QUDA_RECONSTRUCT_NO>::type Gauge;
      return  computeValue<Float, 3, functiontype>(Gauge(data), data);
    } else if(data.Reconstruct() == QUDA_RECONSTRUCT_12){
    //printfQuda("QUDA_RECONSTRUCT_12\n");
      typedef typename gauge_mapper<Float,QUDA_RECONSTRUCT_12>::type Gauge;
      return computeValue<Float, 3, functiontype>(Gauge(data), data);
    } else if(data.Reconstruct() == QUDA_RECONSTRUCT_8){
    //printfQuda("QUDA_RECONSTRUCT_8\n");
      typedef typename gauge_mapper<Float,QUDA_RECONSTRUCT_8>::type Gauge;
      return computeValue<Float, 3, functiontype>(Gauge(data), data);    
    } else {
      errorQuda("Reconstruction type %d of gauge field not supported", data.Reconstruct());
    }
  } else {
    errorQuda("Invalid Gauge Order\n");
  }
}
#endif // GPU_GAUGE_ALG

/** @brief Calculate the Determinant
* 
* @param[in] data Gauge field
* @returns double2 complex Determinant value
*/
double2 getLinkDeterminant( cudaGaugeField& data) {
#ifdef GPU_GAUGE_ALG
  if(data.Precision() == QUDA_HALF_PRECISION) {
    errorQuda("Half precision not supported\n");
  }
  if (data.Precision() == QUDA_SINGLE_PRECISION) {
    return computeValue<float, 0> (data);
  } else if(data.Precision() == QUDA_DOUBLE_PRECISION) {
    return computeValue<double, 0>(data);
  } else {
    errorQuda("Precision %d not supported", data.Precision());
  }
#else
  errorQuda("Pure gauge code has not been built");
#endif // GPU_GAUGE_ALG
}

/** @brief Calculate the Trace
* 
* @param[in] data Gauge field
* @returns double2 complex trace value
*/
double2 getLinkTrace( cudaGaugeField& data) {
#ifdef GPU_GAUGE_ALG
  if(data.Precision() == QUDA_HALF_PRECISION) {
    errorQuda("Half precision not supported\n");
  }
  if (data.Precision() == QUDA_SINGLE_PRECISION) {
    return computeValue<float, 1> (data);
  } else if(data.Precision() == QUDA_DOUBLE_PRECISION) {
    return computeValue<double, 1>(data);
  } else {
    errorQuda("Precision %d not supported", data.Precision());
  }
#else
  errorQuda("Pure gauge code has not been built");
#endif // GPU_GAUGE_ALG
}


}
