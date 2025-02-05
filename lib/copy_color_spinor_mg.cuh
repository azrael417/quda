/*
  Spinor reordering and copying routines.  These are implemented to
  un on both CPU and GPU.  Here we are templating on the following:
  - input precision
  - output precision
  - number of colors
  - number of spins
  - field ordering
*/

#include <color_spinor_field.h>
#include <color_spinor_field_order.h>
#include <tune_quda.h>
#include <algorithm> // for std::swap

namespace quda {

  using namespace colorspinor;

  /** CPU function to reorder spinor fields.  */
  template <typename FloatOut, typename FloatIn, int Ns, int Nc, typename OutOrder, typename InOrder>
    void packSpinor(OutOrder &outOrder, const InOrder &inOrder, int volume) {
    for (int x=0; x<volume; x++) {
      for (int s=0; s<Ns; s++) {
	for (int c=0; c<Nc; c++) {
	  outOrder(0, x, s, c) = inOrder(0, x, s, c);
	}
      }
    }
  }

  /** CUDA kernel to reorder spinor fields.  Adopts a similar form as the CPU version, using the same inlined functions. */
  template <typename FloatOut, typename FloatIn, int Ns, int Nc, typename OutOrder, typename InOrder>
    __global__ void packSpinorKernel(OutOrder outOrder, const InOrder inOrder, int volume) {
    int x = blockIdx.x * blockDim.x + threadIdx.x;
    if (x >= volume) return;

    for (int s=0; s<Ns; s++) {
      for (int c=0; c<Nc; c++) {
	outOrder(0, x, s, c) = inOrder(0, x, s, c);
      }
    }
  }

  template <typename FloatOut, typename FloatIn, int Ns, int Nc, typename OutOrder, typename InOrder>
    class CopySpinor : Tunable {
    const InOrder &in;
    OutOrder &out;
    const ColorSpinorField &meta; // this reference is for meta data only
    QudaFieldLocation location;

  private:
    unsigned int sharedBytesPerThread() const { return 0; }

    unsigned int sharedBytesPerBlock(const TuneParam &param) const { return 0; }
    bool advanceSharedBytes(TuneParam &param) const { return false; } // Don't tune shared mem
    bool tuneGridDim() const { return false; } // Don't tune the grid dimensions.
    unsigned int minThreads() const { return meta.VolumeCB(); }

  public:
    CopySpinor(OutOrder &out, const InOrder &in, const ColorSpinorField &meta, QudaFieldLocation location)
      : out(out), in(in), meta(meta), location(location) { }
    virtual ~CopySpinor() { ; }

    void apply(const cudaStream_t &stream) {
      if (location == QUDA_CPU_FIELD_LOCATION) {
	packSpinor<FloatOut, FloatIn, Ns, Nc>(out, in, meta.VolumeCB());
      } else {
	TuneParam tp = tuneLaunch(*this, getTuning(), getVerbosity());
	packSpinorKernel<FloatOut, FloatIn, Ns, Nc, OutOrder, InOrder>
	  <<<tp.grid, tp.block, tp.shared_bytes, stream>>>
	  (out, in, meta.VolumeCB());
      }
    }

    TuneKey tuneKey() const { return TuneKey(meta.VolString(), typeid(*this).name(), meta.AuxString()); }

    std::string paramString(const TuneParam &param) const { // Don't bother printing the grid dim.
      std::stringstream ps;
      ps << "block=(" << param.block.x << "," << param.block.y << "," << param.block.z << "), ";
      ps << "shared=" << param.shared_bytes;
      return ps.str();
    }

    long long flops() const { return 0; }
    long long bytes() const { return in.Bytes() + out.Bytes(); }
  };


  template <typename FloatOut, typename FloatIn, int Ns, int Nc, typename OutOrder, typename InOrder>
    void genericCopyColorSpinor(OutOrder &outOrder, const InOrder &inOrder,
				const ColorSpinorField &out, QudaFieldLocation location) {
    CopySpinor<FloatOut, FloatIn, Ns, Nc, OutOrder, InOrder> copy(outOrder, inOrder, out, location);
    copy.apply(0);
  }

  /** Decide on the output order*/
  template <typename FloatOut, typename FloatIn, int Ns, int Nc, typename InOrder>
    void genericCopyColorSpinor(InOrder &inOrder, ColorSpinorField &out,
				QudaFieldLocation location, FloatOut *Out) {

    if (out.FieldOrder() == QUDA_FLOAT2_FIELD_ORDER) {
      typedef typename colorspinor::FieldOrderCB<FloatOut, Ns, Nc, 1, QUDA_FLOAT2_FIELD_ORDER> ColorSpinor;
      ColorSpinor outOrder(out, Out);
      genericCopyColorSpinor<FloatOut,FloatIn,Ns,Nc>(outOrder, inOrder, out, location);
    } else if (out.FieldOrder() == QUDA_SPACE_SPIN_COLOR_FIELD_ORDER) {
      typedef typename colorspinor::FieldOrderCB<FloatOut, Ns, Nc, 1, QUDA_SPACE_SPIN_COLOR_FIELD_ORDER> ColorSpinor;
      ColorSpinor outOrder(out, Out);
      genericCopyColorSpinor<FloatOut,FloatIn,Ns,Nc>(outOrder, inOrder, out, location);
    } else {
      errorQuda("Order %d not defined (Ns=%d, Nc=%d)", out.FieldOrder(), Ns, Nc);
    }

  }

  /** Decide on the input order*/
  template <typename FloatOut, typename FloatIn, int Ns, int Nc>
    void genericCopyColorSpinor(ColorSpinorField &out, const ColorSpinorField &in,
				QudaFieldLocation location, FloatOut *Out, FloatIn *In) {

    if (in.FieldOrder() == QUDA_FLOAT2_FIELD_ORDER) {
      typedef typename colorspinor::FieldOrderCB<FloatIn, Ns, Nc, 1, QUDA_FLOAT2_FIELD_ORDER> ColorSpinor;
      ColorSpinor inOrder(in, In);
      genericCopyColorSpinor<FloatOut,FloatIn,Ns,Nc>(inOrder, out, location, Out);
    } else if (in.FieldOrder() == QUDA_SPACE_SPIN_COLOR_FIELD_ORDER) {
      typedef typename colorspinor::FieldOrderCB<FloatIn, Ns, Nc, 1, QUDA_SPACE_SPIN_COLOR_FIELD_ORDER> ColorSpinor;
      ColorSpinor inOrder(in, In);
      genericCopyColorSpinor<FloatOut,FloatIn,Ns,Nc>(inOrder, out, location, Out);
    } else {
      errorQuda("Order %d not defined (Ns=%d, Nc=%d)", in.FieldOrder(), Ns, Nc);
    }

  }


  template <int Ns, int Nc, typename dstFloat, typename srcFloat>
    void copyGenericColorSpinor(ColorSpinorField &dst, const ColorSpinorField &src,
				QudaFieldLocation location, dstFloat *Dst, srcFloat *Src) {

    if (dst.Ndim() != src.Ndim())
      errorQuda("Number of dimensions %d %d don't match", dst.Ndim(), src.Ndim());

    if (dst.Volume() != src.Volume())
      errorQuda("Volumes %d %d don't match", dst.Volume(), src.Volume());

    if (!( dst.SiteOrder() == src.SiteOrder() ||
	   (dst.SiteOrder() == QUDA_EVEN_ODD_SITE_ORDER &&
	    src.SiteOrder() == QUDA_ODD_EVEN_SITE_ORDER) ||
	   (dst.SiteOrder() == QUDA_ODD_EVEN_SITE_ORDER &&
	    src.SiteOrder() == QUDA_EVEN_ODD_SITE_ORDER) ) ) {
      errorQuda("Subset orders %d %d don't match", dst.SiteOrder(), src.SiteOrder());
    }

    if (dst.SiteSubset() != src.SiteSubset())
      errorQuda("Subset types do not match %d %d", dst.SiteSubset(), src.SiteSubset());

    // We currently only support parity-ordered fields; even-odd or odd-even
    if (dst.SiteOrder() == QUDA_LEXICOGRAPHIC_SITE_ORDER) {
      errorQuda("Copying to full fields with lexicographical ordering is not currently supported");
    }

    if (dst.SiteSubset() == QUDA_FULL_SITE_SUBSET) { // full field
      if (src.FieldOrder() == QUDA_QDPJIT_FIELD_ORDER ||
	  dst.FieldOrder() == QUDA_QDPJIT_FIELD_ORDER) {
	errorQuda("QDPJIT field ordering not supported for full site fields");
      }

      // set for the source subset ordering
      srcFloat *srcEven = Src ? Src : (srcFloat*)src.V();
      srcFloat *srcOdd = (srcFloat*)((char*)srcEven + src.Bytes()/2);
      if (src.SiteOrder() == QUDA_ODD_EVEN_SITE_ORDER) {
	std::swap<srcFloat*>(srcEven, srcOdd);
      }

      // set for the destination subset ordering
      dstFloat *dstEven = Dst ? Dst : (dstFloat*)dst.V();
      dstFloat *dstOdd = (dstFloat*)((char*)dstEven + dst.Bytes()/2);
      if (dst.SiteOrder() == QUDA_ODD_EVEN_SITE_ORDER) {
	std::swap<dstFloat*>(dstEven, dstOdd);
      }

      genericCopyColorSpinor<dstFloat, srcFloat, Ns, Nc>(dst, src, location, dstEven, srcEven);
      genericCopyColorSpinor<dstFloat, srcFloat, Ns, Nc>(dst, src, location,  dstOdd,  srcOdd);
    } else { // parity field
      genericCopyColorSpinor<dstFloat, srcFloat, Ns, Nc>(dst, src, location, Dst, Src);
    }

  }

  template <int Nc, typename dstFloat, typename srcFloat>
  void CopyGenericColorSpinor(ColorSpinorField &dst, const ColorSpinorField &src,
			      QudaFieldLocation location, dstFloat *Dst, srcFloat *Src)
  {

    if (dst.Nspin() != src.Nspin())
      errorQuda("source and destination spins must match");

    if (dst.Nspin() == 4) {
#if defined(GPU_WILSON_DIRAC) || defined(GPU_DOMAIN_WALL_DIRAC)
      copyGenericColorSpinor<4,Nc>(dst, src, location, Dst, Src);
#else
      errorQuda("%s has not been built for Nspin=%d fields", __func__, src.Nspin());
#endif
    } else if (dst.Nspin() == 2) {
#if defined(GPU_WILSON_DIRAC) || defined(GPU_DOMAIN_WALL_DIRAC) || defined(GPU_STAGGERED_DIRAC)
      copyGenericColorSpinor<2,Nc>(dst, src, location, Dst, Src);
#else
      errorQuda("%s has not been built for Nspin=%d fields", __func__, src.Nspin());
#endif
    } else if (dst.Nspin() == 1) {
#ifdef GPU_STAGGERED_DIRAC
      copyGenericColorSpinor<1,Nc>(dst, src, location, Dst, Src);
#else
      errorQuda("%s has not been built for Nspin=%d fields", __func__, src.Nspin());
#endif
    } else {
      errorQuda("Nspin=%d unsupported", dst.Nspin());
    }

  }

#ifdef GPU_MULTIGRID
#define INSTANTIATE_COLOR						\
  switch(src.Ncolor()) {						\
  case 1:								\
    CopyGenericColorSpinor<1>(dst, src, location, dst_ptr, src_ptr);	\
    break;								\
  case 2:								\
    CopyGenericColorSpinor<2>(dst, src, location, dst_ptr, src_ptr);	\
    break;								\
  case 4:								\
    CopyGenericColorSpinor<4>(dst, src, location, dst_ptr, src_ptr);	\
    break;								\
  case 6:								\
    CopyGenericColorSpinor<6>(dst, src, location, dst_ptr, src_ptr);	\
    break;								\
  case 9:								\
    CopyGenericColorSpinor<9>(dst, src, location, dst_ptr, src_ptr);	\
    break;								\
  case 12:								\
    CopyGenericColorSpinor<12>(dst, src, location, dst_ptr, src_ptr);	\
    break;								\
  case 16:								\
    CopyGenericColorSpinor<16>(dst, src, location, dst_ptr, src_ptr);	\
    break;								\
  case 24:								\
    CopyGenericColorSpinor<24>(dst, src, location, dst_ptr, src_ptr);	\
    break;								\
  case 36:								\
    CopyGenericColorSpinor<36>(dst, src, location, dst_ptr, src_ptr);	\
    break;								\
  case 48:								\
    CopyGenericColorSpinor<48>(dst, src, location, dst_ptr, src_ptr);	\
    break;								\
  case 72:								\
    CopyGenericColorSpinor<72>(dst, src, location, dst_ptr, src_ptr);	\
    break;								\
  case 256:								\
    CopyGenericColorSpinor<256>(dst, src, location, dst_ptr, src_ptr);	\
    break;								\
  case 576:								\
    CopyGenericColorSpinor<576>(dst, src, location, dst_ptr, src_ptr);	\
    break;								\
  default:								\
    errorQuda("Ncolors=%d not supported", src.Ncolor());		\
  }
#else
#define INSTANTIATE_COLOR
#endif


} // namespace quda
