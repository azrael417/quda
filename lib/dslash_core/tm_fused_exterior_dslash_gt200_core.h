#ifdef MULTI_GPU

// *** CUDA DSLASH ***

#define DSLASH_SHARED_FLOATS_PER_THREAD 0


#if ((CUDA_VERSION >= 4010) && (__COMPUTE_CAPABILITY__ >= 200)) // NVVM compiler
#define VOLATILE
#else // Open64 compiler
#define VOLATILE volatile
#endif
// input spinor
#ifdef SPINOR_DOUBLE
#define spinorFloat double
#define i00_re I0.x
#define i00_im I0.y
#define i01_re I1.x
#define i01_im I1.y
#define i02_re I2.x
#define i02_im I2.y
#define i10_re I3.x
#define i10_im I3.y
#define i11_re I4.x
#define i11_im I4.y
#define i12_re I5.x
#define i12_im I5.y
#define i20_re I6.x
#define i20_im I6.y
#define i21_re I7.x
#define i21_im I7.y
#define i22_re I8.x
#define i22_im I8.y
#define i30_re I9.x
#define i30_im I9.y
#define i31_re I10.x
#define i31_im I10.y
#define i32_re I11.x
#define i32_im I11.y
#define acc00_re accum0.x
#define acc00_im accum0.y
#define acc01_re accum1.x
#define acc01_im accum1.y
#define acc02_re accum2.x
#define acc02_im accum2.y
#define acc10_re accum3.x
#define acc10_im accum3.y
#define acc11_re accum4.x
#define acc11_im accum4.y
#define acc12_re accum5.x
#define acc12_im accum5.y
#define acc20_re accum6.x
#define acc20_im accum6.y
#define acc21_re accum7.x
#define acc21_im accum7.y
#define acc22_re accum8.x
#define acc22_im accum8.y
#define acc30_re accum9.x
#define acc30_im accum9.y
#define acc31_re accum10.x
#define acc31_im accum10.y
#define acc32_re accum11.x
#define acc32_im accum11.y
#else
#define spinorFloat float
#define i00_re I0.x
#define i00_im I0.y
#define i01_re I0.z
#define i01_im I0.w
#define i02_re I1.x
#define i02_im I1.y
#define i10_re I1.z
#define i10_im I1.w
#define i11_re I2.x
#define i11_im I2.y
#define i12_re I2.z
#define i12_im I2.w
#define i20_re I3.x
#define i20_im I3.y
#define i21_re I3.z
#define i21_im I3.w
#define i22_re I4.x
#define i22_im I4.y
#define i30_re I4.z
#define i30_im I4.w
#define i31_re I5.x
#define i31_im I5.y
#define i32_re I5.z
#define i32_im I5.w
#define acc00_re accum0.x
#define acc00_im accum0.y
#define acc01_re accum0.z
#define acc01_im accum0.w
#define acc02_re accum1.x
#define acc02_im accum1.y
#define acc10_re accum1.z
#define acc10_im accum1.w
#define acc11_re accum2.x
#define acc11_im accum2.y
#define acc12_re accum2.z
#define acc12_im accum2.w
#define acc20_re accum3.x
#define acc20_im accum3.y
#define acc21_re accum3.z
#define acc21_im accum3.w
#define acc22_re accum4.x
#define acc22_im accum4.y
#define acc30_re accum4.z
#define acc30_im accum4.w
#define acc31_re accum5.x
#define acc31_im accum5.y
#define acc32_re accum5.z
#define acc32_im accum5.w
#endif // SPINOR_DOUBLE

// gauge link
#ifdef GAUGE_FLOAT2
#define g00_re G0.x
#define g00_im G0.y
#define g01_re G1.x
#define g01_im G1.y
#define g02_re G2.x
#define g02_im G2.y
#define g10_re G3.x
#define g10_im G3.y
#define g11_re G4.x
#define g11_im G4.y
#define g12_re G5.x
#define g12_im G5.y
#define g20_re G6.x
#define g20_im G6.y
#define g21_re G7.x
#define g21_im G7.y
#define g22_re G8.x
#define g22_im G8.y

#else
#define g00_re G0.x
#define g00_im G0.y
#define g01_re G0.z
#define g01_im G0.w
#define g02_re G1.x
#define g02_im G1.y
#define g10_re G1.z
#define g10_im G1.w
#define g11_re G2.x
#define g11_im G2.y
#define g12_re G2.z
#define g12_im G2.w
#define g20_re G3.x
#define g20_im G3.y
#define g21_re G3.z
#define g21_im G3.w
#define g22_re G4.x
#define g22_im G4.y

#endif // GAUGE_DOUBLE

// conjugated gauge link
#define gT00_re (+g00_re)
#define gT00_im (-g00_im)
#define gT01_re (+g10_re)
#define gT01_im (-g10_im)
#define gT02_re (+g20_re)
#define gT02_im (-g20_im)
#define gT10_re (+g01_re)
#define gT10_im (-g01_im)
#define gT11_re (+g11_re)
#define gT11_im (-g11_im)
#define gT12_re (+g21_re)
#define gT12_im (-g21_im)
#define gT20_re (+g02_re)
#define gT20_im (-g02_im)
#define gT21_re (+g12_re)
#define gT21_im (-g12_im)
#define gT22_re (+g22_re)
#define gT22_im (-g22_im)

// output spinor
VOLATILE spinorFloat o00_re;
VOLATILE spinorFloat o00_im;
VOLATILE spinorFloat o01_re;
VOLATILE spinorFloat o01_im;
VOLATILE spinorFloat o02_re;
VOLATILE spinorFloat o02_im;
VOLATILE spinorFloat o10_re;
VOLATILE spinorFloat o10_im;
VOLATILE spinorFloat o11_re;
VOLATILE spinorFloat o11_im;
VOLATILE spinorFloat o12_re;
VOLATILE spinorFloat o12_im;
VOLATILE spinorFloat o20_re;
VOLATILE spinorFloat o20_im;
VOLATILE spinorFloat o21_re;
VOLATILE spinorFloat o21_im;
VOLATILE spinorFloat o22_re;
VOLATILE spinorFloat o22_im;
VOLATILE spinorFloat o30_re;
VOLATILE spinorFloat o30_im;
VOLATILE spinorFloat o31_re;
VOLATILE spinorFloat o31_im;
VOLATILE spinorFloat o32_re;
VOLATILE spinorFloat o32_im;

#include "read_gauge.h"
#include "io_spinor.h"

int x1, x2, x3, x4;
int X;

#if (DD_PREC==2) // half precision
int sp_norm_idx;
#endif // half precision

int sid;

int dim;
int face_idx;
int Y[4] = {X1,X2,X3,X4};
#if (DD_PREC==2)
int faceVolume[4];
faceVolume[0] = (X2*X3*X4)>>1;
faceVolume[1] = (X1*X3*X4)>>1;
faceVolume[2] = (X1*X2*X4)>>1;
faceVolume[3] = (X1*X2*X3)>>1;
#endif

  sid = blockIdx.x*blockDim.x + threadIdx.x;
  if (sid >= param.threads) return;


  dim = dimFromFaceIndex(sid, param); // sid is also modified

  const int face_volume = ((param.threadDimMapUpper[dim] - param.threadDimMapLower[dim]) >> 1);  
  const int face_num = (sid >= face_volume);              // is this thread updating face 0 or 1
  face_idx = sid - face_num*face_volume;        // index into the respective face


  const int dims[] = {X1, X2, X3, X4};
  coordsFromFaceIndex<1>(X, sid, x1, x2, x3, x4, face_idx, face_volume, dim, face_num, param.parity, dims);

  bool active = false;
  for(int dir=0; dir<4; ++dir){
    active = active || isActive(dim,dir,+1,x1,x2,x3,x4,param.commDim,param.X);
  }
  if(!active) return;


  READ_INTERMEDIATE_SPINOR(INTERTEX, param.sp_stride, sid, sid);

  o00_re = i00_re;  o00_im = i00_im;
  o01_re = i01_re;  o01_im = i01_im;
  o02_re = i02_re;  o02_im = i02_im;
  o10_re = i10_re;  o10_im = i10_im;
  o11_re = i11_re;  o11_im = i11_im;
  o12_re = i12_re;  o12_im = i12_im;
  o20_re = i20_re;  o20_im = i20_im;
  o21_re = i21_re;  o21_im = i21_im;
  o22_re = i22_re;  o22_im = i22_im;
  o30_re = i30_re;  o30_im = i30_im;
  o31_re = i31_re;  o31_im = i31_im;
  o32_re = i32_re;  o32_im = i32_im;
if (isActive(dim,0,+1,x1,x2,x3,x4,param.commDim,param.X) && x1==X1m1 )
{
  // Projector P0-
  // 1 0 0 -i 
  // 0 1 -i 0 
  // 0 i 1 0 
  // i 0 0 1 
  
  faceIndexFromCoords<1>(face_idx,x1,x2,x3,x4,0,Y);
  const int sp_idx = face_idx + param.ghostOffset[0];
#if (DD_PREC==2)
    sp_norm_idx = face_idx + faceVolume[0] + param.ghostNormOffset[0];
#endif
  
  const int ga_idx = sid;
  
  spinorFloat a0_re, a0_im;
  spinorFloat a1_re, a1_im;
  spinorFloat a2_re, a2_im;
  spinorFloat b0_re, b0_im;
  spinorFloat b1_re, b1_im;
  spinorFloat b2_re, b2_im;
  
  
  const int sp_stride_pad = ghostFace[0];
  
  // read half spinor from device memory
  READ_HALF_SPINOR(SPINORTEX, sp_stride_pad, sp_idx + (SPINOR_HOP/2)*sp_stride_pad, sp_norm_idx);
  
  a0_re = i00_re;  a0_im = i00_im;
  a1_re = i01_re;  a1_im = i01_im;
  a2_re = i02_re;  a2_im = i02_im;
  b0_re = i10_re;  b0_im = i10_im;
  b1_re = i11_re;  b1_im = i11_im;
  b2_re = i12_re;  b2_im = i12_im;
  
  // read gauge matrix from device memory
  READ_GAUGE_MATRIX(G, GAUGE0TEX, 0, ga_idx, ga_stride);
  
  // reconstruct gauge matrix
  RECONSTRUCT_GAUGE_MATRIX(0);
  
  // multiply row 0
  spinorFloat A0_re = 0;
  A0_re += g00_re * a0_re;
  A0_re -= g00_im * a0_im;
  A0_re += g01_re * a1_re;
  A0_re -= g01_im * a1_im;
  A0_re += g02_re * a2_re;
  A0_re -= g02_im * a2_im;
  spinorFloat A0_im = 0;
  A0_im += g00_re * a0_im;
  A0_im += g00_im * a0_re;
  A0_im += g01_re * a1_im;
  A0_im += g01_im * a1_re;
  A0_im += g02_re * a2_im;
  A0_im += g02_im * a2_re;
  spinorFloat B0_re = 0;
  B0_re += g00_re * b0_re;
  B0_re -= g00_im * b0_im;
  B0_re += g01_re * b1_re;
  B0_re -= g01_im * b1_im;
  B0_re += g02_re * b2_re;
  B0_re -= g02_im * b2_im;
  spinorFloat B0_im = 0;
  B0_im += g00_re * b0_im;
  B0_im += g00_im * b0_re;
  B0_im += g01_re * b1_im;
  B0_im += g01_im * b1_re;
  B0_im += g02_re * b2_im;
  B0_im += g02_im * b2_re;
  
  // multiply row 1
  spinorFloat A1_re = 0;
  A1_re += g10_re * a0_re;
  A1_re -= g10_im * a0_im;
  A1_re += g11_re * a1_re;
  A1_re -= g11_im * a1_im;
  A1_re += g12_re * a2_re;
  A1_re -= g12_im * a2_im;
  spinorFloat A1_im = 0;
  A1_im += g10_re * a0_im;
  A1_im += g10_im * a0_re;
  A1_im += g11_re * a1_im;
  A1_im += g11_im * a1_re;
  A1_im += g12_re * a2_im;
  A1_im += g12_im * a2_re;
  spinorFloat B1_re = 0;
  B1_re += g10_re * b0_re;
  B1_re -= g10_im * b0_im;
  B1_re += g11_re * b1_re;
  B1_re -= g11_im * b1_im;
  B1_re += g12_re * b2_re;
  B1_re -= g12_im * b2_im;
  spinorFloat B1_im = 0;
  B1_im += g10_re * b0_im;
  B1_im += g10_im * b0_re;
  B1_im += g11_re * b1_im;
  B1_im += g11_im * b1_re;
  B1_im += g12_re * b2_im;
  B1_im += g12_im * b2_re;
  
  // multiply row 2
  spinorFloat A2_re = 0;
  A2_re += g20_re * a0_re;
  A2_re -= g20_im * a0_im;
  A2_re += g21_re * a1_re;
  A2_re -= g21_im * a1_im;
  A2_re += g22_re * a2_re;
  A2_re -= g22_im * a2_im;
  spinorFloat A2_im = 0;
  A2_im += g20_re * a0_im;
  A2_im += g20_im * a0_re;
  A2_im += g21_re * a1_im;
  A2_im += g21_im * a1_re;
  A2_im += g22_re * a2_im;
  A2_im += g22_im * a2_re;
  spinorFloat B2_re = 0;
  B2_re += g20_re * b0_re;
  B2_re -= g20_im * b0_im;
  B2_re += g21_re * b1_re;
  B2_re -= g21_im * b1_im;
  B2_re += g22_re * b2_re;
  B2_re -= g22_im * b2_im;
  spinorFloat B2_im = 0;
  B2_im += g20_re * b0_im;
  B2_im += g20_im * b0_re;
  B2_im += g21_re * b1_im;
  B2_im += g21_im * b1_re;
  B2_im += g22_re * b2_im;
  B2_im += g22_im * b2_re;
  
  o00_re += A0_re;
  o00_im += A0_im;
  o10_re += B0_re;
  o10_im += B0_im;
  o20_re -= B0_im;
  o20_im += B0_re;
  o30_re -= A0_im;
  o30_im += A0_re;
  
  o01_re += A1_re;
  o01_im += A1_im;
  o11_re += B1_re;
  o11_im += B1_im;
  o21_re -= B1_im;
  o21_im += B1_re;
  o31_re -= A1_im;
  o31_im += A1_re;
  
  o02_re += A2_re;
  o02_im += A2_im;
  o12_re += B2_re;
  o12_im += B2_im;
  o22_re -= B2_im;
  o22_im += B2_re;
  o32_re -= A2_im;
  o32_im += A2_re;
  
}

if (isActive(dim,0,-1,x1,x2,x3,x4,param.commDim,param.X) && x1==0 )
{
  // Projector P0+
  // 1 0 0 i 
  // 0 1 i 0 
  // 0 -i 1 0 
  // -i 0 0 1 
  
  faceIndexFromCoords<1>(face_idx,x1,x2,x3,x4,0,Y);
  const int sp_idx = face_idx + param.ghostOffset[0];
#if (DD_PREC==2)
    sp_norm_idx = face_idx + param.ghostNormOffset[0];
#endif
  
  const int ga_idx = Vh+face_idx;
  
  spinorFloat a0_re, a0_im;
  spinorFloat a1_re, a1_im;
  spinorFloat a2_re, a2_im;
  spinorFloat b0_re, b0_im;
  spinorFloat b1_re, b1_im;
  spinorFloat b2_re, b2_im;
  
  
  const int sp_stride_pad = ghostFace[0];
  
  // read half spinor from device memory
  READ_HALF_SPINOR(SPINORTEX, sp_stride_pad, sp_idx, sp_norm_idx);
  
  a0_re = i00_re;  a0_im = i00_im;
  a1_re = i01_re;  a1_im = i01_im;
  a2_re = i02_re;  a2_im = i02_im;
  b0_re = i10_re;  b0_im = i10_im;
  b1_re = i11_re;  b1_im = i11_im;
  b2_re = i12_re;  b2_im = i12_im;
  
  // read gauge matrix from device memory
  READ_GAUGE_MATRIX(G, GAUGE1TEX, 1, ga_idx, ga_stride);
  
  // reconstruct gauge matrix
  RECONSTRUCT_GAUGE_MATRIX(1);
  
  // multiply row 0
  spinorFloat A0_re = 0;
  A0_re += gT00_re * a0_re;
  A0_re -= gT00_im * a0_im;
  A0_re += gT01_re * a1_re;
  A0_re -= gT01_im * a1_im;
  A0_re += gT02_re * a2_re;
  A0_re -= gT02_im * a2_im;
  spinorFloat A0_im = 0;
  A0_im += gT00_re * a0_im;
  A0_im += gT00_im * a0_re;
  A0_im += gT01_re * a1_im;
  A0_im += gT01_im * a1_re;
  A0_im += gT02_re * a2_im;
  A0_im += gT02_im * a2_re;
  spinorFloat B0_re = 0;
  B0_re += gT00_re * b0_re;
  B0_re -= gT00_im * b0_im;
  B0_re += gT01_re * b1_re;
  B0_re -= gT01_im * b1_im;
  B0_re += gT02_re * b2_re;
  B0_re -= gT02_im * b2_im;
  spinorFloat B0_im = 0;
  B0_im += gT00_re * b0_im;
  B0_im += gT00_im * b0_re;
  B0_im += gT01_re * b1_im;
  B0_im += gT01_im * b1_re;
  B0_im += gT02_re * b2_im;
  B0_im += gT02_im * b2_re;
  
  // multiply row 1
  spinorFloat A1_re = 0;
  A1_re += gT10_re * a0_re;
  A1_re -= gT10_im * a0_im;
  A1_re += gT11_re * a1_re;
  A1_re -= gT11_im * a1_im;
  A1_re += gT12_re * a2_re;
  A1_re -= gT12_im * a2_im;
  spinorFloat A1_im = 0;
  A1_im += gT10_re * a0_im;
  A1_im += gT10_im * a0_re;
  A1_im += gT11_re * a1_im;
  A1_im += gT11_im * a1_re;
  A1_im += gT12_re * a2_im;
  A1_im += gT12_im * a2_re;
  spinorFloat B1_re = 0;
  B1_re += gT10_re * b0_re;
  B1_re -= gT10_im * b0_im;
  B1_re += gT11_re * b1_re;
  B1_re -= gT11_im * b1_im;
  B1_re += gT12_re * b2_re;
  B1_re -= gT12_im * b2_im;
  spinorFloat B1_im = 0;
  B1_im += gT10_re * b0_im;
  B1_im += gT10_im * b0_re;
  B1_im += gT11_re * b1_im;
  B1_im += gT11_im * b1_re;
  B1_im += gT12_re * b2_im;
  B1_im += gT12_im * b2_re;
  
  // multiply row 2
  spinorFloat A2_re = 0;
  A2_re += gT20_re * a0_re;
  A2_re -= gT20_im * a0_im;
  A2_re += gT21_re * a1_re;
  A2_re -= gT21_im * a1_im;
  A2_re += gT22_re * a2_re;
  A2_re -= gT22_im * a2_im;
  spinorFloat A2_im = 0;
  A2_im += gT20_re * a0_im;
  A2_im += gT20_im * a0_re;
  A2_im += gT21_re * a1_im;
  A2_im += gT21_im * a1_re;
  A2_im += gT22_re * a2_im;
  A2_im += gT22_im * a2_re;
  spinorFloat B2_re = 0;
  B2_re += gT20_re * b0_re;
  B2_re -= gT20_im * b0_im;
  B2_re += gT21_re * b1_re;
  B2_re -= gT21_im * b1_im;
  B2_re += gT22_re * b2_re;
  B2_re -= gT22_im * b2_im;
  spinorFloat B2_im = 0;
  B2_im += gT20_re * b0_im;
  B2_im += gT20_im * b0_re;
  B2_im += gT21_re * b1_im;
  B2_im += gT21_im * b1_re;
  B2_im += gT22_re * b2_im;
  B2_im += gT22_im * b2_re;
  
  o00_re += A0_re;
  o00_im += A0_im;
  o10_re += B0_re;
  o10_im += B0_im;
  o20_re += B0_im;
  o20_im -= B0_re;
  o30_re += A0_im;
  o30_im -= A0_re;
  
  o01_re += A1_re;
  o01_im += A1_im;
  o11_re += B1_re;
  o11_im += B1_im;
  o21_re += B1_im;
  o21_im -= B1_re;
  o31_re += A1_im;
  o31_im -= A1_re;
  
  o02_re += A2_re;
  o02_im += A2_im;
  o12_re += B2_re;
  o12_im += B2_im;
  o22_re += B2_im;
  o22_im -= B2_re;
  o32_re += A2_im;
  o32_im -= A2_re;
  
}

if (isActive(dim,1,+1,x1,x2,x3,x4,param.commDim,param.X) && x2==X2m1 )
{
  // Projector P1-
  // 1 0 0 -1 
  // 0 1 1 0 
  // 0 1 1 0 
  // -1 0 0 1 
  
  faceIndexFromCoords<1>(face_idx,x1,x2,x3,x4,1,Y);
  const int sp_idx = face_idx + param.ghostOffset[1];
#if (DD_PREC==2)
    sp_norm_idx = face_idx + faceVolume[1] + param.ghostNormOffset[1];
#endif
  
  const int ga_idx = sid;
  
  spinorFloat a0_re, a0_im;
  spinorFloat a1_re, a1_im;
  spinorFloat a2_re, a2_im;
  spinorFloat b0_re, b0_im;
  spinorFloat b1_re, b1_im;
  spinorFloat b2_re, b2_im;
  
  
  const int sp_stride_pad = ghostFace[1];
  
  // read half spinor from device memory
  READ_HALF_SPINOR(SPINORTEX, sp_stride_pad, sp_idx + (SPINOR_HOP/2)*sp_stride_pad, sp_norm_idx);
  
  a0_re = i00_re;  a0_im = i00_im;
  a1_re = i01_re;  a1_im = i01_im;
  a2_re = i02_re;  a2_im = i02_im;
  b0_re = i10_re;  b0_im = i10_im;
  b1_re = i11_re;  b1_im = i11_im;
  b2_re = i12_re;  b2_im = i12_im;
  
  // read gauge matrix from device memory
  READ_GAUGE_MATRIX(G, GAUGE0TEX, 2, ga_idx, ga_stride);
  
  // reconstruct gauge matrix
  RECONSTRUCT_GAUGE_MATRIX(2);
  
  // multiply row 0
  spinorFloat A0_re = 0;
  A0_re += g00_re * a0_re;
  A0_re -= g00_im * a0_im;
  A0_re += g01_re * a1_re;
  A0_re -= g01_im * a1_im;
  A0_re += g02_re * a2_re;
  A0_re -= g02_im * a2_im;
  spinorFloat A0_im = 0;
  A0_im += g00_re * a0_im;
  A0_im += g00_im * a0_re;
  A0_im += g01_re * a1_im;
  A0_im += g01_im * a1_re;
  A0_im += g02_re * a2_im;
  A0_im += g02_im * a2_re;
  spinorFloat B0_re = 0;
  B0_re += g00_re * b0_re;
  B0_re -= g00_im * b0_im;
  B0_re += g01_re * b1_re;
  B0_re -= g01_im * b1_im;
  B0_re += g02_re * b2_re;
  B0_re -= g02_im * b2_im;
  spinorFloat B0_im = 0;
  B0_im += g00_re * b0_im;
  B0_im += g00_im * b0_re;
  B0_im += g01_re * b1_im;
  B0_im += g01_im * b1_re;
  B0_im += g02_re * b2_im;
  B0_im += g02_im * b2_re;
  
  // multiply row 1
  spinorFloat A1_re = 0;
  A1_re += g10_re * a0_re;
  A1_re -= g10_im * a0_im;
  A1_re += g11_re * a1_re;
  A1_re -= g11_im * a1_im;
  A1_re += g12_re * a2_re;
  A1_re -= g12_im * a2_im;
  spinorFloat A1_im = 0;
  A1_im += g10_re * a0_im;
  A1_im += g10_im * a0_re;
  A1_im += g11_re * a1_im;
  A1_im += g11_im * a1_re;
  A1_im += g12_re * a2_im;
  A1_im += g12_im * a2_re;
  spinorFloat B1_re = 0;
  B1_re += g10_re * b0_re;
  B1_re -= g10_im * b0_im;
  B1_re += g11_re * b1_re;
  B1_re -= g11_im * b1_im;
  B1_re += g12_re * b2_re;
  B1_re -= g12_im * b2_im;
  spinorFloat B1_im = 0;
  B1_im += g10_re * b0_im;
  B1_im += g10_im * b0_re;
  B1_im += g11_re * b1_im;
  B1_im += g11_im * b1_re;
  B1_im += g12_re * b2_im;
  B1_im += g12_im * b2_re;
  
  // multiply row 2
  spinorFloat A2_re = 0;
  A2_re += g20_re * a0_re;
  A2_re -= g20_im * a0_im;
  A2_re += g21_re * a1_re;
  A2_re -= g21_im * a1_im;
  A2_re += g22_re * a2_re;
  A2_re -= g22_im * a2_im;
  spinorFloat A2_im = 0;
  A2_im += g20_re * a0_im;
  A2_im += g20_im * a0_re;
  A2_im += g21_re * a1_im;
  A2_im += g21_im * a1_re;
  A2_im += g22_re * a2_im;
  A2_im += g22_im * a2_re;
  spinorFloat B2_re = 0;
  B2_re += g20_re * b0_re;
  B2_re -= g20_im * b0_im;
  B2_re += g21_re * b1_re;
  B2_re -= g21_im * b1_im;
  B2_re += g22_re * b2_re;
  B2_re -= g22_im * b2_im;
  spinorFloat B2_im = 0;
  B2_im += g20_re * b0_im;
  B2_im += g20_im * b0_re;
  B2_im += g21_re * b1_im;
  B2_im += g21_im * b1_re;
  B2_im += g22_re * b2_im;
  B2_im += g22_im * b2_re;
  
  o00_re += A0_re;
  o00_im += A0_im;
  o10_re += B0_re;
  o10_im += B0_im;
  o20_re += B0_re;
  o20_im += B0_im;
  o30_re -= A0_re;
  o30_im -= A0_im;
  
  o01_re += A1_re;
  o01_im += A1_im;
  o11_re += B1_re;
  o11_im += B1_im;
  o21_re += B1_re;
  o21_im += B1_im;
  o31_re -= A1_re;
  o31_im -= A1_im;
  
  o02_re += A2_re;
  o02_im += A2_im;
  o12_re += B2_re;
  o12_im += B2_im;
  o22_re += B2_re;
  o22_im += B2_im;
  o32_re -= A2_re;
  o32_im -= A2_im;
  
}

if (isActive(dim,1,-1,x1,x2,x3,x4,param.commDim,param.X) && x2==0 )
{
  // Projector P1+
  // 1 0 0 1 
  // 0 1 -1 0 
  // 0 -1 1 0 
  // 1 0 0 1 
  
  faceIndexFromCoords<1>(face_idx,x1,x2,x3,x4,1,Y);
  const int sp_idx = face_idx + param.ghostOffset[1];
#if (DD_PREC==2)
    sp_norm_idx = face_idx + param.ghostNormOffset[1];
#endif
  
  const int ga_idx = Vh+face_idx;
  
  spinorFloat a0_re, a0_im;
  spinorFloat a1_re, a1_im;
  spinorFloat a2_re, a2_im;
  spinorFloat b0_re, b0_im;
  spinorFloat b1_re, b1_im;
  spinorFloat b2_re, b2_im;
  
  
  const int sp_stride_pad = ghostFace[1];
  
  // read half spinor from device memory
  READ_HALF_SPINOR(SPINORTEX, sp_stride_pad, sp_idx, sp_norm_idx);
  
  a0_re = i00_re;  a0_im = i00_im;
  a1_re = i01_re;  a1_im = i01_im;
  a2_re = i02_re;  a2_im = i02_im;
  b0_re = i10_re;  b0_im = i10_im;
  b1_re = i11_re;  b1_im = i11_im;
  b2_re = i12_re;  b2_im = i12_im;
  
  // read gauge matrix from device memory
  READ_GAUGE_MATRIX(G, GAUGE1TEX, 3, ga_idx, ga_stride);
  
  // reconstruct gauge matrix
  RECONSTRUCT_GAUGE_MATRIX(3);
  
  // multiply row 0
  spinorFloat A0_re = 0;
  A0_re += gT00_re * a0_re;
  A0_re -= gT00_im * a0_im;
  A0_re += gT01_re * a1_re;
  A0_re -= gT01_im * a1_im;
  A0_re += gT02_re * a2_re;
  A0_re -= gT02_im * a2_im;
  spinorFloat A0_im = 0;
  A0_im += gT00_re * a0_im;
  A0_im += gT00_im * a0_re;
  A0_im += gT01_re * a1_im;
  A0_im += gT01_im * a1_re;
  A0_im += gT02_re * a2_im;
  A0_im += gT02_im * a2_re;
  spinorFloat B0_re = 0;
  B0_re += gT00_re * b0_re;
  B0_re -= gT00_im * b0_im;
  B0_re += gT01_re * b1_re;
  B0_re -= gT01_im * b1_im;
  B0_re += gT02_re * b2_re;
  B0_re -= gT02_im * b2_im;
  spinorFloat B0_im = 0;
  B0_im += gT00_re * b0_im;
  B0_im += gT00_im * b0_re;
  B0_im += gT01_re * b1_im;
  B0_im += gT01_im * b1_re;
  B0_im += gT02_re * b2_im;
  B0_im += gT02_im * b2_re;
  
  // multiply row 1
  spinorFloat A1_re = 0;
  A1_re += gT10_re * a0_re;
  A1_re -= gT10_im * a0_im;
  A1_re += gT11_re * a1_re;
  A1_re -= gT11_im * a1_im;
  A1_re += gT12_re * a2_re;
  A1_re -= gT12_im * a2_im;
  spinorFloat A1_im = 0;
  A1_im += gT10_re * a0_im;
  A1_im += gT10_im * a0_re;
  A1_im += gT11_re * a1_im;
  A1_im += gT11_im * a1_re;
  A1_im += gT12_re * a2_im;
  A1_im += gT12_im * a2_re;
  spinorFloat B1_re = 0;
  B1_re += gT10_re * b0_re;
  B1_re -= gT10_im * b0_im;
  B1_re += gT11_re * b1_re;
  B1_re -= gT11_im * b1_im;
  B1_re += gT12_re * b2_re;
  B1_re -= gT12_im * b2_im;
  spinorFloat B1_im = 0;
  B1_im += gT10_re * b0_im;
  B1_im += gT10_im * b0_re;
  B1_im += gT11_re * b1_im;
  B1_im += gT11_im * b1_re;
  B1_im += gT12_re * b2_im;
  B1_im += gT12_im * b2_re;
  
  // multiply row 2
  spinorFloat A2_re = 0;
  A2_re += gT20_re * a0_re;
  A2_re -= gT20_im * a0_im;
  A2_re += gT21_re * a1_re;
  A2_re -= gT21_im * a1_im;
  A2_re += gT22_re * a2_re;
  A2_re -= gT22_im * a2_im;
  spinorFloat A2_im = 0;
  A2_im += gT20_re * a0_im;
  A2_im += gT20_im * a0_re;
  A2_im += gT21_re * a1_im;
  A2_im += gT21_im * a1_re;
  A2_im += gT22_re * a2_im;
  A2_im += gT22_im * a2_re;
  spinorFloat B2_re = 0;
  B2_re += gT20_re * b0_re;
  B2_re -= gT20_im * b0_im;
  B2_re += gT21_re * b1_re;
  B2_re -= gT21_im * b1_im;
  B2_re += gT22_re * b2_re;
  B2_re -= gT22_im * b2_im;
  spinorFloat B2_im = 0;
  B2_im += gT20_re * b0_im;
  B2_im += gT20_im * b0_re;
  B2_im += gT21_re * b1_im;
  B2_im += gT21_im * b1_re;
  B2_im += gT22_re * b2_im;
  B2_im += gT22_im * b2_re;
  
  o00_re += A0_re;
  o00_im += A0_im;
  o10_re += B0_re;
  o10_im += B0_im;
  o20_re -= B0_re;
  o20_im -= B0_im;
  o30_re += A0_re;
  o30_im += A0_im;
  
  o01_re += A1_re;
  o01_im += A1_im;
  o11_re += B1_re;
  o11_im += B1_im;
  o21_re -= B1_re;
  o21_im -= B1_im;
  o31_re += A1_re;
  o31_im += A1_im;
  
  o02_re += A2_re;
  o02_im += A2_im;
  o12_re += B2_re;
  o12_im += B2_im;
  o22_re -= B2_re;
  o22_im -= B2_im;
  o32_re += A2_re;
  o32_im += A2_im;
  
}

if (isActive(dim,2,+1,x1,x2,x3,x4,param.commDim,param.X) && x3==X3m1 )
{
  // Projector P2-
  // 1 0 -i 0 
  // 0 1 0 i 
  // i 0 1 0 
  // 0 -i 0 1 
  
  faceIndexFromCoords<1>(face_idx,x1,x2,x3,x4,2,Y);
  const int sp_idx = face_idx + param.ghostOffset[2];
#if (DD_PREC==2)
    sp_norm_idx = face_idx + faceVolume[2] + param.ghostNormOffset[2];
#endif
  
  const int ga_idx = sid;
  
  spinorFloat a0_re, a0_im;
  spinorFloat a1_re, a1_im;
  spinorFloat a2_re, a2_im;
  spinorFloat b0_re, b0_im;
  spinorFloat b1_re, b1_im;
  spinorFloat b2_re, b2_im;
  
  
  const int sp_stride_pad = ghostFace[2];
  
  // read half spinor from device memory
  READ_HALF_SPINOR(SPINORTEX, sp_stride_pad, sp_idx + (SPINOR_HOP/2)*sp_stride_pad, sp_norm_idx);
  
  a0_re = i00_re;  a0_im = i00_im;
  a1_re = i01_re;  a1_im = i01_im;
  a2_re = i02_re;  a2_im = i02_im;
  b0_re = i10_re;  b0_im = i10_im;
  b1_re = i11_re;  b1_im = i11_im;
  b2_re = i12_re;  b2_im = i12_im;
  
  // read gauge matrix from device memory
  READ_GAUGE_MATRIX(G, GAUGE0TEX, 4, ga_idx, ga_stride);
  
  // reconstruct gauge matrix
  RECONSTRUCT_GAUGE_MATRIX(4);
  
  // multiply row 0
  spinorFloat A0_re = 0;
  A0_re += g00_re * a0_re;
  A0_re -= g00_im * a0_im;
  A0_re += g01_re * a1_re;
  A0_re -= g01_im * a1_im;
  A0_re += g02_re * a2_re;
  A0_re -= g02_im * a2_im;
  spinorFloat A0_im = 0;
  A0_im += g00_re * a0_im;
  A0_im += g00_im * a0_re;
  A0_im += g01_re * a1_im;
  A0_im += g01_im * a1_re;
  A0_im += g02_re * a2_im;
  A0_im += g02_im * a2_re;
  spinorFloat B0_re = 0;
  B0_re += g00_re * b0_re;
  B0_re -= g00_im * b0_im;
  B0_re += g01_re * b1_re;
  B0_re -= g01_im * b1_im;
  B0_re += g02_re * b2_re;
  B0_re -= g02_im * b2_im;
  spinorFloat B0_im = 0;
  B0_im += g00_re * b0_im;
  B0_im += g00_im * b0_re;
  B0_im += g01_re * b1_im;
  B0_im += g01_im * b1_re;
  B0_im += g02_re * b2_im;
  B0_im += g02_im * b2_re;
  
  // multiply row 1
  spinorFloat A1_re = 0;
  A1_re += g10_re * a0_re;
  A1_re -= g10_im * a0_im;
  A1_re += g11_re * a1_re;
  A1_re -= g11_im * a1_im;
  A1_re += g12_re * a2_re;
  A1_re -= g12_im * a2_im;
  spinorFloat A1_im = 0;
  A1_im += g10_re * a0_im;
  A1_im += g10_im * a0_re;
  A1_im += g11_re * a1_im;
  A1_im += g11_im * a1_re;
  A1_im += g12_re * a2_im;
  A1_im += g12_im * a2_re;
  spinorFloat B1_re = 0;
  B1_re += g10_re * b0_re;
  B1_re -= g10_im * b0_im;
  B1_re += g11_re * b1_re;
  B1_re -= g11_im * b1_im;
  B1_re += g12_re * b2_re;
  B1_re -= g12_im * b2_im;
  spinorFloat B1_im = 0;
  B1_im += g10_re * b0_im;
  B1_im += g10_im * b0_re;
  B1_im += g11_re * b1_im;
  B1_im += g11_im * b1_re;
  B1_im += g12_re * b2_im;
  B1_im += g12_im * b2_re;
  
  // multiply row 2
  spinorFloat A2_re = 0;
  A2_re += g20_re * a0_re;
  A2_re -= g20_im * a0_im;
  A2_re += g21_re * a1_re;
  A2_re -= g21_im * a1_im;
  A2_re += g22_re * a2_re;
  A2_re -= g22_im * a2_im;
  spinorFloat A2_im = 0;
  A2_im += g20_re * a0_im;
  A2_im += g20_im * a0_re;
  A2_im += g21_re * a1_im;
  A2_im += g21_im * a1_re;
  A2_im += g22_re * a2_im;
  A2_im += g22_im * a2_re;
  spinorFloat B2_re = 0;
  B2_re += g20_re * b0_re;
  B2_re -= g20_im * b0_im;
  B2_re += g21_re * b1_re;
  B2_re -= g21_im * b1_im;
  B2_re += g22_re * b2_re;
  B2_re -= g22_im * b2_im;
  spinorFloat B2_im = 0;
  B2_im += g20_re * b0_im;
  B2_im += g20_im * b0_re;
  B2_im += g21_re * b1_im;
  B2_im += g21_im * b1_re;
  B2_im += g22_re * b2_im;
  B2_im += g22_im * b2_re;
  
  o00_re += A0_re;
  o00_im += A0_im;
  o10_re += B0_re;
  o10_im += B0_im;
  o20_re -= A0_im;
  o20_im += A0_re;
  o30_re += B0_im;
  o30_im -= B0_re;
  
  o01_re += A1_re;
  o01_im += A1_im;
  o11_re += B1_re;
  o11_im += B1_im;
  o21_re -= A1_im;
  o21_im += A1_re;
  o31_re += B1_im;
  o31_im -= B1_re;
  
  o02_re += A2_re;
  o02_im += A2_im;
  o12_re += B2_re;
  o12_im += B2_im;
  o22_re -= A2_im;
  o22_im += A2_re;
  o32_re += B2_im;
  o32_im -= B2_re;
  
}

if (isActive(dim,2,-1,x1,x2,x3,x4,param.commDim,param.X) && x3==0 )
{
  // Projector P2+
  // 1 0 i 0 
  // 0 1 0 -i 
  // -i 0 1 0 
  // 0 i 0 1 
  
  faceIndexFromCoords<1>(face_idx,x1,x2,x3,x4,2,Y);
  const int sp_idx = face_idx + param.ghostOffset[2];
#if (DD_PREC==2)
    sp_norm_idx = face_idx + param.ghostNormOffset[2];
#endif
  
  const int ga_idx = Vh+face_idx;
  
  spinorFloat a0_re, a0_im;
  spinorFloat a1_re, a1_im;
  spinorFloat a2_re, a2_im;
  spinorFloat b0_re, b0_im;
  spinorFloat b1_re, b1_im;
  spinorFloat b2_re, b2_im;
  
  
  const int sp_stride_pad = ghostFace[2];
  
  // read half spinor from device memory
  READ_HALF_SPINOR(SPINORTEX, sp_stride_pad, sp_idx, sp_norm_idx);
  
  a0_re = i00_re;  a0_im = i00_im;
  a1_re = i01_re;  a1_im = i01_im;
  a2_re = i02_re;  a2_im = i02_im;
  b0_re = i10_re;  b0_im = i10_im;
  b1_re = i11_re;  b1_im = i11_im;
  b2_re = i12_re;  b2_im = i12_im;
  
  // read gauge matrix from device memory
  READ_GAUGE_MATRIX(G, GAUGE1TEX, 5, ga_idx, ga_stride);
  
  // reconstruct gauge matrix
  RECONSTRUCT_GAUGE_MATRIX(5);
  
  // multiply row 0
  spinorFloat A0_re = 0;
  A0_re += gT00_re * a0_re;
  A0_re -= gT00_im * a0_im;
  A0_re += gT01_re * a1_re;
  A0_re -= gT01_im * a1_im;
  A0_re += gT02_re * a2_re;
  A0_re -= gT02_im * a2_im;
  spinorFloat A0_im = 0;
  A0_im += gT00_re * a0_im;
  A0_im += gT00_im * a0_re;
  A0_im += gT01_re * a1_im;
  A0_im += gT01_im * a1_re;
  A0_im += gT02_re * a2_im;
  A0_im += gT02_im * a2_re;
  spinorFloat B0_re = 0;
  B0_re += gT00_re * b0_re;
  B0_re -= gT00_im * b0_im;
  B0_re += gT01_re * b1_re;
  B0_re -= gT01_im * b1_im;
  B0_re += gT02_re * b2_re;
  B0_re -= gT02_im * b2_im;
  spinorFloat B0_im = 0;
  B0_im += gT00_re * b0_im;
  B0_im += gT00_im * b0_re;
  B0_im += gT01_re * b1_im;
  B0_im += gT01_im * b1_re;
  B0_im += gT02_re * b2_im;
  B0_im += gT02_im * b2_re;
  
  // multiply row 1
  spinorFloat A1_re = 0;
  A1_re += gT10_re * a0_re;
  A1_re -= gT10_im * a0_im;
  A1_re += gT11_re * a1_re;
  A1_re -= gT11_im * a1_im;
  A1_re += gT12_re * a2_re;
  A1_re -= gT12_im * a2_im;
  spinorFloat A1_im = 0;
  A1_im += gT10_re * a0_im;
  A1_im += gT10_im * a0_re;
  A1_im += gT11_re * a1_im;
  A1_im += gT11_im * a1_re;
  A1_im += gT12_re * a2_im;
  A1_im += gT12_im * a2_re;
  spinorFloat B1_re = 0;
  B1_re += gT10_re * b0_re;
  B1_re -= gT10_im * b0_im;
  B1_re += gT11_re * b1_re;
  B1_re -= gT11_im * b1_im;
  B1_re += gT12_re * b2_re;
  B1_re -= gT12_im * b2_im;
  spinorFloat B1_im = 0;
  B1_im += gT10_re * b0_im;
  B1_im += gT10_im * b0_re;
  B1_im += gT11_re * b1_im;
  B1_im += gT11_im * b1_re;
  B1_im += gT12_re * b2_im;
  B1_im += gT12_im * b2_re;
  
  // multiply row 2
  spinorFloat A2_re = 0;
  A2_re += gT20_re * a0_re;
  A2_re -= gT20_im * a0_im;
  A2_re += gT21_re * a1_re;
  A2_re -= gT21_im * a1_im;
  A2_re += gT22_re * a2_re;
  A2_re -= gT22_im * a2_im;
  spinorFloat A2_im = 0;
  A2_im += gT20_re * a0_im;
  A2_im += gT20_im * a0_re;
  A2_im += gT21_re * a1_im;
  A2_im += gT21_im * a1_re;
  A2_im += gT22_re * a2_im;
  A2_im += gT22_im * a2_re;
  spinorFloat B2_re = 0;
  B2_re += gT20_re * b0_re;
  B2_re -= gT20_im * b0_im;
  B2_re += gT21_re * b1_re;
  B2_re -= gT21_im * b1_im;
  B2_re += gT22_re * b2_re;
  B2_re -= gT22_im * b2_im;
  spinorFloat B2_im = 0;
  B2_im += gT20_re * b0_im;
  B2_im += gT20_im * b0_re;
  B2_im += gT21_re * b1_im;
  B2_im += gT21_im * b1_re;
  B2_im += gT22_re * b2_im;
  B2_im += gT22_im * b2_re;
  
  o00_re += A0_re;
  o00_im += A0_im;
  o10_re += B0_re;
  o10_im += B0_im;
  o20_re += A0_im;
  o20_im -= A0_re;
  o30_re -= B0_im;
  o30_im += B0_re;
  
  o01_re += A1_re;
  o01_im += A1_im;
  o11_re += B1_re;
  o11_im += B1_im;
  o21_re += A1_im;
  o21_im -= A1_re;
  o31_re -= B1_im;
  o31_im += B1_re;
  
  o02_re += A2_re;
  o02_im += A2_im;
  o12_re += B2_re;
  o12_im += B2_im;
  o22_re += A2_im;
  o22_im -= A2_re;
  o32_re -= B2_im;
  o32_im += B2_re;
  
}

if (isActive(dim,3,+1,x1,x2,x3,x4,param.commDim,param.X) && x4==X4m1 )
{
  // Projector P3-
  // 0 0 0 0 
  // 0 0 0 0 
  // 0 0 2 0 
  // 0 0 0 2 
  
  faceIndexFromCoords<1>(face_idx,x1,x2,x3,x4,3,Y);
  const int sp_idx = face_idx + param.ghostOffset[3];
#if (DD_PREC==2)
    sp_norm_idx = face_idx + faceVolume[3] + param.ghostNormOffset[3];
#endif
  
  const int ga_idx = sid;
  
  if (gauge_fixed && ga_idx < X4X3X2X1hmX3X2X1h)
  {
    spinorFloat a0_re, a0_im;
    spinorFloat a1_re, a1_im;
    spinorFloat a2_re, a2_im;
    spinorFloat b0_re, b0_im;
    spinorFloat b1_re, b1_im;
    spinorFloat b2_re, b2_im;
    
    
    const int sp_stride_pad = ghostFace[3];
    //const int t_proj_scale = TPROJSCALE;
    
    // read half spinor from device memory
    READ_HALF_SPINOR(SPINORTEX, sp_stride_pad, sp_idx + (SPINOR_HOP/2)*sp_stride_pad, sp_norm_idx);
    
#ifdef TWIST_INV_DSLASH
    a0_re = i00_re;  a0_im = i00_im;
    a1_re = i01_re;  a1_im = i01_im;
    a2_re = i02_re;  a2_im = i02_im;
    b0_re = i10_re;  b0_im = i10_im;
    b1_re = i11_re;  b1_im = i11_im;
    b2_re = i12_re;  b2_im = i12_im;
#else  
    a0_re = 2*i00_re;  a0_im = 2*i00_im;
    a1_re = 2*i01_re;  a1_im = 2*i01_im;
    a2_re = 2*i02_re;  a2_im = 2*i02_im;
    b0_re = 2*i10_re;  b0_im = 2*i10_im;
    b1_re = 2*i11_re;  b1_im = 2*i11_im;
    b2_re = 2*i12_re;  b2_im = 2*i12_im;
#endif 
    
    // identity gauge matrix
    spinorFloat A0_re = a0_re; spinorFloat A0_im = a0_im;
    spinorFloat B0_re = b0_re; spinorFloat B0_im = b0_im;
    spinorFloat A1_re = a1_re; spinorFloat A1_im = a1_im;
    spinorFloat B1_re = b1_re; spinorFloat B1_im = b1_im;
    spinorFloat A2_re = a2_re; spinorFloat A2_im = a2_im;
    spinorFloat B2_re = b2_re; spinorFloat B2_im = b2_im;
    
    o20_re += A0_re;
    o20_im += A0_im;
    o30_re += B0_re;
    o30_im += B0_im;
    
    o21_re += A1_re;
    o21_im += A1_im;
    o31_re += B1_re;
    o31_im += B1_im;
    
    o22_re += A2_re;
    o22_im += A2_im;
    o32_re += B2_re;
    o32_im += B2_im;
    
  } else {
    spinorFloat a0_re, a0_im;
    spinorFloat a1_re, a1_im;
    spinorFloat a2_re, a2_im;
    spinorFloat b0_re, b0_im;
    spinorFloat b1_re, b1_im;
    spinorFloat b2_re, b2_im;
    
    
    const int sp_stride_pad = ghostFace[3];
    //const int t_proj_scale = TPROJSCALE;
    
    // read half spinor from device memory
    READ_HALF_SPINOR(SPINORTEX, sp_stride_pad, sp_idx + (SPINOR_HOP/2)*sp_stride_pad, sp_norm_idx);
    
#ifdef TWIST_INV_DSLASH
    a0_re = i00_re;  a0_im = i00_im;
    a1_re = i01_re;  a1_im = i01_im;
    a2_re = i02_re;  a2_im = i02_im;
    b0_re = i10_re;  b0_im = i10_im;
    b1_re = i11_re;  b1_im = i11_im;
    b2_re = i12_re;  b2_im = i12_im;
#else  
    a0_re = 2*i00_re;  a0_im = 2*i00_im;
    a1_re = 2*i01_re;  a1_im = 2*i01_im;
    a2_re = 2*i02_re;  a2_im = 2*i02_im;
    b0_re = 2*i10_re;  b0_im = 2*i10_im;
    b1_re = 2*i11_re;  b1_im = 2*i11_im;
    b2_re = 2*i12_re;  b2_im = 2*i12_im;
#endif 
    
    // read gauge matrix from device memory
    READ_GAUGE_MATRIX(G, GAUGE0TEX, 6, ga_idx, ga_stride);
    
    // reconstruct gauge matrix
    RECONSTRUCT_GAUGE_MATRIX(6);
    
    // multiply row 0
    spinorFloat A0_re = 0;
    A0_re += g00_re * a0_re;
    A0_re -= g00_im * a0_im;
    A0_re += g01_re * a1_re;
    A0_re -= g01_im * a1_im;
    A0_re += g02_re * a2_re;
    A0_re -= g02_im * a2_im;
    spinorFloat A0_im = 0;
    A0_im += g00_re * a0_im;
    A0_im += g00_im * a0_re;
    A0_im += g01_re * a1_im;
    A0_im += g01_im * a1_re;
    A0_im += g02_re * a2_im;
    A0_im += g02_im * a2_re;
    spinorFloat B0_re = 0;
    B0_re += g00_re * b0_re;
    B0_re -= g00_im * b0_im;
    B0_re += g01_re * b1_re;
    B0_re -= g01_im * b1_im;
    B0_re += g02_re * b2_re;
    B0_re -= g02_im * b2_im;
    spinorFloat B0_im = 0;
    B0_im += g00_re * b0_im;
    B0_im += g00_im * b0_re;
    B0_im += g01_re * b1_im;
    B0_im += g01_im * b1_re;
    B0_im += g02_re * b2_im;
    B0_im += g02_im * b2_re;
    
    // multiply row 1
    spinorFloat A1_re = 0;
    A1_re += g10_re * a0_re;
    A1_re -= g10_im * a0_im;
    A1_re += g11_re * a1_re;
    A1_re -= g11_im * a1_im;
    A1_re += g12_re * a2_re;
    A1_re -= g12_im * a2_im;
    spinorFloat A1_im = 0;
    A1_im += g10_re * a0_im;
    A1_im += g10_im * a0_re;
    A1_im += g11_re * a1_im;
    A1_im += g11_im * a1_re;
    A1_im += g12_re * a2_im;
    A1_im += g12_im * a2_re;
    spinorFloat B1_re = 0;
    B1_re += g10_re * b0_re;
    B1_re -= g10_im * b0_im;
    B1_re += g11_re * b1_re;
    B1_re -= g11_im * b1_im;
    B1_re += g12_re * b2_re;
    B1_re -= g12_im * b2_im;
    spinorFloat B1_im = 0;
    B1_im += g10_re * b0_im;
    B1_im += g10_im * b0_re;
    B1_im += g11_re * b1_im;
    B1_im += g11_im * b1_re;
    B1_im += g12_re * b2_im;
    B1_im += g12_im * b2_re;
    
    // multiply row 2
    spinorFloat A2_re = 0;
    A2_re += g20_re * a0_re;
    A2_re -= g20_im * a0_im;
    A2_re += g21_re * a1_re;
    A2_re -= g21_im * a1_im;
    A2_re += g22_re * a2_re;
    A2_re -= g22_im * a2_im;
    spinorFloat A2_im = 0;
    A2_im += g20_re * a0_im;
    A2_im += g20_im * a0_re;
    A2_im += g21_re * a1_im;
    A2_im += g21_im * a1_re;
    A2_im += g22_re * a2_im;
    A2_im += g22_im * a2_re;
    spinorFloat B2_re = 0;
    B2_re += g20_re * b0_re;
    B2_re -= g20_im * b0_im;
    B2_re += g21_re * b1_re;
    B2_re -= g21_im * b1_im;
    B2_re += g22_re * b2_re;
    B2_re -= g22_im * b2_im;
    spinorFloat B2_im = 0;
    B2_im += g20_re * b0_im;
    B2_im += g20_im * b0_re;
    B2_im += g21_re * b1_im;
    B2_im += g21_im * b1_re;
    B2_im += g22_re * b2_im;
    B2_im += g22_im * b2_re;
    
    o20_re += A0_re;
    o20_im += A0_im;
    o30_re += B0_re;
    o30_im += B0_im;
    
    o21_re += A1_re;
    o21_im += A1_im;
    o31_re += B1_re;
    o31_im += B1_im;
    
    o22_re += A2_re;
    o22_im += A2_im;
    o32_re += B2_re;
    o32_im += B2_im;
    
  }
}

if (isActive(dim,3,-1,x1,x2,x3,x4,param.commDim,param.X) && x4==0 )
{
  // Projector P3+
  // 2 0 0 0 
  // 0 2 0 0 
  // 0 0 0 0 
  // 0 0 0 0 
  
  faceIndexFromCoords<1>(face_idx,x1,x2,x3,x4,3,Y);
  const int sp_idx = face_idx + param.ghostOffset[3];
#if (DD_PREC==2)
    sp_norm_idx = face_idx + param.ghostNormOffset[3];
#endif
  
  const int ga_idx = Vh+face_idx;
  
  if (gauge_fixed && ga_idx < X4X3X2X1hmX3X2X1h)
  {
    spinorFloat a0_re, a0_im;
    spinorFloat a1_re, a1_im;
    spinorFloat a2_re, a2_im;
    spinorFloat b0_re, b0_im;
    spinorFloat b1_re, b1_im;
    spinorFloat b2_re, b2_im;
    
    
    const int sp_stride_pad = ghostFace[3];
    //const int t_proj_scale = TPROJSCALE;
    
    // read half spinor from device memory
    READ_HALF_SPINOR(SPINORTEX, sp_stride_pad, sp_idx, sp_norm_idx);
    
#ifdef TWIST_INV_DSLASH
    a0_re = i00_re;  a0_im = i00_im;
    a1_re = i01_re;  a1_im = i01_im;
    a2_re = i02_re;  a2_im = i02_im;
    b0_re = i10_re;  b0_im = i10_im;
    b1_re = i11_re;  b1_im = i11_im;
    b2_re = i12_re;  b2_im = i12_im;
#else  
    a0_re = 2*i00_re;  a0_im = 2*i00_im;
    a1_re = 2*i01_re;  a1_im = 2*i01_im;
    a2_re = 2*i02_re;  a2_im = 2*i02_im;
    b0_re = 2*i10_re;  b0_im = 2*i10_im;
    b1_re = 2*i11_re;  b1_im = 2*i11_im;
    b2_re = 2*i12_re;  b2_im = 2*i12_im;
#endif 
    
    // identity gauge matrix
    spinorFloat A0_re = a0_re; spinorFloat A0_im = a0_im;
    spinorFloat B0_re = b0_re; spinorFloat B0_im = b0_im;
    spinorFloat A1_re = a1_re; spinorFloat A1_im = a1_im;
    spinorFloat B1_re = b1_re; spinorFloat B1_im = b1_im;
    spinorFloat A2_re = a2_re; spinorFloat A2_im = a2_im;
    spinorFloat B2_re = b2_re; spinorFloat B2_im = b2_im;
    
    o00_re += A0_re;
    o00_im += A0_im;
    o10_re += B0_re;
    o10_im += B0_im;
    
    o01_re += A1_re;
    o01_im += A1_im;
    o11_re += B1_re;
    o11_im += B1_im;
    
    o02_re += A2_re;
    o02_im += A2_im;
    o12_re += B2_re;
    o12_im += B2_im;
    
  } else {
    spinorFloat a0_re, a0_im;
    spinorFloat a1_re, a1_im;
    spinorFloat a2_re, a2_im;
    spinorFloat b0_re, b0_im;
    spinorFloat b1_re, b1_im;
    spinorFloat b2_re, b2_im;
    
    
    const int sp_stride_pad = ghostFace[3];
    //const int t_proj_scale = TPROJSCALE;
    
    // read half spinor from device memory
    READ_HALF_SPINOR(SPINORTEX, sp_stride_pad, sp_idx, sp_norm_idx);
    
#ifdef TWIST_INV_DSLASH
    a0_re = i00_re;  a0_im = i00_im;
    a1_re = i01_re;  a1_im = i01_im;
    a2_re = i02_re;  a2_im = i02_im;
    b0_re = i10_re;  b0_im = i10_im;
    b1_re = i11_re;  b1_im = i11_im;
    b2_re = i12_re;  b2_im = i12_im;
#else  
    a0_re = 2*i00_re;  a0_im = 2*i00_im;
    a1_re = 2*i01_re;  a1_im = 2*i01_im;
    a2_re = 2*i02_re;  a2_im = 2*i02_im;
    b0_re = 2*i10_re;  b0_im = 2*i10_im;
    b1_re = 2*i11_re;  b1_im = 2*i11_im;
    b2_re = 2*i12_re;  b2_im = 2*i12_im;
#endif 
    
    // read gauge matrix from device memory
    READ_GAUGE_MATRIX(G, GAUGE1TEX, 7, ga_idx, ga_stride);
    
    // reconstruct gauge matrix
    RECONSTRUCT_GAUGE_MATRIX(7);
    
    // multiply row 0
    spinorFloat A0_re = 0;
    A0_re += gT00_re * a0_re;
    A0_re -= gT00_im * a0_im;
    A0_re += gT01_re * a1_re;
    A0_re -= gT01_im * a1_im;
    A0_re += gT02_re * a2_re;
    A0_re -= gT02_im * a2_im;
    spinorFloat A0_im = 0;
    A0_im += gT00_re * a0_im;
    A0_im += gT00_im * a0_re;
    A0_im += gT01_re * a1_im;
    A0_im += gT01_im * a1_re;
    A0_im += gT02_re * a2_im;
    A0_im += gT02_im * a2_re;
    spinorFloat B0_re = 0;
    B0_re += gT00_re * b0_re;
    B0_re -= gT00_im * b0_im;
    B0_re += gT01_re * b1_re;
    B0_re -= gT01_im * b1_im;
    B0_re += gT02_re * b2_re;
    B0_re -= gT02_im * b2_im;
    spinorFloat B0_im = 0;
    B0_im += gT00_re * b0_im;
    B0_im += gT00_im * b0_re;
    B0_im += gT01_re * b1_im;
    B0_im += gT01_im * b1_re;
    B0_im += gT02_re * b2_im;
    B0_im += gT02_im * b2_re;
    
    // multiply row 1
    spinorFloat A1_re = 0;
    A1_re += gT10_re * a0_re;
    A1_re -= gT10_im * a0_im;
    A1_re += gT11_re * a1_re;
    A1_re -= gT11_im * a1_im;
    A1_re += gT12_re * a2_re;
    A1_re -= gT12_im * a2_im;
    spinorFloat A1_im = 0;
    A1_im += gT10_re * a0_im;
    A1_im += gT10_im * a0_re;
    A1_im += gT11_re * a1_im;
    A1_im += gT11_im * a1_re;
    A1_im += gT12_re * a2_im;
    A1_im += gT12_im * a2_re;
    spinorFloat B1_re = 0;
    B1_re += gT10_re * b0_re;
    B1_re -= gT10_im * b0_im;
    B1_re += gT11_re * b1_re;
    B1_re -= gT11_im * b1_im;
    B1_re += gT12_re * b2_re;
    B1_re -= gT12_im * b2_im;
    spinorFloat B1_im = 0;
    B1_im += gT10_re * b0_im;
    B1_im += gT10_im * b0_re;
    B1_im += gT11_re * b1_im;
    B1_im += gT11_im * b1_re;
    B1_im += gT12_re * b2_im;
    B1_im += gT12_im * b2_re;
    
    // multiply row 2
    spinorFloat A2_re = 0;
    A2_re += gT20_re * a0_re;
    A2_re -= gT20_im * a0_im;
    A2_re += gT21_re * a1_re;
    A2_re -= gT21_im * a1_im;
    A2_re += gT22_re * a2_re;
    A2_re -= gT22_im * a2_im;
    spinorFloat A2_im = 0;
    A2_im += gT20_re * a0_im;
    A2_im += gT20_im * a0_re;
    A2_im += gT21_re * a1_im;
    A2_im += gT21_im * a1_re;
    A2_im += gT22_re * a2_im;
    A2_im += gT22_im * a2_re;
    spinorFloat B2_re = 0;
    B2_re += gT20_re * b0_re;
    B2_re -= gT20_im * b0_im;
    B2_re += gT21_re * b1_re;
    B2_re -= gT21_im * b1_im;
    B2_re += gT22_re * b2_re;
    B2_re -= gT22_im * b2_im;
    spinorFloat B2_im = 0;
    B2_im += gT20_re * b0_im;
    B2_im += gT20_im * b0_re;
    B2_im += gT21_re * b1_im;
    B2_im += gT21_im * b1_re;
    B2_im += gT22_re * b2_im;
    B2_im += gT22_im * b2_re;
    
    o00_re += A0_re;
    o00_im += A0_im;
    o10_re += B0_re;
    o10_im += B0_im;
    
    o01_re += A1_re;
    o01_im += A1_im;
    o11_re += B1_re;
    o11_im += B1_im;
    
    o02_re += A2_re;
    o02_im += A2_im;
    o12_re += B2_re;
    o12_im += B2_im;
    
  }
}

{
#ifdef DSLASH_XPAY
  READ_ACCUM(ACCUMTEX, param.sp_stride)
  
#ifndef TWIST_XPAY
#ifndef TWIST_INV_DSLASH
  //perform invert twist first:
  APPLY_TWIST_INV( a, b, o);
#endif
  o00_re += acc00_re;
  o00_im += acc00_im;
  o01_re += acc01_re;
  o01_im += acc01_im;
  o02_re += acc02_re;
  o02_im += acc02_im;
  o10_re += acc10_re;
  o10_im += acc10_im;
  o11_re += acc11_re;
  o11_im += acc11_im;
  o12_re += acc12_re;
  o12_im += acc12_im;
  o20_re += acc20_re;
  o20_im += acc20_im;
  o21_re += acc21_re;
  o21_im += acc21_im;
  o22_re += acc22_re;
  o22_im += acc22_im;
  o30_re += acc30_re;
  o30_im += acc30_im;
  o31_re += acc31_re;
  o31_im += acc31_im;
  o32_re += acc32_re;
  o32_im += acc32_im;
#else
  APPLY_TWIST( a, acc);
  //warning! b is unrelated to the twisted mass parameter in this case!
  
  o00_re = b*o00_re+acc00_re;
  o00_im = b*o00_im+acc00_im;
  o01_re = b*o01_re+acc01_re;
  o01_im = b*o01_im+acc01_im;
  o02_re = b*o02_re+acc02_re;
  o02_im = b*o02_im+acc02_im;
  o10_re = b*o10_re+acc10_re;
  o10_im = b*o10_im+acc10_im;
  o11_re = b*o11_re+acc11_re;
  o11_im = b*o11_im+acc11_im;
  o12_re = b*o12_re+acc12_re;
  o12_im = b*o12_im+acc12_im;
  o20_re = b*o20_re+acc20_re;
  o20_im = b*o20_im+acc20_im;
  o21_re = b*o21_re+acc21_re;
  o21_im = b*o21_im+acc21_im;
  o22_re = b*o22_re+acc22_re;
  o22_im = b*o22_im+acc22_im;
  o30_re = b*o30_re+acc30_re;
  o30_im = b*o30_im+acc30_im;
  o31_re = b*o31_re+acc31_re;
  o31_im = b*o31_im+acc31_im;
  o32_re = b*o32_re+acc32_re;
  o32_im = b*o32_im+acc32_im;
#endif//TWIST_XPAY
#else //no XPAY
#ifndef TWIST_INV_DSLASH
     APPLY_TWIST_INV( a, b, o);
#endif
#endif
}

// write spinor field back to device memory
WRITE_SPINOR(param.sp_stride);

// undefine to prevent warning when precision is changed
#undef spinorFloat
#undef g00_re
#undef g00_im
#undef g01_re
#undef g01_im
#undef g02_re
#undef g02_im
#undef g10_re
#undef g10_im
#undef g11_re
#undef g11_im
#undef g12_re
#undef g12_im
#undef g20_re
#undef g20_im
#undef g21_re
#undef g21_im
#undef g22_re
#undef g22_im

#undef i00_re
#undef i00_im
#undef i01_re
#undef i01_im
#undef i02_re
#undef i02_im
#undef i10_re
#undef i10_im
#undef i11_re
#undef i11_im
#undef i12_re
#undef i12_im
#undef i20_re
#undef i20_im
#undef i21_re
#undef i21_im
#undef i22_re
#undef i22_im
#undef i30_re
#undef i30_im
#undef i31_re
#undef i31_im
#undef i32_re
#undef i32_im

#undef acc00_re
#undef acc00_im
#undef acc01_re
#undef acc01_im
#undef acc02_re
#undef acc02_im
#undef acc10_re
#undef acc10_im
#undef acc11_re
#undef acc11_im
#undef acc12_re
#undef acc12_im
#undef acc20_re
#undef acc20_im
#undef acc21_re
#undef acc21_im
#undef acc22_re
#undef acc22_im
#undef acc30_re
#undef acc30_im
#undef acc31_re
#undef acc31_im
#undef acc32_re
#undef acc32_im



#undef VOLATILE

#endif // MULTI_GPU
