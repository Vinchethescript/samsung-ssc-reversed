#include <stdint.h>
#include <arm_neon.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>

typedef int32_t _BOOL4;      // 4-byte boolean
typedef int64_t _QWORD;     // 8-byte unsigned integer
typedef uint32_t _DWORD;     // 4-byte unsigned integer
typedef uint8_t _BYTE;       // 1-byte unsigned integer
typedef __int128_t _OWORD;   // 16-byte (128-bit) type from n128
typedef uint16_t _WORD;      // 2-byte unsigned integer


#define LODWORD(x) (*((uint32_t *)&(x)))
#define HIDWORD(x) (*((uint32_t *)&(x) + 1))
#define SHIDWORD(x) (*((int32_t *)&(x) + 1))
#define LOWORD(x)    (*((uint16_t *)&(x)))
#define HIWORD(x)    (*((uint16_t *)&(x) + 1))
#define LOBYTE(x)    (*((uint8_t *)&(x)))
#define HIBYTE(x)    (*((uint8_t *)&(x) + 1))

#define WORD2 HIWORD
#define DWORD1 LODWORD
#define SDWORD2 HIDWORD
#define SLODWORD LODWORD

#define ZERO8x8   vdup_n_s8(0)
#define ZERO8x16  vdupq_n_s8(0)

#define ZERO16x4  vdup_n_s16(0)
#define ZERO16x8  vdupq_n_s16(0)

#define ZERO32x2  vdup_n_s32(0)
#define ZERO32x4  vdupq_n_s32(0)

#define ZERO64x2  vdupq_n_s64(0)


_DWORD dword_2EDB0[1832]; // idb
int32x2_t pcmpower[864]; // idb
float coeffs96andbelow; // weak
float coeffs; // weak
char in_shared; // weak
int64_t unk_2DF50; // weak
int16_t unk_2B4F0; // weak
int unk_16B48; // weak
int64_t unk_16B4C; // weak
int64_t unk_16B7A; // weak
int64_t unk_16BA8; // weak
__int128_t xmmword_16B10 = 0x7000000060000000500000004LL; // weak
__int128_t xmmword_16A80 = 0x3000000020000000100000000LL; // weak
__int128_t xmmword_149B0 = 0x19000000000000000000000000LL; // weak
__int128_t xmmword_149C0 = 36028797018963968LL; // weak

int count_for_debug = 0; // weak


char eMeans[25] =
{
    'g',
    'd',
    '\\',
    'U',
    'Q',
    'M',
    'H',
    'F',
    'N',
    'K',
    'I',
    'G',
    'N',
    'J',
    'E',
    'H',
    'F',
    'J',
    'L',
    'G',
    '<',
    '<',
    '<',
    '<',
    '<'
}; // idb
char tf_select_table[8] = { '\0', '\xFE', '\0', '\xFD', '\x03', '\0', '\x01', '\xFF' }; // idb
int64_t qword_108 = 36LL; // weak
int pre_shared[]; // weak
int previous_uhq_index; // weak
int64_t drc_struct; // weak
int unk_295D8;
int64_t qword_295E0; // weak
int DRC_ChNum; // weak
int dword_295DC; // weak
int unk_295D4;

int64_t set_DRC_limit_gain(int64_t ret) {
    drc_struct = ret;
    return ret;
}

long double ec_enc_init(int64_t a1, int64_t a2, int a3) {
    long double result = *(long double *)&xmmword_149B0;

    *(_QWORD *)a1 = a2;
    *(_QWORD *)(a1 + 44) = 0xFFFFFFFFLL;
    *(_OWORD *)(a1 + 12) = xmmword_149B0;
    *(_OWORD *)(a1 + 28) = xmmword_149C0;
    *(_DWORD *)(a1 + 8) = a3;
    return result;
}

double Biquad_Narrow_int2int_stereo(int32x2_t *a1, uint64_t *a2, const float *a3, int64_t a4, int a5, double a6, long double a7) {
  __int128_t v12; // q0
  int64_t v13; // d2
  int64_t v23; // d20
  int32x2_t v24; // s19

  *(_QWORD *)&v12 = *(_QWORD *)(a4 + 32);
  LODWORD(a7) = *(_DWORD *)a4;
  LODWORD(v13) = *(_DWORD *)(a4 + 8);
  int32x2_t v7 = vdup_n_s32(*(_DWORD *)(a4 + 16));
  int32x2_t v8 = vdup_n_s32(*(_DWORD *)(a4 + 24));
  const float *v9 = a3 + 2;
  const float *v10 = a3 + 3;
  const float *v11 = a3 + 4;
  *((_QWORD *)&v12 + 1) = *(_QWORD *)(a4 + 72);
  DWORD1(a7) = *(_DWORD *)(a4 + 40);
  HIDWORD(v13) = *(_DWORD *)(a4 + 48);
  int v14 = *(_DWORD *)(a4 + 56);
  int v15 = *(_DWORD *)(a4 + 64);
  float32x2_t v17 = vld1_dup_f32(a3);
  const float *v16 = a3 + 2;
  float32x2_t v18 = vld1_dup_f32(v9);
  float32x2_t v19 = vld1_dup_f32(v10);
  float32x2_t v20 = vld1_dup_f32(v11);
  float32x2_t v21 = vld1_dup_f32(v16);

  do {
    uint64_t v22 = *a2;
    ++a2;
    v23 = *(_QWORD *)&a7;
    v24 = v7;
    LODWORD(a7) = v22 << 7;
    int64x2_t v25 = vmlal_s32(vmlal_s32(vmlal_s32(vmlal_s32(vdupq_n_s64(v12), vdup_n_s32(a7), vcvt_s32_f32(v17)), vdup_n_s32(v23), vcvt_s32_f32(v21)), vdup_n_s32(v13), vcvt_s32_f32(v18)), v7, vcvt_s32_f32(v19));
    LODWORD(v13) = vget_lane_s32(vaddhn_s64(v25, vmull_s32(v8, vcvt_s32_f32(v20))), 0);
    --a5;
    *(_QWORD *)&v12 = vgetq_lane_s64(vmlal_s32(v25, v8, vcvt_s32_f32(v20)), 0);
    v7 = vshl_n_s32(vdup_n_s32(v13), 3uLL);
    LODWORD(v13) = vget_lane_s32(vshr_n_s32(vdup_n_s32(v13), 4uLL), 0);
    LOBYTE(v12) = vgetq_lane_s8(vandq_s8(vdupq_n_s8(v12), vdupq_n_s8(-1)), 0);
    *(_QWORD *)a1 = v13;
    a1 += 2;
    v8 = v24;
    v13 = v23;
  } while ( a5 > 0 );

  int64_t v26 = SLODWORD(a7);
  int64_t v27 = (signed int)v12;
  *(_QWORD *)&v12 = vgetq_lane_s64(vmovl_s32(vzip2_s32(vdup_n_s32(SLODWORD(a7)), vdup_n_s32(v23))), 0);
  *(_QWORD *)&a7 = vgetq_lane_s64(vmovl_s32(vzip2_s32(v7, v24)), 0);
  *(_QWORD *)a4 = v26;
  *(_QWORD *)(a4 + 8) = (signed int)v23;
  *(_QWORD *)(a4 + 16) = vget_lane_s32(v7, 0);
  *(_QWORD *)(a4 + 24) = vget_lane_s32(v24, 0);
  *(_QWORD *)(a4 + 32) = v27;
  *(_OWORD *)(a4 + 40) = v12;
  *(long double *)(a4 + 56) = a7;

  *(_QWORD *)(a4 + 72) = SDWORD2(v12);
  return *(double *)&v12;
}

int *powercalc(int *result, int a2, _DWORD *a3) {
  uint64_t v4; // x9


  if ( !a2 ) {
    *a3 = 0;
    return result;
  }

  uint64_t v3 = (unsigned int)(a2 - 1) + 1LL;
  if ( v3 >= 4 ) {
    int64_t v5 = a2 & 3;
    uint64_t v6 = v3 - v5;
    const float *v7 = (const float *)(result + 4);
    int64x2_t v8 = vdupq_n_s64(0uLL);
    result += 2 * v6;
    a2 -= v6;
    int64x2_t v9 = vdupq_n_s64(0uLL);
    do {
      const float *v10 = v7 - 4;
      float32x2_t v13 = vld1_f32(v7); // WAS float32x2x2_t
      float32x2_t v14 = vld1_f32(v10); // WAS float32x2x2_t
      v6 -= 4LL;
      v7 += 8;
      v9 = vaddw_s32(
             vaddw_s32(v9, vshr_n_s32(vshrn_n_s64(vmovl_s32(vcvt_s32_f32(vmulx_f32(v13, v13))), 0x10uLL), 1uLL)),
             vshr_n_s32(vshrn_n_s64(vmovl_s32(vcvt_s32_f32(vmulx_f32(v13, v13))), 0x10uLL), 1uLL));
      v8 = vaddw_s32(
             vaddw_s32(v8, vshr_n_s32(vshrn_n_s64(vmovl_s32(vcvt_s32_f32(vmulx_f32(v14, v14))), 0x10uLL), 1uLL)),
             vshr_n_s32(vshrn_n_s64(vmovl_s32(vcvt_s32_f32(vmulx_f32(v14, v14))), 0x10uLL), 1uLL));
    } while ( v6 );

    v4 = vaddvq_s64(vaddq_s64(v9, v8));
    if ( !(_DWORD)v5 )
      goto LABEL_9;

  } else {
    v4 = 0LL;
  }

  do {
    int64_t v11 = *result;
    int64_t v12 = result[1];
    result += 2;
    --a2;
    v4 += ((int)((uint64_t)(v11 * v11) >> 16) >> 1)
        + (int64_t)((int)((uint64_t)(v12 * v12) >> 16) >> 1);
  } while ( a2 );

LABEL_9:
  *a3 = v4 >> 9;
  return result;
}

int64_t CalculateLimitGain(int a1, int a2, int a3, int a4) {
  unsigned int v4; // w8
  int v5; // w9

  if ( a3 < 96001 ) {
    v4 = 30400;
    v5 = 80;
    goto LABEL_5;
  }
  if ( a3 < 128001 ) {
    v4 = 30900;
    v5 = 760;
LABEL_5:
    if ( (int)((uint64_t)(58982LL * a2) >> 16) > a1 ) {
      unsigned int v6 = v4 - v5;
      if ( a1 < a2 >> 2 )
        v6 = 0x8000;

      return v6;
    }
    return v4;
  }

  int v8; // w8
  if ( a4 == 96000 )
    v8 = 31564;
  else
    v8 = 31380;

  if ( a4 == 96000 ) {
    uint64_t v9 = (uint64_t)(61604LL * a2) >> 16;
    if ( a3 > 269999 ) {
      if ( (int)v9 <= a1 )
        return 31564LL;

      if ( (int)((uint64_t)(60293LL * a2) >> 16) <= a1 )
        return (unsigned int)(v8 - 331);

      if ( (int)((uint64_t)(58982LL * a2) >> 16) <= a1 )
        return (unsigned int)(v8 - 600);

      if ( (int)((uint64_t)(52428LL * a2) >> 16) <= a1 )
        return (unsigned int)(v8 - 750);

    } else {
      if ( (int)v9 <= a1 )
        return 31564LL;

      if ( (int)((uint64_t)(60293LL * a2) >> 16) <= a1 )
        return (unsigned int)(v8 - 250);

      if ( (int)((uint64_t)(58982LL * a2) >> 16) <= a1 )
        return (unsigned int)(v8 - 480);

      if ( (int)((uint64_t)(52428LL * a2) >> 16) <= a1 )
        return (unsigned int)(v8 - 700);

    }
    return (unsigned int)(v8 - 1400);
  }
  if ( (int)((uint64_t)(58982LL * a2) >> 16) <= a1 )
    return 31380LL;

  uint64_t v10 = (uint64_t)(52428LL * a2) >> 16;
  if ( (int)v10 <= a1 )
    return (unsigned int)(v8 - 993);

  bool v13; // zf
  uint8_t v15 = __OFSUB__((_DWORD)v10, a1);
  bool v14 = (int)v10 - a1 < 0;
  int v11 = a2 >> 2;
  unsigned int v12 = v8 - 1655;
  if ( v14 ^ v15 ) {
    v15 = 0;
    v13 = 0;
    v14 = 0;
  } else {
    v15 = __OFSUB__(v11, a1);
    v13 = v11 == a1;
    v14 = v11 - a1 < 0;
  }

  int64_t result; // x0
  if ( (uint8_t)(v14 ^ v15) | v13 )
    result = v12;
  else
    result = 0x8000LL;

  return result;
}

float *SoundBooster_DRC_Exe(float *result, int a2, long double a3) {
  int v3; // w11
  int v4; // w10
  int v5; // w14
  int v6; // w15
  int64_t v7; // x16
  int64_t v8; // x15
  signed int v9; // w16
  unsigned int v10; // w17
  float *v11; // x15
  int64_t v12; // x2
  int64_t v13; // x17
  int32x4_t v14; // s1
  float *v15; // x16
  int32x4_t v16; // s2
  int32x4_t v17; // s3
  int32x4_t v18; // s4
  __int128_t v19; // q5
  __int128_t v20; // q6
  _BOOL4 v21; // w2
  int v22; // t1
  signed int v23; // w15
  uint64_t v24; // x9
  int64_t v25; // x11
  int v26; // w12
  int64_t v27; // x14
  int64_t v28; // x12
  int64_t v29; // x12
  float *v30; // x13
  int64_t v31; // x14
  int64x2_t v32; // d1
  int64_t v33; // x15
  int64x2_t v34; // d1
  int64x2_t v35; // d2
  float32x2_t v36; // 0:q3.16,16:q4.16
  float32x4x2_t v37; // 0:q16.16,16:q17.16

  v3 = unk_295D8;
  v4 = HIDWORD(qword_295E0);
  v5 = DRC_ChNum * a2;
  if ( -(DRC_ChNum * a2) >= 0 )
    v6 = -v5;
  else
    v6 = -1;
  v7 = (unsigned int)(v6 + v5);
  v8 = v7 + 1;
  if ( (uint64_t)(v7 + 1) >= 8 )
  {
    v12 = ((_DWORD)v7 + 1) & 7;
    v13 = v8 - v12;
    v14 = vdupq_n_s32(drc_struct);
    v15 = result + 4;
    LODWORD(a3) = 0;
    *((_QWORD *)&a3 + 1) = 0LL;
    v16 = ZERO32x4;
    v17 = ZERO32x4;
    v5 -= v8 - v12;
    v11 = &result[v8 - v12];
    v18 = ZERO32x4;
    do {
      v19 = *((_OWORD *)v15 - 1);
      v20 = *(_OWORD *)v15;
      v13 -= 8LL;
      v15 += 8;
      LODWORD(v19) = abs(v19);
      LODWORD(v20) = abs(v20);
      LODWORD(a3) = (SLODWORD(a3) > v19) ? SLODWORD(a3) : v19;
      v16 = vmaxq_s32(v16, vdupq_n_s32(v20));
      v17 = vsubq_s32(v17, (int32x4_t)vcgtq_s32(vdupq_n_s32(v19), v14));
      v18 = vsubq_s32(v18, (int32x4_t)vcgtq_s32(vdupq_n_s32(v20), v14));
    } while ( v13 );

    v10 = vaddvq_s32(vaddq_s32(v18, v17));
    v9 = vmaxvq_f32(vmaxq_f32(vdupq_n_f32(a3), (float32x4_t)v16));
    if ( !(_DWORD)v12 )
      goto LABEL_16;
  }
  else
  {
    v9 = 0;
    v10 = 0;
    v11 = result;
  }
  do
  {
    v22 = *(_DWORD *)v11;
    ++v11;
    v21 = v22;
    --v5;
    if ( v22 < 0 )
      v21 = !v21;
    if ( v9 < v21 )
      v9 = v21;
    if ( v21 > drc_struct )
      ++v10;
  }
  while ( v5 > 0 );
LABEL_16:
  v23 = 0x400000;
  if ( v10 >= 0x19 )
    v23 = (signed int)(((int64_t)drc_struct << 31) / (unsigned int)v9) >> 9;
  if ( v23 <= dword_295DC )
    v3 = unk_295D4;
  v24 = (uint64_t)(v3 * (int64_t)dword_295DC + (0x400000 - v3) * (int64_t)v23) >> 22;
  if ( SHIDWORD(qword_295E0) >= (signed int)v24 )
    v4 = (uint64_t)(v3 * (int64_t)dword_295DC + (0x400000 - v3) * (int64_t)v23) >> 22;
  LODWORD(v25) = (v4 - (signed int)qword_295E0) / a2;
  dword_295DC = v24;
  if ( (_DWORD)qword_295E0 != 0x400000 || (_DWORD)v25 )
  {
    if ( -a2 >= 0 )
      v26 = -a2;
    else
      v26 = -1;
    v27 = (unsigned int)(v26 + a2);
    v28 = v27 + 1;
    v25 = (signed int)v25;
    if ( (uint64_t)(v27 + 1) < 4 )
    {
      v29 = (signed int)qword_295E0;
      v30 = result;
      do
      {
LABEL_32:
        --a2;
        *(_QWORD *)&a3 = v29 * (*(_QWORD *)v30);
        *((_QWORD *)&a3 + 1) *= v29;
        LODWORD(a3) = ((int32_t)(a3 * 10000) >> 0x16uLL) / 10000;
        *(_QWORD *)v30 = *(_QWORD *)&a3;
        v30 += 2;
        v29 += v25;
      }
      while ( a2 > 0 );
      goto LABEL_33;
    }
    v31 = ((_DWORD)v27 + 1) & 3;
    v32 = vdupq_n_s64((signed int)qword_295E0);
    *((_QWORD *)&a3 + 1) = v25;
    v33 = v28 - v31;
    //*(_QWORD *)&a3 = vaddq_s64(v32, 0LL); // this makes no sense
    v29 = (signed int)qword_295E0 + (v28 - v31) * v25;
    v30 = &result[2 * v33];
    a2 -= v33;
    v34 = vaddq_s64(v32, vdupq_n_s64(2 * v25));
    v35 = vdupq_n_s64(4 * v25);
    do {
      v36 = vld1_f32(result);
      v33 -= 4LL;
      // I don't know how to fix this
      /*v37 = COERCE_FLOAT(
              vshrn_high_n_s64(
                vshrn_n_s64(*(_QWORD *)&a3 * vmovl_s32(v36), 0x16uLL),
                v34 * vmovl_high_s32(v36),
                0x16uLL));
      *(_QWORD *)&a3 = vaddq_s64(*(int64x2_t *)&a3, v35);
      vst2q_f32(result, v37);*/
      result += 8;
      v34 = vaddq_s64(v34, v35);
    } while ( v33 );
    if ( (_DWORD)v31 )
      goto LABEL_32;
  }
LABEL_33:
  LODWORD(qword_295E0) = v4;
  HIDWORD(qword_295E0) = v24;
  return result;
}

int64_t SSC_COPY8(int64_t result, int64_t a2, int a3) {
  int64_t v3; // x8
  char v4; // w9
  int64_t v5; // x10

  if ( a3 ) {
    v3 = a3;
    do {
      v4 = *(_BYTE *)(a2 + v3 - 1);
      v5 = result + v3--;
      *(_BYTE *)(v5 - 1) = v4;
    } while ( v3 );
  }
  return result;
}

int64_t SSC_COPY32(int64_t result, int64_t a2, int a3) {
  if ( a3 ) {
    int64_t v3 = a3 - 1LL;
    do {
      int64_t v4 = 4 * v3;
      int v5 = *(_DWORD *)(a2 + 4 * v3--);
      *(_DWORD *)(result + v4) = v5;
    } while ( v3 != -1 );
  }
  return result;
}

int64_t ec_enc_shrink(int64_t a1, unsigned int a2) {

  unsigned int v2 = a2;
  int64_t v3 = a1;
  int64_t result = SSC_COPY8(
             *(_QWORD *)a1 + a2 - *(unsigned int *)(a1 + 12),
             *(_QWORD *)a1 + *(unsigned int *)(a1 + 8) - *(unsigned int *)(a1 + 12), 1);

  *(_DWORD *)(v3 + 8) = v2;

  return result;
}
int64_t ec_ilog(unsigned int a1) {
  unsigned int v3; // w8
  unsigned int v4; // w9
  int64_t result; // x0

  unsigned int v1 = a1 >> 16 * (a1 >> 16 != 0) >> 8 * (((a1 >> 16 * (a1 >> 16 != 0)) & 0xFF00) != 0);
  bool v2 = (v1 & 0xF0) != 0;
  v3 = v1 >> 4 * v2;
  v4 = (uint16_t)(((((a1 != 0) | (uint16_t)(16 * (a1 >> 16 != 0))) & 0xFFF7 | 8
                                                                                            * (((a1 >> 16 * (a1 >> 16 != 0)) & 0xFF00) != 0)) & 0xFFFB | 4 * v2) & 0xFFFD) | 2 * ((v3 & 0xC) != 0);
  if ( (2 << 2 * ((v3 & 0xC) != 0)) & v3 )
    result = v4 + 1;
  else
    result = v4;
  return result;
}

int64_t *ec_enc_bit_logp(int64_t *result, int a2, char a3) {
  unsigned int v3 = *((_DWORD *)result + 8);
  unsigned int v4 = v3 >> a3;
  unsigned int v5 = v3 - (v3 >> a3);
  if ( a2 )
    *((_DWORD *)result + 9) += v5;

  if ( a2 )
    v5 = v4;

  *((_DWORD *)result + 8) = v5;
  if ( v5 <= 0x8000 ) {
    unsigned int v6 = *((_DWORD *)result + 9);
    do {
      if ( v6 >> 15 == 255 ) {
        ++*((_DWORD *)result + 10);
      } else {
        int v7 = *((_DWORD *)result + 11);
        unsigned int v8 = v6 >> 23;
        if ( !(v7 & 0x80000000) ) {
          int v11; // w10
          int64_t v9 = *((unsigned int *)result + 7);
          if ( (unsigned int)(*((_DWORD *)result + 3) + v9) >= *((_DWORD *)result + 2) ) {
            v11 = -1;
          } else {
            int64_t v10 = *result;
            v11 = 0;
            *((_DWORD *)result + 7) = v9 + 1;
            *(_BYTE *)(v10 + v9) = v7 + v8;
          }
          *((_DWORD *)result + 12) |= v11;
        }
        int v12 = *((_DWORD *)result + 10);
        if ( v12 ) {
          char v13 = v8 - 1;
          do {
            int v16; // w11
            int64_t v14 = *((unsigned int *)result + 7);
            if ( (unsigned int)(*((_DWORD *)result + 3) + v14) >= *((_DWORD *)result + 2) ) {
              v16 = -1;
            } else {
              int64_t v15 = *result;
              *((_DWORD *)result + 7) = v14 + 1;
              *(_BYTE *)(v15 + v14) = v13;
              v12 = *((_DWORD *)result + 10);
              v16 = 0;
            }
            int v17 = *((_DWORD *)result + 12);
            *((_DWORD *)result + 10) = --v12;
            *((_DWORD *)result + 12) = v17 | v16;
          } while ( v12 );
        }
        int v18 = (v6 >> 15) & 0xFF;
        v5 = *((_DWORD *)result + 8);
        v6 = *((_DWORD *)result + 9);
        *((_DWORD *)result + 11) = v18;
      }
      v5 <<= 8;
      v6 = (v6 & 0x7FFF) << 8;
      int v19 = *((_DWORD *)result + 6) + 8;
      *((_DWORD *)result + 8) = v5;
      *((_DWORD *)result + 9) = v6;
      *((_DWORD *)result + 6) = v19;
    } while ( v5 <= 0x8000 );
  }
  return result;
}

int64_t pitch_downsample(_QWORD *a1, _WORD *a2, unsigned int a3)
{
  uint64_t v3; // x22
  unsigned int v4; // w20
  _WORD *v5; // x19
  _QWORD *v6; // x21
  int64_t v7; // x9
  int64_t v8; // x10
  int v9; // w11
  int v10; // w12
  int v11; // w9
  int v12; // w12
  int v13; // w8
  int32x2_t v14; // d0
  uint64_t *v15; // x11
  int32x2_t v16; // d1
  int32x2_t v17; // d2
  int64_t v18; // x12
  int32x2_t v19; // d3
  int32x2_t v20; // d4
  int32x2_t v21; // d5
  int32x2_t v22; // d2
  int32x2_t v23; // d0
  int64_t v24; // x13
  int *v25; // x9
  int v26; // w10
  int v27; // t1
  int64_t v28; // x10
  int64_t v29; // x11
  int v30; // w13
  int32x2_t v31; // d0
  uint64_t *v32; // x12
  int32x2_t v33; // d1
  int32x2_t v34; // d2
  int64_t v35; // x13
  int32x2_t v36; // d3
  int32x2_t v37; // d4
  int32x2_t v38; // d5
  int32x2_t v39; // d2
  int32x2_t v40; // d0
  int64_t v41; // x8
  int *v42; // x10
  int v43; // w11
  int v44; // t1
  int64_t v45; // x0
  int v46; // w0
  _DWORD *v47; // x10
  _DWORD *v48; // x11
  int v49; // w8
  uint64_t v50; // x9
  int64_t v51; // x12
  uint64_t v52; // x12
  uint64_t v53; // x12
  int64_t v54; // x16
  uint64_t v55; // x16
  const float *v56; // x13
  const float *v57; // x14
  int16x4_t *v58; // x15
  int32x4_t v59; // q0
  const float *v60; // x17
  __uint128_t v61; // q1
  const float *v62; // x17
  __uint128_t v63; // q5
  int *v64; // x10
  _DWORD *v65; // x11
  int v66; // w13
  int v67; // w17
  int v68; // w14
  int32x2_t v69; // d0
  int32x2_t v70; // d2
  uint32x4_t v71; // q0
  uint32x4_t v72; // q1
  int v73; // w12
  int v74; // w11
  int v75; // w8
  int v76; // w9
  int v77; // w10
  int64_t result; // x0
  int v79; // w1
  uint16x4_t v80; // [xsp+8h] [xbp-48h]
  int32x2_t v81; // [xsp+10h] [xbp-40h]
  int64_t v82; // [xsp+18h] [xbp-38h]
  int v83; // [xsp+20h] [xbp-30h]
  int64_t v84; // [xsp+28h] [xbp-28h]
  float32x4x2_t v85; // 0:q3.16,16:q4.16
  float32x4x2_t v86; // 0:q16.16,16:q17.16

  v3 = _ReadStatusReg(ARM64_SYSREG(3, 3, 13, 0, 2));
  v4 = a3;
  v5 = a2;
  v6 = a1;
  v84 = *(_QWORD *)(v3 + 40);
  v81 = ZERO32x2;
  v82 = 0LL;
  v83 = 0;
  if ( (signed int)a3 <= 0 )
  {
    v11 = 0;
    v12 = 0;
    v13 = 0;
    goto LABEL_29;
  }
  v7 = *a1;
  if ( a3 >= 4 )
  {
    v8 = a3 & 0xFFFFFFFC;
    v14 = ZERO32x2;
    v15 = (uint64_t *)(v7 + 8);
    v16 = ZERO32x2;
    v17 = ZERO32x2;
    v18 = a3 & 0xFFFFFFFC;
    v19 = ZERO32x2;
    do
    {
      v20 = vdup_n_s32(*(v15 - 1));
      v21 = vdup_n_s32(*v15);
      v18 -= 4LL;
      v15 += 2;
      v17 = vmax_s32(v17, v20);
      v19 = vmax_s32(v19, v21);
      v14 = vmin_s32(v14, v20);
      v16 = vmin_s32(v16, v21);
    }
    while ( v18 );
    v22 = vmax_s32(v17, v19);
    v23 = vmin_s32(v14, v16);
    v10 = vget_lane_s32(vmax_s32(v22, vdup_lane_s32(v22, 1)), 0);
    v9 = vget_lane_s32(vmin_s32(v23, vdup_lane_s32(v23, 1)), 0);
    if ( v8 == a3 )
      goto LABEL_14;
  }
  else
  {
    v8 = 0LL;
    v9 = 0;
    v10 = 0;
  }
  v24 = a3 - v8;
  v25 = (int *)(v7 + 4 * v8);
  do
  {
    v27 = *v25;
    ++v25;
    v26 = v27;
    if ( v10 <= v27 )
      v10 = v26;
    if ( v9 >= v26 )
      v9 = v26;
    --v24;
  }
  while ( v24 );
LABEL_14:
  v28 = a1[1];
  if ( v10 <= -v9 )
    v11 = -v9;
  else
    v11 = v10;
  if ( a3 < 4 )
  {
    v29 = 0LL;
    v30 = 0;
    v12 = 0;
    goto LABEL_22;
  }
  v29 = a3 & 0xFFFFFFFC;
  v31 = ZERO32x2;
  v32 = (uint64_t *)(v28 + 8);
  v33 = ZERO32x2;
  v34 = ZERO32x2;
  v35 = a3 & 0xFFFFFFFC;
  v36 = ZERO32x2;
  do
  {
    v37 = vdup_n_s32(*(v32 - 1));
    v38 = vdup_n_s32(*v32);
    v35 -= 4LL;
    v32 += 2;
    v34 = vmax_s32(v34, v37);
    v36 = vmax_s32(v36, v38);
    v31 = vmin_s32(v31, v37);
    v33 = vmin_s32(v33, v38);
  }
  while ( v35 );
  v39 = vmax_s32(v34, v36);
  v40 = vmin_s32(v31, v33);
  v12 = vget_lane_s32(vmax_s32(v39, vdup_lane_s32(v39, 1)), 0);
  v30 = vget_lane_s32(vmin_s32(v40, vdup_lane_s32(v40, 1)), 0);
  if ( v29 != a3 ) {
LABEL_22:
    v41 = a3 - v29;
    v42 = (int *)(v28 + 4 * v29);
    do
    {
      v44 = *v42;
      ++v42;
      v43 = v44;
      if ( v12 <= v44 )
        v12 = v43;
      if ( v30 >= v43 )
        v30 = v43;
      --v41;
    }
    while ( v41 );
  }
  v13 = -v30;
LABEL_29:
  if ( v12 > v13 )
    v13 = v12;
  if ( v11 > v13 )
    v13 = v11;
  if ( v13 <= 1 )
    v45 = 1LL;
  else
    v45 = (unsigned int)v13;
  v46 = ec_ilog(v45);
  v47 = (_DWORD *)*v6;
  v48 = (_DWORD *)v6[1];
  v49 = (((((v46 << 16) - 0x10000) >> 16) - 10) & ~(((((v46 << 16) - 0x10000) >> 16) - 10) >> 31)) + 1;
  *v5 = ((*v48 + (v48[1] >> 1)) >> 1 >> (((((unsigned int)((v46 << 16) - 0x10000) >> 16) - 10) & ~(((((v46 << 16) - 0x10000) >> 16)
                                                                                                  - 10) >> 31))
                                       + 1))
      + ((*(_DWORD *)*v6 + (*(_DWORD *)(*v6 + 4LL) >> 1)) >> 1 >> (((((unsigned int)((v46 << 16) - 0x10000) >> 16) - 10) & ~(((((v46 << 16) - 0x10000) >> 16) - 10) >> 31))
                                                                 + 1));
  if ( (signed int)v4 >= 4 )
  {
    v50 = v4 >> 1;
    v51 = 2LL;
    if ( (unsigned int)v50 > 2 )
      v51 = v4 >> 1;
    v52 = v51 - 1;
    if ( v52 >= 5 )
    {
      v54 = v52 & 3;
      if ( !(v52 & 3) )
        v54 = 4LL;
      v55 = v52 - v54;
      v56 = (const float *)(v48 + 2);
      v57 = (const float *)(v47 + 2);
      v58 = (int16x4_t *)(v5 + 1);
      v53 = v55 + 1;
      v59 = vnegq_s32(
              vdupq_n_s32(
                (((((v46 << 16) - 0x10000) >> 16) - 10) & (unsigned int)~(((((v46 << 16) - 0x10000) >> 16) - 10) >> 31))
              + 1));
      do
      {
        v60 = v57 - 1;
        v61 = (__uint128_t)*v60;
        v62 = v56 - 1;
        v85 = vld2q_f32(v57);
        v57 += 8;
        v63 = (__uint128_t)*v62;
        v86 = vld2q_f32(v56);
        v56 += 8;
        v55 -= 4LL;
        /*v58 = vmovn_s32(
                vaddq_s32(
                  vshlq_s32(
                    vshrq_n_s32(vsraq_n_s32(v86, vaddq_s32(v86, (int32x4_t)v63), 1uLL), 1uLL),
                    v59),
                  vshlq_s32(
                    vshrq_n_s32(vsraq_n_s32(v85, vaddq_s32(v85, (int32x4_t)v61), 1uLL), 1uLL),
                    v59)));*/
        ++v58;
      }
      while ( v55 );
    }
    else
    {
      v53 = 1LL;
    }
    v64 = &v47[2 * v53];
    v65 = &v48[2 * v53];
    do
    {
      v66 = *(v64 - 1);
      v67 = *v64;
      v68 = v64[1];
      v64 += 2;
      v5[v53++] = ((*v65 + ((v65[1] + *(v65 - 1)) >> 1)) >> 1 >> v49) + ((v67 + ((v68 + v66) >> 1)) >> 1 >> v49);
      v65 += 2;
    }
    while ( v53 < v50 );
  }
  _ssc_autocorr(v5, &v81);
  LODWORD(v82) = v82 - ((signed int)v82 >> 12);
  v69 = vshl_s32(v81, vdup_n_s32(-60129542157LL));
  v70 = vadd_s32(v81, v69);
  HIDWORD(v82) = HIDWORD(v82) - 36 * (SHIDWORD(v82) >> 16) - (18 * (unsigned int)WORD2(v82) >> 15);
  v70 = vsub_s32(v81, v69);
  v81 = v70;
  v83 -= v83 >> 10;
  _ssc_lpc(&v80, &v81);
  v71 = vmull_u16(v80, (uint16x4_t)6050688686405481266LL);
  v72 = vshrq_n_u32(v71, 0xFuLL);
  v73 = (int16_t)*v5;
  v74 = 0;
  v75 = 0;
  v76 = 0;
  v77 = 0;
  result = 1LL;
  v80 = vshrn_n_u32(v71, 0xFuLL);
  do
  {
    v79 = (int16_t)v5[result];
    int16x8_t v72_int16 = vreinterpretq_s16_u16(vreinterpretq_u16_u32(v72));

    uint32x4_t v5vc = vdupq_n_u32(v75 * (int16_t)(vgetq_lane_u32(v72, 3) + ((26214 * (int16_t)vgetq_lane_u32(v72, 3)) >> 15)));
    uint32x4_t temp1 = vdupq_n_u32(v75 * (int16_t)(vgetq_lane_u32(v72, 3) + ((26214 * (int16_t)vgetq_lane_u32(v72, 3)) >> 15)));
    uint32x4_t temp2 = vdupq_n_u32(v74 * (52428 * (int16_t)vgetq_lane_u32(v72, 3) >> 16));
    uint32x4_t temp3 = vdupq_n_u32(v76 * (int16_t)(vgetq_lane_u32(v72, 3) + ((26214 * (int16_t)vgetq_lane_u32(v72, 2)) >> 15)));
    uint32x4_t temp4 = vdupq_n_u32(v77 * (int16_t)(vgetq_lane_u32(v72, 3) + ((26214 * (int16_t)vgetq_lane_u32(v72, 0)) >> 15)));
    uint32x4_t temp5 = vdupq_n_u32(v73 * ((vgetq_lane_u32(v72, 0) << 16 + 214761472) >> 16));
    uint32x4_t temp6 = vshlq_n_u32(vdupq_n_u32(v79), 12);
    uint32x4_t offset = vdupq_n_u32(2048);

    v5vc = vaddq_u32(v5vc, temp1);
    v5vc = vaddq_u32(v5vc, temp2);
    v5vc = vaddq_u32(v5vc, temp3);
    v5vc = vaddq_u32(v5vc, temp4);
    v5vc = vaddq_u32(v5vc, temp5);
    v5vc = vaddq_u32(v5vc, temp6);
    v5vc = vaddq_u32(v5vc, offset);

    v5vc = vshrq_n_u32(v5vc, 12);


    // Store the result back to memory
    vst1q_u32(&v5[result], v5vc);
      
    ++result;
    v74 = v75;
    v75 = v76;
    v76 = v77;
    v77 = v73;
    v73 = v79;
  }
  while ( result != 944 );
  *(_QWORD *)(v3 + 40);
  return result * 2;
}

int64_t ssc_encode(int *a1, uint64_t *a2, int a3, int64_t a4, int a5) {
  uint64_t v5; // x27
  int64_t v6; // x8
  int v7; // w19
  int64_t v8; // x28
  int v9; // w25
  uint64_t *v10; // x20
  int *v11; // x22
  int v12; // w21
  int64_t v13; // x0
  char v14; // w8
  char v15; // w8
  int64_t v16; // x0
  int v17; // w11
  int v18; // w10
  int16_t v19; // w8
  _BOOL4 v20; // w23
  int v21; // w8
  int v22; // w9
  int v23; // w22
  _BOOL4 v24; // w24
  int v25; // w8
  int v26; // w26
  int v27; // w21
  int64_t v28; // x0
  const float *v29; // x2
  int64_t result; // x0
  int v31; // w19
  _DWORD *v32; // x28
  int v33; // w22
  int v34; // w0
  int v35; // w8
  int v36; // w19
  int v37; // w10
  int v38; // w8
  int v39; // w8
  int64_t v40; // x9
  int64_t v41; // x11
  int32x2_t v42; // w13
  int v43; // w12
  int64_t v44; // x10
  int32x2_t v45; // w12
  int32x2_t v46; // w11
  int32x2_t v47; // s0
  int64_t *v48; // x12
  int32x2_t v49; // s1
  int32x2_t v50; // s2
  int64_t v51; // x13
  int32x2_t v52; // s3
  int64_t v53; // d4
  int64_t v54; // d5
  int32x2_t v55; // s2
  int32x2_t v56; // s0
  int64_t v57; // x10
  int *v58; // x11
  int v59; // w14
  int v60; // t1
  int v61; // w10
  int32x2_t v62; // s0
  int64_t *v63; // x11
  int32x2_t v64; // s1
  int32x2_t v65; // s2
  int64_t v66; // x12
  int32x2_t v67; // s3
  int64_t v68; // d4
  int64_t v69; // d5
  int32x2_t v70; // s2
  int32x2_t v71; // s0
  int64_t v72; // x8
  int32x2_t *v73; // x10
  int32x2_t v74; // w13
  int32x2_t v75; // t1
  int64_t v76; // x10
  int64_t v77; // x11
  int32x2_t v78; // w13
  int32x2_t v79; // w12
  int v80; // w9
  int32x2_t v81; // s0
  int32x2_t v82; // s1
  int32x2_t v83; // s2
  int64_t *v84; // x12
  int64_t v85; // x13
  int32x2_t v86; // s3
  int64_t v87; // d4
  int64_t v88; // d5
  int32x2_t v89; // s2
  int32x2_t v90; // s0
  int64_t v91; // x10
  int32x2_t *v92; // x9
  int32x2_t v93; // w11
  int32x2_t v94; // t1
  int v95; // w23
  int v96; // w24
  int v97; // w24
  int v98; // w0
  char v99; // w8
  int64_t v100; // x10
  int v101; // w9
  int64_t v102; // x11
  int64_t v103; // x10
  int64_t v104; // x12
  int v105; // w11
  int *v106; // x10
  int v107; // w13
  int v108; // w13
  int v109; // w1
  int64_t v110; // x9
  int64_t v111; // x10
  int64_t v112; // x11
  int64_t v113; // x10
  int64_t v114; // x12
  int v115; // w11
  int *v116; // x10
  int v117; // w13
  int v118; // w13
  uint64_t v119; // x28
  unsigned int v120; // w8
  int64_t v121; // x20
  _BOOL4 v122; // w24
  int v123; // w14
  unsigned int v124; // w9
  int v125; // w10
  int *v126; // x19
  long double v127; // q0
  long double v128; // q1
  long double v129; // q2
  long double v130; // q3
  int16_t v131; // w0
  int v132; // w8
  int v133; // w13
  int16_t v134; // w10
  int16_t v135; // w11
  int v136; // w10
  uint16_t v137; // w12
  int v138; // w9
  int v139; // w11
  uint64_t v140; // x9
  int v141; // w9
  int v142; // w10
  int64_t v143; // x26
  int v144; // w2
  int v145; // w19
  int64_t v146; // x20
  int v147; // w8
  int64_t v148; // x2
  int64_t v149; // x28
  int v150; // w19
  int v151; // w25
  int v152; // w24
  int64_t v153; // x28
  int v154; // w0
  char v155; // w23
  int v156; // w22
  int v157; // w20
  int v158; // w0
  unsigned int v159; // w21
  int v160; // w19
  int v161; // w23
  int64_t v162; // x8
  int64_t v163; // x9
  int64_t v164; // x11
  int64_t v165; // x8
  int64_t v166; // x9
  bool v167; // cf
  int64_t v168; // x8
  int *v169; // x11
  uint64_t v170; // x12
  int *v171; // x9
  int v172; // w19
  int64_t v173; // x20
  char v174; // w8
  int64_t v175; // x10
  _BOOL4 v176; // w21
  int64_t v177; // x8
  int64_t v178; // x19
  unsigned int v179; // w21
  int64_t v180; // x24
  int64_t v181; // STF8_8
  int64_t v182; // ST118_8
  int64_t v183; // ST58_8
  int64_t v184; // ST88_8
  int64_t v185; // ST50_8
  int64_t v186; // ST48_8
  int64_t v187; // x19
  char *v188; // x27
  uint64_t v189; // x23
  int64_t v190; // x8
  int64_t v191; // x8
  int64_t v192; // x9
  int64_t v193; // x11
  int64_t v194; // x8
  int64_t v195; // x9
  int64_t v196; // x8
  int *v197; // x11
  uint64_t v198; // x12
  int *v199; // x9
  uint64_t v200; // x14
  char v201; // w13
  int v202; // w15
  int64_t v203; // x16
  _DWORD *v204; // x14
  int v205; // w17
  int v206; // w0
  uint64_t v207; // x14
  char v208; // w13
  int v209; // w15
  int64_t v210; // x16
  _DWORD *v211; // x14
  int v212; // w17
  int v213; // w0
  int64_t v214; // x8
  int64_t v215; // x9
  __int128_t *v216; // x10
  int64_t v217; // x11
  __int128_t v218; // q1
  __int128_t v219; // q2
  int16_t *v220; // x10
  int64_t v221; // x8
  char v222; // w8
  int64_t v223; // x11
  int v224; // w9
  char v225; // w10
  int v226; // w19
  unsigned int v227; // w21
  __int128_t v228; // q0
  int v229; // w17
  char *v230; // x6
  int v231; // w8
  int v232; // w10
  unsigned int v233; // w8
  unsigned int v234; // w26
  int64_t v235; // x22
  int64_t v236; // x8
  int v237; // w25
  int v238; // w19
  int64_t v239; // x10
  int64_t *v240; // x8
  int32x4_t v241; // s0
  int64_t v242; // x9
  int32x4_t v243; // s1
  int64_t v244; // d2
  int64_t v245; // d3
  int v246; // w8
  int16_t *v247; // x9
  int64_t v248; // x10
  int v249; // w11
  int v250; // t1
  int v251; // w20
  int v252; // w27
  uint64_t v253; // x10
  int64_t v254; // x9
  int v255; // w8
  _OWORD *v256; // x11
  int64_t v257; // x12
  int64_t v258; // x10
  int16_t *v259; // x21
  _QWORD *v260; // x20
  int64_t *v261; // x8
  int32x4_t v262; // s0
  int64_t v263; // x9
  int32x4_t v264; // s1
  int64_t v265; // d2
  int64_t v266; // d3
  int64_t v267; // x9
  int v268; // w10
  int v269; // t1
  int v270; // w8
  bool v271; // nf
  uint8_t v272; // vf
  bool v273; // zf
  unsigned int v274; // w24
  unsigned int v275; // w28
  int16_t *v276; // x21
  _QWORD *v277; // x23
  int64_t *v278; // x8
  int32x4_t v279; // s0
  int64_t v280; // x9
  int32x4_t v281; // s1
  int64_t v282; // d2
  int64_t v283; // d3
  int v284; // w8
  int64_t v285; // x9
  int v286; // w10
  int v287; // t1
  int v288; // w8
  int16_t *v289; // x21
  _QWORD *v290; // x23
  int64_t *v291; // x8
  int32x4_t v292; // s0
  int64_t v293; // x9
  int32x4_t v294; // s1
  int64_t v295; // d2
  int64_t v296; // d3
  int v297; // w8
  int64_t v298; // x9
  int v299; // w10
  int v300; // t1
  unsigned int v301; // w9
  int v302; // w8
  bool v303; // nf
  uint8_t v304; // vf
  int v305; // w21
  unsigned int v306; // w28
  bool v307; // zf
  bool v308; // nf
  unsigned int v309; // w28
  bool v310; // zf
  bool v311; // nf
  int v312; // w8
  int16x4_t *v313; // x4
  int v314; // w5
  int64_t v315; // x11
  int v316; // w12
  int64_t v317; // x9
  int v318; // w14
  int v319; // w15
  int *v320; // x16
  int64_t v321; // x17
  int v322; // w13
  int v323; // w2
  int v324; // t1
  int v325; // w1
  int v326; // w0
  int v327; // w0
  int v328; // w15
  int *v329; // x17
  int v330; // w14
  int v331; // w16
  int64_t v332; // x0
  int v333; // w3
  int v334; // t1
  int v335; // w2
  int v336; // w1
  int v337; // w1
  _BOOL4 v338; // w8
  _BOOL4 v339; // w12
  int v340; // w25
  int64_t v341; // x8
  int v342; // w11
  int v343; // w12
  int v344; // w14
  int v345; // w10
  int v346; // w11
  _DWORD *v347; // x12
  int v348; // w13
  int v349; // w15
  int v350; // w14
  bool v351; // nf
  uint8_t v352; // vf
  int v353; // w15
  int v354; // w15
  int v355; // w16
  int v356; // w13
  int v357; // w1
  int64_t v358; // x9
  int64_t *v359; // x10
  uint64_t v360; // x11
  int64_t v361; // x8
  int v362; // w11
  int64_t v363; // x10
  int *v364; // x12
  int64_t v365; // x13
  int v366; // w11
  int64_t v367; // x19
  int64_t v368; // x23
  int v369; // w24
  int64_t v370; // x25
  int v371; // w20
  unsigned int v372; // w21
  int v373; // w0
  int v374; // w12
  int v375; // w8
  int v376; // w2
  unsigned int v377; // w22
  unsigned int v378; // w23
  int v379; // w20
  int v380; // w24
  int v381; // w8
  int v382; // w26
  int v383; // w0
  int *v384; // x26
  int64_t v385; // x27
  int v386; // w9
  int v387; // w28
  int v388; // w0
  int64_t v389; // x8
  int64_t v390; // x9
  int *v391; // x10
  int64_t v392; // x12
  int v393; // w14
  int64_t v394; // x10
  int *v395; // x9
  int v396; // w19
  __int128_t v397; // q7
  int v398; // w1
  __int128_t *v399; // x19
  int64_t v400; // x20
  int64_t v401; // x9
  char *v402; // x10
  int32x4_t v403; // s0
  int32x4_t v404; // s1
  char *v405; // x11
  int64_t v406; // x12
  __int128_t *v407; // x13
  __int128_t v408; // t1
  int16x4_t v409; // h6
  int32x4_t v410; // s16
  int32x4_t v411; // s17
  int32x4_t v412; // s19
  int v413; // w13
  int64_t v414; // x15
  int16_t v415; // w16
  int v416; // w17
  int v417; // w0
  int v418; // w8
  int64_t v419; // x9
  int v420; // w10
  int64_t v421; // x13
  int *v422; // x17
  char *v423; // x2
  char *v424; // x3
  int16_t *v425; // x4
  int64_t v426; // x7
  int v427; // w6
  int64_t v428; // x5
  int64_t v429; // x7
  int16_t *v430; // x19
  int v431; // w21
  int v432; // w19
  int64_t v433; // x6
  int64_t v434; // x5
  int64_t v435; // x7
  int v436; // w21
  int v437; // w22
  int v438; // w19
  int64_t v439; // x5
  char *v440; // x5
  int64_t v441; // x6
  int *v442; // x7
  __int128_t v443; // q0
  __int128_t v444; // t1
  int64_t v445; // x6
  int v446; // w7
  int v447; // w19
  int64_t v448; // x8
  int *v449; // x15
  int64_t v450; // x16
  char *v451; // x16
  int64_t v452; // x17
  int *v453; // x0
  __int128_t v454; // q0
  __int128_t v455; // t1
  int64_t v456; // x17
  int v457; // w0
  int v458; // w1
  uint64_t v459; // x9
  int64_t v460; // x8
  uint64_t v461; // x10
  int64_t v462; // x16
  int16_t v463; // w0
  int64_t v464; // x11
  int v465; // w17
  int64_t v466; // x9
  int64_t v467; // x9
  char *v468; // x10
  int *v469; // x11
  int64_t v470; // x12
  __int128_t v471; // t1
  __int128_t v472; // q2
  int64_t v473; // x10
  int64_t v474; // x8
  char *v475; // x9
  _WORD *v476; // x10
  int v477; // t1
  int64_t v478; // x10
  char *v479; // x11
  int *v480; // x12
  int64_t v481; // x13
  __int128_t v482; // q2
  __int128_t v483; // q3
  __int128_t v484; // q4
  int32x4_t v485; // s5
  int32x4_t v486; // s5
  int32x4_t v487; // s5
  __int128_t v488; // q3
  __int128_t v489; // q6
  __int128_t v490; // q5
  int64_t v491; // x11
  int64_t v492; // x13
  int v493; // w14
  int v494; // w15
  int v495; // w16
  int v496; // w14
  int v497; // w15
  int v498; // w14
  int v499; // w15
  int v500; // w14
  int v501; // w16
  int64_t v502; // x9
  int *v503; // x10
  int64_t v504; // x11
  __int128_t v505; // q0
  __int128_t v506; // q1
  int64_t v507; // x8
  _WORD *v508; // x9
  int v509; // w14
  uint64_t v510; // x8
  int v511; // w10
  int v512; // w14
  int *v513; // x16
  int *v514; // x0
  int v515; // w17
  int v516; // w0
  int v517; // w17
  int v518; // w0
  int v519; // w2
  int v520; // w0
  int16_t *v521; // x12
  int v522; // w11
  int v523; // w10
  int v524; // w14
  int v525; // w13
  unsigned int v526; // w13
  int v527; // w9
  int v528; // w13
  int v529; // w11
  int v530; // w8
  int v531; // w10
  int v532; // w10
  int v533; // w8
  int v534; // w25
  int16_t *v535; // x11
  int v536; // w12
  int64_t v537; // x22
  int v538; // w19
  int v539; // w21
  int64_t v540; // x28
  int v541; // w23
  int v542; // w20
  int v543; // w27
  int v544; // w26
  char v545; // w2
  int v546; // w25
  int v547; // w0
  int v548; // w9
  int v549; // w8
  uint64_t v550; // x11
  int v551; // w8
  int64_t v552; // x21
  int v553; // w24
  int v554; // w9
  int v555; // w8
  uint16_t *v556; // x8
  int64_t v557; // x9
  int v558; // w11
  int v559; // w13
  int v560; // w15
  int v561; // w17
  int v562; // w14
  int v563; // w16
  int64_t v564; // x17
  int64_t v565; // x14
  int64_t *v566; // x16
  int32x4_t v567; // s0
  int32x4_t v568; // s1
  int32x4_t v569; // s2
  _QWORD *v570; // x13
  int32x4_t v571; // s3
  int64_t v572; // d4
  int64_t v573; // d5
  int64_t v574; // d6
  int16_t *v575; // x16
  int16_t *v576; // x17
  _BOOL4 v577; // w0
  int v578; // t1
  _BOOL4 v579; // w1
  int v580; // t1
  _BOOL4 v581; // w2
  _BOOL4 v582; // w3
  int v583; // w13
  int v584; // w2
  int v585; // w0
  uint16_t v586; // w8
  int v587; // w9
  unsigned int *v588; // x22
  int v589; // w0
  int v590; // w28
  int v591; // w10
  int v592; // w25
  int64_t v593; // x9
  int v594; // w25
  int v595; // w21
  int16_t *v596; // x8
  int64_t v597; // x10
  int64_t v598; // x11
  uint64_t v599; // x14
  int64_t v600; // x12
  uint64_t v601; // x11
  int32x4_t v602; // s0
  int64_t *v603; // x10
  int64_t *v604; // x13
  int32x4_t v605; // s1
  int64_t v606; // d2
  int64_t v607; // d3
  int64_t v608; // d4
  int64_t v609; // d5
  int v610; // w10
  int64_t v611; // x11
  int v612; // w13
  int16_t *v613; // x13
  int16_t *v614; // x14
  int v615; // w15
  int v616; // t1
  int v617; // t1
  int64_t v618; // x15
  int64_t v619; // x12
  int32x4_t v620; // s0
  int64_t *v621; // x13
  int64_t *v622; // x14
  int32x4_t v623; // s1
  int64_t v624; // d2
  int64_t v625; // d3
  int64_t v626; // d4
  int64_t v627; // d5
  int16_t *v628; // x14
  int16_t *v629; // x15
  int v630; // w16
  int v631; // t1
  int v632; // t1
  int v633; // w13
  int64_t v634; // x12
  int64_t v635; // x15
  int64_t v636; // x10
  int32x4_t v637; // s0
  int64_t *v638; // x11
  int64_t *v639; // x14
  int32x4_t v640; // s1
  int64_t v641; // d2
  int64_t v642; // d3
  int64_t v643; // d4
  int64_t v644; // d5
  int v645; // w11
  int16_t *v646; // x14
  int16_t *v647; // x15
  int v648; // w16
  int v649; // t1
  int v650; // t1
  int v651; // w13
  int64_t v652; // x10
  int64_t v653; // x15
  int64_t v654; // x11
  int32x4_t v655; // s0
  int64_t *v656; // x12
  int64_t *v657; // x14
  int32x4_t v658; // s1
  int64_t v659; // d2
  int64_t v660; // d3
  int64_t v661; // d4
  int64_t v662; // d5
  int v663; // w12
  int16_t *v664; // x14
  int16_t *v665; // x15
  int v666; // w16
  int v667; // t1
  int v668; // t1
  int v669; // w12
  int64_t v670; // x11
  int64_t v671; // x15
  int64_t v672; // x10
  int32x4_t v673; // s0
  int64_t *v674; // x13
  int64_t *v675; // x14
  int32x4_t v676; // s1
  int64_t v677; // d2
  int64_t v678; // d3
  int64_t v679; // d4
  int64_t v680; // d5
  int v681; // w13
  int16_t *v682; // x14
  int16_t *v683; // x15
  int v684; // w16
  int v685; // t1
  int v686; // t1
  int v687; // w12
  int64_t v688; // x10
  int64_t v689; // x15
  int64_t v690; // x11
  int32x4_t v691; // s0
  int64_t *v692; // x13
  int64_t *v693; // x14
  int32x4_t v694; // s1
  int64_t v695; // d2
  int64_t v696; // d3
  int64_t v697; // d4
  int64_t v698; // d5
  int v699; // w13
  int v700; // w13
  int16_t *v701; // x14
  int16_t *v702; // x15
  int v703; // w16
  int v704; // t1
  int v705; // t1
  int16_t v706; // w13
  int64_t v707; // x11
  int64_t v708; // x15
  int64_t v709; // x10
  int32x4_t v710; // s0
  int64_t *v711; // x12
  int64_t *v712; // x14
  int32x4_t v713; // s1
  int64_t v714; // d2
  int64_t v715; // d3
  int64_t v716; // d4
  int64_t v717; // d5
  int v718; // w12
  int v719; // w10
  int16_t *v720; // x14
  int16_t *v721; // x15
  int v722; // w16
  int v723; // t1
  int v724; // t1
  int64_t v725; // x12
  int16_t v726; // w10
  int64_t v727; // x15
  int64_t v728; // x11
  int32x4_t v729; // s0
  int64_t *v730; // x13
  int64_t *v731; // x14
  int32x4_t v732; // s1
  int64_t v733; // d2
  int64_t v734; // d3
  int64_t v735; // d4
  int64_t v736; // d5
  int v737; // w13
  int v738; // w11
  int16_t *v739; // x14
  int16_t *v740; // x15
  int v741; // w16
  int v742; // t1
  int v743; // t1
  int v744; // w11
  int64_t v745; // x13
  int v746; // w14
  int v747; // w1
  int v748; // w17
  int64_t v749; // x2
  int64_t v750; // x17
  int64_t *v751; // x0
  int32x4_t v752; // s0
  int64_t *v753; // x1
  int32x4_t v754; // s1
  int64_t v755; // d2
  int64_t v756; // d3
  int64_t v757; // d4
  int64_t v758; // d5
  int v759; // w0
  int16_t *v760; // x1
  int16_t *v761; // x2
  int v762; // w3
  int v763; // t1
  int v764; // t1
  _BOOL4 v765; // w8
  int v766; // w21
  int v767; // w20
  int16_t v768; // w0
  int v769; // w9
  int v770; // w27
  int v771; // w21
  int16_t v772; // w0
  int v773; // w9
  int v774; // w8
  unsigned int v775; // w9
  int v776; // w11
  unsigned int v777; // w12
  int64_t v778; // x13
  int32x4_t v779; // s2
  int32x4_t v780; // s0
  char *v781; // x11
  int32x4_t v782; // s1
  int64_t v783; // x14
  int32x4_t v784; // s4
  int32x4_t v785; // s7
  int v786; // w16
  int64_t v787; // x14
  char *v788; // x13
  int v789; // w15
  int v790; // t1
  int64_t v791; // x13
  int64_t v792; // x14
  int32x4_t v793; // s3
  int32x4_t v794; // s1
  int32x4_t v795; // s2
  int32x4_t v796; // s0
  char *v797; // x11
  int64_t v798; // x12
  int32x4_t v799; // s7
  int64_t v800; // x10
  char *v801; // x12
  int v802; // w13
  int v803; // t1
  int v804; // w8
  int v805; // w9
  int v806; // w10
  int16_t v807; // w9
  int v808; // w8
  int v809; // w8
  _BOOL4 v810; // w12
  _BOOL4 v811; // w13
  int v812; // w11
  int v813; // w19
  int v814; // w13
  int v815; // w24
  int v816; // w0
  int v817; // w9
  int v818; // w20
  int v819; // w8
  int v820; // w10
  int v821; // w1
  int v822; // w19
  int v823; // w20
  int v824; // w0
  int64_t v825; // x9
  _OWORD *v826; // x10
  __int128_t v827; // q0
  int64_t v828; // x11
  int64_t v829; // x8
  _WORD *v830; // x9
  int64_t v831; // x8
  int64_t v832; // x9
  uint64_t v833; // x9
  int64_t v834; // x13
  int64_t v835; // x11
  int64_t v836; // x12
  _OWORD *v837; // x11
  _OWORD *v838; // x12
  __int128_t v839; // q0
  uint64_t v840; // x13
  int64_t v841; // x9
  int64_t v842; // x10
  int64_t v843; // x12
  int64_t v844; // x8
  int64_t v845; // x11
  int64_t v846; // x9
  int64_t v847; // x8
  _WORD *v848; // x9
  int64_t v849; // x10
  int v850; // w11
  int v851; // w12
  int64_t v852; // x11
  int64_t v853; // x9
  _WORD *v854; // x10
  int64_t v855; // x8
  int v856; // w8
  int v857; // w8
  int16_t v858; // w8
  int64_t v859; // x10
  _OWORD *v860; // x11
  int64_t v861; // x12
  __int128_t v862; // q0
  __int128_t *v863; // x10
  int64_t v864; // x12
  __int128_t v865; // q0
  __int128_t v866; // q1
  _OWORD *v867; // x13
  int v868; // [xsp+50h] [xbp-570h]
  unsigned int v869; // [xsp+58h] [xbp-568h]
  int v870; // [xsp+64h] [xbp-55Ch]
  _BOOL4 v871; // [xsp+68h] [xbp-558h]
  int16_t v872; // [xsp+6Ch] [xbp-554h]
  uint64_t v873; // [xsp+70h] [xbp-550h]
  int v874; // [xsp+7Ch] [xbp-544h]
  int64_t v875; // [xsp+80h] [xbp-540h]
  int v876; // [xsp+88h] [xbp-538h]
  int v877; // [xsp+88h] [xbp-538h]
  int v878; // [xsp+90h] [xbp-530h]
  int v879; // [xsp+98h] [xbp-528h]
  int v880; // [xsp+98h] [xbp-528h]
  int64_t v881; // [xsp+A0h] [xbp-520h]
  int64_t v882; // [xsp+A8h] [xbp-518h]
  int v883; // [xsp+B0h] [xbp-510h]
  int v884; // [xsp+B4h] [xbp-50Ch]
  int v885; // [xsp+B8h] [xbp-508h]
  int v886; // [xsp+BCh] [xbp-504h]
  int64_t v887; // [xsp+C0h] [xbp-500h]
  int64_t v888; // [xsp+C8h] [xbp-4F8h]
  int16_t *v889; // [xsp+D0h] [xbp-4F0h]
  int64_t v890; // [xsp+D0h] [xbp-4F0h]
  int v891; // [xsp+DCh] [xbp-4E4h]
  int v892; // [xsp+DCh] [xbp-4E4h]
  int v893; // [xsp+E0h] [xbp-4E0h]
  int v894; // [xsp+E4h] [xbp-4DCh]
  int16_t *v895; // [xsp+E8h] [xbp-4D8h]
  int64_t v896; // [xsp+F0h] [xbp-4D0h]
  int64_t v897; // [xsp+F8h] [xbp-4C8h]
  unsigned int v898; // [xsp+F8h] [xbp-4C8h]
  int64_t v899; // [xsp+100h] [xbp-4C0h]
  int64_t v900; // [xsp+108h] [xbp-4B8h]
  uint64_t v901; // [xsp+110h] [xbp-4B0h]
  int64_t v902; // [xsp+118h] [xbp-4A8h]
  int v903; // [xsp+118h] [xbp-4A8h]
  int64_t v904; // [xsp+120h] [xbp-4A0h]
  int64_t v905; // [xsp+120h] [xbp-4A0h]
  int v906; // [xsp+128h] [xbp-498h]
  int64_t v907; // [xsp+128h] [xbp-498h]
  int64_t v908; // [xsp+128h] [xbp-498h]
  char v909; // [xsp+130h] [xbp-490h]
  int v910; // [xsp+138h] [xbp-488h]
  int v911; // [xsp+148h] [xbp-478h]
  unsigned int v912; // [xsp+150h] [xbp-470h]
  int v913; // [xsp+160h] [xbp-460h]
  int v914; // [xsp+16Ch] [xbp-454h]
  int v915; // [xsp+170h] [xbp-450h]
  int v916; // [xsp+174h] [xbp-44Ch]
  int v917; // [xsp+178h] [xbp-448h]
  int v918; // [xsp+17Ch] [xbp-444h]
  int v919; // [xsp+180h] [xbp-440h]
  int v920; // [xsp+184h] [xbp-43Ch]
  int v921; // [xsp+188h] [xbp-438h]
  int v922; // [xsp+18Ch] [xbp-434h]
  int v923; // [xsp+190h] [xbp-430h]
  int v924; // [xsp+194h] [xbp-42Ch]
  int v925; // [xsp+198h] [xbp-428h]
  int v926; // [xsp+19Ch] [xbp-424h]
  int v927; // [xsp+1A0h] [xbp-420h]
  int v928; // [xsp+1A4h] [xbp-41Ch]
  int v929; // [xsp+1A8h] [xbp-418h]
  int v930; // [xsp+1ACh] [xbp-414h]
  int v931; // [xsp+1B0h] [xbp-410h]
  char v932; // [xsp+1B4h] [xbp-40Ch]
  int v933; // [xsp+1E0h] [xbp-3E0h]
  int v934; // [xsp+1E4h] [xbp-3DCh]
  int64_t v935; // [xsp+1F0h] [xbp-3D0h]
  int v936; // [xsp+238h] [xbp-388h]
  int v937; // [xsp+23Ch] [xbp-384h]
  int v938; // [xsp+280h] [xbp-340h]
  int v939; // [xsp+284h] [xbp-33Ch]
  int v940; // [xsp+288h] [xbp-338h]
  int v941; // [xsp+28Ch] [xbp-334h]
  __int128_t v942; // [xsp+290h] [xbp-330h]
  __int128_t v943; // [xsp+2A0h] [xbp-320h]
  __int128_t v944; // [xsp+2B0h] [xbp-310h]
  __int128_t v945; // [xsp+2C0h] [xbp-300h]
  __int128_t v946; // [xsp+2D0h] [xbp-2F0h]
  int64_t v947; // [xsp+2E0h] [xbp-2E0h]
  char v948; // [xsp+2F0h] [xbp-2D0h]
  int16_t v949; // [xsp+348h] [xbp-278h]
  int16_t v950; // [xsp+34Ah] [xbp-276h]
  int16_t v951; // [xsp+34Ch] [xbp-274h]
  int64_t v952; // [xsp+358h] [xbp-268h]
  char v953[88]; // [xsp+3A0h] [xbp-220h]
  int *v954; // [xsp+3F8h] [xbp-1C8h]
  int *v955; // [xsp+400h] [xbp-1C0h]
  char v956[92]; // [xsp+4A8h] [xbp-118h]
  int v957[23]; // [xsp+504h] [xbp-BCh]
  int64_t v958; // [xsp+560h] [xbp-60h]

  v5 = _ReadStatusReg(ARM64_SYSREG(3, 3, 13, 0, 2));
  v958 = *(_QWORD *)(v5 + 40);
  v947 = 0LL;
  v945 = 0u;
  v946 = 0u;
  v943 = 0u;
  v944 = 0u;
  v942 = 0u;
  v6 = a1[3];
  v915 = 0;
  v7 = a1[27];
  v896 = v6;
  v8 = a4;
  v9 = a3;
  v10 = a2;
  v11 = a1;
  a1[5] = *(_DWORD *)(*(_QWORD *)a1 + 8LL);
  a1[26] = a5;
  *(_WORD *)a4 = -4353;
  v906 = a5;
  v884 = a5 > 192000;
  if ( a5 > 255999 )
  {
    if ( a5 <= 327999 )
    {
      if ( a5 == 256000 )
      {
        *(_BYTE *)(a4 + 3) = -10;
        set_DRC_limit_gain(7993344LL);
        v17 = 0;
        v11[26] = 256000;
        goto LABEL_37;
      }
      v12 = 291000;
      if ( a5 == 291000 )
      {
        v14 = -32;
      }
      else
      {
        v12 = 308000;
        if ( a5 != 308000 )
          goto LABEL_43;
        v14 = -31;
      }
    }
    else
    {
      if ( a5 <= 583999 )
      {
        if ( a5 != 328000 )
        {
          v12 = 442000;
          if ( a5 != 442000 )
            goto LABEL_43;
          v14 = -30;
          goto LABEL_41;
        }
        *(_BYTE *)(a4 + 3) = -11;
        set_DRC_limit_gain(8080384LL);
        v17 = 0;
        v11[26] = 328000;
LABEL_37:
        v18 = 1;
        goto LABEL_46;
      }
      v12 = 584000;
      if ( a5 == 584000 )
      {
        v14 = -29;
      }
      else
      {
        v12 = 886000;
        if ( a5 != 886000 )
          goto LABEL_43;
        v14 = -28;
      }
    }
LABEL_41:
    *(_BYTE *)(a4 + 3) = v14;
    v16 = 8080384LL;
    goto LABEL_42;
  }
  if ( a5 <= 151999 )
  {
    switch ( a5 )
    {
      case 88000:
        *(_BYTE *)(a4 + 3) = -16;
        if ( v7 != 24 )
          goto LABEL_39;
        break;
      case 96000:
        *(_BYTE *)(a4 + 3) = -15;
        if ( v7 != 24 )
        {
LABEL_39:
          v13 = 30450LL;
          goto LABEL_45;
        }
        break;
      case 128000:
        *(_BYTE *)(a4 + 3) = -14;
        if ( v7 == 24 )
          v13 = 7910400LL;
        else
          v13 = 30900LL;
        goto LABEL_45;
      default:
        goto LABEL_43;
    }
    v13 = 7795200LL;
    goto LABEL_45;
  }
  if ( a5 > 228999 )
  {
    if ( a5 == 229000 )
    {
      *(_BYTE *)(a4 + 3) = -12;
      if ( v7 != 24 )
        goto LABEL_7;
LABEL_32:
      v13 = 8033280LL;
      goto LABEL_45;
    }
    v12 = 250000;
    if ( a5 == 250000 )
    {
      v15 = -27;
LABEL_29:
      v16 = 7993344LL;
      *(_BYTE *)(a4 + 3) = v15;
LABEL_42:
      set_DRC_limit_gain(v16);
      v11[26] = v12;
      v18 = 1;
      v17 = 1;
      goto LABEL_46;
    }
LABEL_43:
    v18 = 0;
    v17 = 0;
    *(_BYTE *)(a4 + 3) = -13;
    goto LABEL_46;
  }
  v12 = 152000;
  if ( a5 == 152000 )
  {
    v15 = -26;
    goto LABEL_29;
  }
  if ( a5 != 192000 )
    goto LABEL_43;
  *(_BYTE *)(a4 + 3) = -13;
  if ( v7 == 24 )
    goto LABEL_32;
LABEL_7:
  v13 = 31380LL;
LABEL_45:
  set_DRC_limit_gain(v13);
  v18 = 0;
  v17 = 0;
LABEL_46:
  v891 = v17;
  v19 = 16 * *((_WORD *)v11 + 106);
  *(_BYTE *)(v8 + 2) = v19;
  *(_BYTE *)(v8 + 2) = v19 & 0xFC | *((_WORD *)v11 + 107) & 3;
  if ( v17 )
    *(_BYTE *)(v8 + 1) = ((uint8_t)*((_WORD *)v11 + 106) >> 4) | 0xE0;
  v20 = v18 != 0;
  v21 = v11[26] * v9;
  v22 = 8 * v11[24];
  v900 = (int64_t)v11;
  v23 = v18;
  v24 = v7 == 24;
  v25 = v21 / v22;
  if ( !v18 )
    v25 += 3 * v25 >> 7;
  v26 = (~v25 & 1) + v25;
  v27 = v26 - 1;
  ec_enc_init((int64_t)&v909, v8 + 4, v26 - 1);
  v886 = v23;
  if ( v23 )
  {
    Biquad_Narrow_int2int_stereo(pcmpower, v10, (const float *)&coeffs96andbelow, v900 + 216, v9, 0, 0);
    powercalc(pcmpower, v9, &v954);
    powercalc((int *)v10, v9, v957);
    v28 = (unsigned int)CalculateLimitGain((int)v954, v957[0], v906, *(_DWORD *)(v900 + 100)) << 8;
  }
  else
  {
    if ( v906 > 96000 )
      v29 = (const float *)&coeffs;
    else
      v29 = (const float *)&coeffs96andbelow;
    Biquad_Narrow_int2int_stereo(pcmpower, v10, v29, v900 + 216, v9, 0, 0);
    powercalc(pcmpower, v9, &v954);
    powercalc((int *)v10, v9, v957);
    v957[0] -= (int)v954;
    LODWORD(v28) = CalculateLimitGain((int)v954, v957[0], v906, *(_DWORD *)(v900 + 100));
    if ( v7 == 24 )
      v28 = (unsigned int)((_DWORD)v28 << 8);
    else
      v28 = (unsigned int)v28;
  }
  set_DRC_limit_gain(v28);
  // zeros have been set as second argument because it wasn't specified any value
  SoundBooster_DRC_Exe((float *)v10, v9 >> 3, 0);
  SoundBooster_DRC_Exe((float *)v10 + (v9 >> 2), v9 >> 3, 0);
  SoundBooster_DRC_Exe((float *)&v10[v9 >> 2], v9 >> 3, 0);
  SoundBooster_DRC_Exe((float *)v10 + 3 * (v9 >> 2), v9 >> 3, 0);
  SoundBooster_DRC_Exe((float *)&v10[2 * (v9 >> 2)], v9 >> 3, 0);
  SoundBooster_DRC_Exe((float *)v10 + 5 * (v9 >> 2), v9 >> 3, 0);
  SoundBooster_DRC_Exe((float *)&v10[3 * (v9 >> 2)], v9 >> 3, 0);
  SoundBooster_DRC_Exe((float *)v10 + 7 * (v9 >> 2), v9 >> 3, 0);
  ec_enc_shrink((int64_t)&v909, v27);
  result = 0xFFFFFFFFLL;
  if ( !v10 || v26 < 3 )
    goto LABEL_909;
  v875 = v8;
  v31 = v911;
  v32 = *(_DWORD **)v900;
  v903 = *(_DWORD *)(v900 + 8);
  v33 = *(_DWORD *)(*(_QWORD *)v900 + 4LL);
  v878 = *(_DWORD *)(*(_QWORD *)v900 + 8LL);
  v895 = *(int16_t **)(*(_QWORD *)v900 + 16LL);
  v34 = ec_ilog(v912);
  v35 = *(_DWORD *)(v900 + 24);
  if ( v27 >= 1275 )
    v27 = 1275;
  v36 = v31 - v34;
  v901 = (uint64_t)v32;
  if ( v35 == -1 )
  {
    v893 = v27;
  }
  else
  {
    if ( v36 <= 1 )
      v37 = 0;
    else
      v37 = v36;
    v38 = (v37 + v35 * v9 + 4 * *v32) / (8 * *v32) - 1;
    if ( v27 < v38 )
      v38 = v27;
    if ( v38 <= 2 )
      v38 = 2;
    v893 = v38;
  }
  v899 = *(unsigned int *)(v900 + 20);
  v39 = *(_DWORD *)(v900 + 76);
  LODWORD(v40) = (v9 - v33) * v896;
  if ( (int)v40 < 1 )
  {
    if ( v39 > 0 )
      goto LABEL_105;
LABEL_76:
    if ( (int)v40 < 1 )
    {
      v46 = ZERO32x2;
      v39 = 0;
      goto LABEL_103;
    }
    if ( (unsigned int)v40 >= 4 )
    {
      v44 = (unsigned int)v40 & 0xFFFFFFFC;
      v62 = ZERO32x2;
      v63 = (int64_t *)(v10 + 1);
      v64 = ZERO32x2;
      v65 = ZERO32x2;
      v66 = (unsigned int)v40 & 0xFFFFFFFC;
      v67 = ZERO32x2;
      do
      {
        v68 = *(v63 - 1);
        v69 = *v63;
        v66 -= 4LL;
        v63 += 2;
        v65 = vmax_s32(v65, vdup_n_s32(v68));
        v67 = vmax_s32(v67, vdup_n_s32(v69));
        v62 = vmin_s32(v62, vdup_n_s32(v68));
        v64 = vmin_s32(v64, vdup_n_s32(v69));
      }
      while ( v66 );
      v70 = vmax_s32(v65, v67);
      v71 = vmin_s32(v62, v64);
      v46 = vmax_s32(v70, vdup_lane_s32(v70, 1));
      v45 = vmin_s32(v71, vdup_lane_s32(v71, 1));
      if ( v44 == (unsigned int)v40 )
      {
LABEL_102:
        v39 = -(int64_t)v45;
LABEL_103:
        if ( (int64_t)v46 > v39 )
          v39 = (int64_t)v46;
        goto LABEL_105;
      }
    }
    else
    {
      v44 = 0LL;
      v45 = ZERO32x2;
      v46 = ZERO32x2;
    }
    v72 = (unsigned int)v40 - v44;
    v73 = (int32x2_t *)((char *)v10 + 4 * v44);
    do
    {
      v75 = *v73;
      ++v73;
      v74 = v75;
      uint32x2_t is_greater = vcge_s32(v75, v46);
      uint32x2_t is_less = vcle_s32(v75, v45);
      bool res_is_less = vget_lane_u32(is_less, 0) & vget_lane_u32(is_less, 1);
      bool res_is_greater = vget_lane_u32(is_greater, 0) & vget_lane_u32(is_greater, 1);
      if (res_is_less == 0xFFFFFFFF)
        v46 = v74;
      if (res_is_greater == 0xFFFFFFFF)
        v45 = v74;
      --v72;
    }
    while ( v72 );
    goto LABEL_102;
  }
  if ( (unsigned int)v40 >= 4 )
  {
    v41 = (unsigned int)v40 & 0xFFFFFFFC;
    v47 = ZERO32x2;
    v48 = (int64_t *)(v10 + 1);
    v49 = ZERO32x2;
    v50 = ZERO32x2;
    v51 = (unsigned int)v40 & 0xFFFFFFFC;
    v52 = ZERO32x2;
    do
    {
      v53 = *(v48 - 1);
      v54 = *v48;
      v51 -= 4LL;
      v48 += 2;
      v50 = vmax_s32(v50, vdup_n_s32(v53));
      v52 = vmax_s32(v52, vdup_n_s32(v54));
      v47 = vmin_s32(v47, vdup_n_s32(v53));
      v49 = vmin_s32(v49, vdup_n_s32(v54));
    }
    while ( v51 );
    v55 = vmax_s32(v50, v52);
    v56 = vmin_s32(v47, v49);
    int32x2_t before_v43 = vmax_s32(v55, vdup_lane_s32(v55, 1));
    v43 = ((int64_t)vget_lane_s32(before_v43, 0) << 32) | (uint32_t)vget_lane_s32(before_v43, 1);
    v42 = vmin_s32(v56, vdup_lane_s32(v56, 1));
    if ( v41 == (unsigned int)v40 )
      goto LABEL_88;
  }
  else
  {
    v41 = 0LL;
    v42 = ZERO32x2;
    v43 = 0;
  }
  v57 = (unsigned int)v40 - v41;
  v58 = (int *)((char *)v10 + 4 * v41);
  do
  {
    v60 = *v58;
    ++v58;
    v59 = v60;
    if ( v43 <= v60 )
      v43 = v59;

    uint32x2_t greater = vcgt_s32(v42, vdup_n_s32(v59));
    if (vget_lane_u32(greater, 0) & vget_lane_u32(greater, 1)) {
      int32x2_t converted = vdup_n_s32(v59);
      v42 = vmax_s32(converted, vdup_lane_s32(converted, 1));
    }
    --v57;
  }
  while ( v57 );
LABEL_88:
  int32x2_t before_v61 = vmax_s32(v42, vdup_lane_s32(v42, 1));
  v61 = -(((int64_t)vget_lane_s32(before_v61, 0) << 32) | (uint32_t)vget_lane_s32(before_v61, 1));
  int32x2_t neg_v42 = vneg_s32(v42);
  int32x2_t v43_twice = {v43, v43};
  uint32x2_t is_greater = vcgt_s32(v43_twice, neg_v42);
  uint32_t result_mask = vget_lane_u32(is_greater, 0) | (vget_lane_u32(is_greater, 1) << 1);

  if (result_mask == 0x3)
    v61 = v43;
  if ( v39 <= v61 )
    goto LABEL_76;
LABEL_105:
  LODWORD(v76) = v33 * v896;
  v894 = 8 * v893;
  if ( v33 * (int)v896 < 1 )
  {
    v79 = ZERO32x2;
    v80 = 0;
    goto LABEL_119;
  }
  v40 = (int)v40;
  v76 = (unsigned int)v76;
  if ( (unsigned int)v76 < 4 )
  {
    v77 = 0LL;
    v78 = ZERO32x2;
    v79 = ZERO32x2;
    goto LABEL_112;
  }
  v77 = (unsigned int)v76 & 0xFFFFFFFC;
  v81 = ZERO32x2;
  v82 = ZERO32x2;
  v83 = ZERO32x2;
  v84 = (int64_t *)((char *)v10 + 4 * v40 + 8);
  v85 = (unsigned int)v76 & 0xFFFFFFFC;
  v86 = ZERO32x2;
  do
  {
    v87 = *(v84 - 1);
    v88 = *v84;
    v85 -= 4LL;
    v84 += 2;
    v83 = vmax_s32(v83, vdup_n_s32(v87));
    v86 = vmax_s32(v86, vdup_n_s32(v88));
    v81 = vmin_s32(v81, vdup_n_s32(v87));
    v82 = vmin_s32(v82, vdup_n_s32(v88));
  }
  while ( v85 );
  v89 = vmax_s32(v83, v86);
  v90 = vmin_s32(v81, v82);
  v79 = vmax_s32(v89, vdup_lane_s32(v89, 1));
  v78 = vmin_s32(v90, vdup_lane_s32(v90, 1));
  if ( v77 != v76 )
  {
LABEL_112:
    v91 = v76 - v77;
    v92 = (int32x2_t *)((char *)v10 + 4 * (v77 + v40));
    do
    {
      v94 = *v92;
      ++v92;
      v93 = v94;
      uint32x2_t is_less = vcle_s32(v79, v94);
      uint32x2_t is_greater = vcge_s32(v78, v93);
      if (vget_lane_u32(is_less, 0) & vget_lane_u32(is_less, 1))
        v79 = v93;
      if (vget_lane_u32(is_greater, 0) & vget_lane_u32(is_greater, 1))
        v78 = v93;
      --v91;
    }
    while ( v91 );
  }
  v80 = -vget_lane_s32(vneg_s32(v78), 0);
LABEL_119:
  v904 = v900 + 296;
  if ( vget_lane_s32(v79, 0) > v80 )
    v80 = vget_lane_s32(v79, 0);
  
  v95 = v24 || v20;
  if ( v39 <= v80 )
    v96 = v80;
  else
    v96 = v39;
  *(_DWORD *)(v900 + 76) = v80;
  if ( v36 == 1 )
  {
    ec_enc_bit_logp((int64_t *)&v909, v96 == 0, 15);
    if ( v96 )
    {
      v883 = 0;
      v880 = 1;
    }
    else
    {
      v97 = v911;
      v98 = ec_ilog(v912);
      v911 += v894 - v97 + v98;
      v883 = 1;
      v880 = 8 * v893;
    }
  }
  else
  {
    v883 = 0;
    v880 = v36;
  }
  if ( v95 )
    v99 = 4;
  else
    v99 = 12;
  LODWORD(v100) = *(_DWORD *)(v900 + 8);
  v101 = v36 + 4;
  v897 = v904 + 4LL * v903 * (int)v896;
  if ( v9 >= 1 )
  {
    v100 = (int)v100;
    v102 = 0LL;
    if ( v9 == 1 )
      goto LABEL_954;
    v200 = (unsigned int)v9 - 1LL;
    v201 = __CFADD__((_DWORD)v200, (_DWORD)v200) ? 1 : 0;
    if ( 2 * (v9 - 1) & 0x80000000 )
      goto LABEL_954;
    if ( v200 >> 32 )
      goto LABEL_954;
    if ( v201 & 1 )
      goto LABEL_954;
    v102 = v9 & 0xFFFFFFFE;
    v202 = 1;
    v203 = v9 & 0xFFFFFFFE;
    v204 = (_DWORD *)((char *)&in_shared + 4 * v100 + 4);
    do
    {
      v205 = v10[v202];
      v206 = *((_DWORD *)v10 + v202 * 2 - 2);
      v203 -= 2LL;
      v202 += 2;
      v108 = v205 << v99;
      *(v204 - 1) = v206 << v99;
      *v204 = v205 << v99;
      v204 += 2;
    }
    while ( v203 );
    if ( v102 != v9 )
    {
LABEL_954:
      v103 = v102 + v100;
      v104 = (unsigned int)v9 - v102;
      v105 = v102;
      v106 = (int *)((char *)&in_shared + 4 * v103);
      do
      {
        v107 = v10[v105];
        --v104;
        ++v105;
        v108 = v107 << v99;
        *v106 = v108;
        ++v106;
      }
      while ( v104 );
    }
    LODWORD(v100) = *(_DWORD *)(v900 + 8);
    v109 = v27 - (v101 >> 3);
    *(_DWORD *)(v900 + 68) = -(55706 * (v108 >> 16) + (27853 * (v108 & 0xFFF0u) >> 15));
    if ( v9 >= 1 )
      goto LABEL_137;
LABEL_142:
    v120 = *(_DWORD *)(v900 + 72);
    v119 = v5;
    goto LABEL_143;
  }
  v109 = v27 - (v101 >> 3);
  *(_DWORD *)(v900 + 68) = *(_DWORD *)(v900 + 68);
  if ( v9 < 1 )
    goto LABEL_142;
LABEL_137:
  v110 = (int64_t)v10 + 4;
  v111 = v9 + 2 * (int)v100;
  v112 = 0LL;
  if ( v9 == 1 )
    goto LABEL_955;
  v207 = (unsigned int)v9 - 1LL;
  v208 = __CFADD__((_DWORD)v207, (_DWORD)v207) ? 1 : 0;
  if ( 2 * (v9 - 1) & 0x80000000 )
    goto LABEL_955;
  if ( v207 >> 32 )
    goto LABEL_955;
  if ( v208 & 1 )
    goto LABEL_955;
  v112 = v9 & 0xFFFFFFFE;
  v209 = 2;
  v210 = v9 & 0xFFFFFFFE;
  v211 = (_DWORD *)((char *)&in_shared + 4 * v111 + 4);
  do
  {
    v212 = *(_DWORD *)(v110 + 4LL * v209);
    v213 = *(_DWORD *)(v110 + 4LL * (v209 - 2));
    v210 -= 2LL;
    v209 += 4;
    v118 = v212 << v99;
    *(v211 - 1) = v213 << v99;
    *v211 = v212 << v99;
    v211 += 2;
  }
  while ( v210 );
  if ( v112 != v9 )
  {
LABEL_955:
    v113 = v112 + v111;
    v114 = (unsigned int)v9 - v112;
    v115 = 2 * v112;
    v116 = (int *)((char *)&in_shared + 4 * v113);
    do
    {
      v117 = *(_DWORD *)(v110 + 4LL * v115);
      --v114;
      v115 += 2;
      v118 = v117 << v99;
      *v116 = v118;
      ++v116;
    }
    while ( v114 );
  }
  v119 = v5;
  v120 = -(55706 * (v118 >> 16) + (27853 * (v118 & 0xFFF0u) >> 15));
LABEL_143:
  *(_DWORD *)(v900 + 72) = v120;
  v885 = v109;
  v888 = v878;
  v121 = v9 + 1024LL;
  v122 = v109 < 25;
  v954 = pre_shared;
  v881 = v9;
  v955 = &pre_shared[v121];
  SSC_COPY32((int64_t)pre_shared, v897, 1024);
  SSC_COPY32((int64_t)&unk_2DF50, (int64_t)&in_shared + 4 * *(int *)(v900 + 8), v9);
  v890 = v897 + 4096;
  SSC_COPY32((int64_t)&pre_shared[v121], v897 + 4096, 1024);
  SSC_COPY32(
    (int64_t)&pre_shared[v121 + 1024],
    (int64_t)&in_shared + 4 * (*(_DWORD *)(v900 + 8) + v9) + 4 * *(int *)(v900 + 8),
    v9);
  if ( (v122 | v883) & 1 )
  {
    v123 = v885;
    LOWORD(v124) = 0;
    v125 = 15;
    v126 = (int *)(v900 + 56);
    v957[0] = 15;
  }
  else
  {
    pitch_downsample(&v954, (int16x4_t *)&in_shared, v121);
    pitch_search(
      (const int16_t *)&unk_2B4F0,
      (uint64_t *)&in_shared,
      v9,
      979,
      v957,
      v127,
      v128,
      v129,
      v130);
    v957[0] = 1024 - v957[0];
    v126 = (int *)(v900 + 56);
    v131 = remove_doubling(
             (int64_t)&in_shared,
             1024LL,
             15,
             v9,
             v957,
             *(_DWORD *)(v900 + 56),
             *(uint16_t *)(v900 + 60));
    v125 = v957[0];
    if ( v957[0] >= 1023 )
    {
      v125 = 1022;
      v957[0] = 1022;
    }
    v123 = v885;
    v124 = (unsigned int)(22938 * v131) >> 15;
  }
  v132 = *v126;
  v133 = v125 - *v126;
  if ( v125 - *v126 < 0 )
    v133 = !v133;
  if ( 10 * v133 <= v125 )
    v134 = 6554;
  else
    v134 = 13108;
  if ( v123 > 24 )
  {
    v135 = v134 + 3277;
    if ( v123 >= 35 )
      v135 = v134;
    v136 = *(int16_t *)(v900 + 60);
    if ( v136 < 18023 )
      goto LABEL_155;
LABEL_161:
    v135 -= 6554;
    goto LABEL_162;
  }
  v135 = v134 + 6554;
  v136 = *(int16_t *)(v900 + 60);
  if ( v136 >= 18023 )
    goto LABEL_161;
LABEL_155:
  if ( v136 > 13107 )
    v135 -= 3277;
LABEL_162:
  if ( v135 <= 6554 )
    v137 = 6554;
  else
    v137 = v135;
  v873 = v119;
  LODWORD(v882) = v878 * v896;
  if ( (int16_t)v124 >= (int)v137 )
  {
    v139 = (int16_t)v124 - v136;
    if ( v139 < 0 )
      v139 = !v139;
    if ( v139 < 3277 )
      LOWORD(v124) = v136;
    v140 = 1431655766LL * (((int16_t)v124 + 1536) >> 10);
    v141 = HIDWORD(v140) + (v140 >> 63) - 1;
    if ( v141 >= 7 )
      v141 = 7;
    v142 = v141 & ~(v141 >> 31);
    v138 = 3072 * v142 + 3072;
    v874 = 0;
    v877 = v142;
  }
  else
  {
    v138 = 0;
    v877 = 0;
    v874 = 1;
  }
  v143 = v900;
  v144 = *(_DWORD *)(v900 + 8);
  v872 = v138;
  v145 = -v138;
  if ( v132 <= 15 )
    v132 = 15;
  v887 = (int)v899;
  *(_DWORD *)(v900 + 56) = v132;
  SSC_COPY32((int64_t)&in_shared, v904, v144);
  comb_filter(
    (__int128_t *)((char *)&in_shared + 4 * *(int *)(v900 + 8)),
    (uint64_t)(v954 + 1024),
    *(_DWORD *)(v900 + 56),
    v957[0],
    v9,
    -*(uint16_t *)(v900 + 60),
    v145,
    *(_DWORD *)(v900 + 8));
  v146 = 4LL * v9;
  SSC_COPY32(v904, (int64_t)&in_shared + 4 * v9, *(_DWORD *)(v900 + 8));
  SSC_COPY32(v897, v897 + 4LL * v9, 1024 - v9);
  SSC_COPY32(v890 - 4LL * v9, (int64_t)(v954 + 1024), v9);
  v147 = *(_DWORD *)(v900 + 56);
  v148 = *(int *)(v900 + 8);
  v149 = v900 + 296;
  if ( v147 <= 15 )
    v147 = 15;
  *(_DWORD *)(v900 + 56) = v147;
  SSC_COPY32((int64_t)&in_shared + 4 * ((int)v148 + v9), v149 + 4 * v148, v148);
  comb_filter(
    (__int128_t *)((char *)&in_shared + 4 * (*(_DWORD *)(v900 + 8) + v9) + 4 * *(int *)(v900 + 8)),
    (uint64_t)(v955 + 1024),
    *(_DWORD *)(v900 + 56),
    v957[0],
    v9,
    -*(uint16_t *)(v900 + 60),
    v145,
    *(_DWORD *)(v900 + 8));
  SSC_COPY32(
    v149 + 4LL * *(int *)(v900 + 8),
    (int64_t)&in_shared + 4 * (*(_DWORD *)(v900 + 8) + v9) + v146,
    *(_DWORD *)(v900 + 8));
  SSC_COPY32(v890, v890 + v146, 1024 - v9);
  SSC_COPY32(v897 - v146 + 0x2000, (int64_t)(v955 + 1024), v9);
  v150 = v957[0];
  v870 = v957[0];
  if ( v874 )
  {
    v151 = v893;
    v152 = v896;
    v153 = v901;
    if ( v880 + 16 <= v894 )
      ec_enc_bit_logp((int64_t *)&v909, 0, 1);
  }
  else
  {
    ec_enc_bit_logp((int64_t *)&v909, 1, 1);
    v154 = ec_ilog(v150 + 1);
    v155 = v154 - 5;
    v156 = v154;
    ec_enc_uint((int64_t)&v909, v154 - 5, 6u);
    ec_enc_bits((int64_t *)&v909, v150 + 1 - (16 << v155), v156 - 1);
    ec_enc_bits((int64_t *)&v909, v877, 3);
    v152 = v896;
    v151 = v893;
    v153 = v901;
  }
  v157 = v911;
  v882 = (int)v882;
  v158 = ec_ilog(v912);
  v159 = *(_DWORD *)(v153 + 4);
  v871 = v157 + 3 - v158 > v894;
  v160 = 8 * *(_DWORD *)(v153 + 28);
  ssc_mdct_forward(v153 + 72, (int64_t)&in_shared, dword_2EDB0, *(int **)(v153 + 64), v159, 0, 1);
  ssc_mdct_forward(
    v153 + 72,
    (int64_t)&in_shared + 4 * (int)(v160 + v159),
    &dword_2EDB0[v160],
    *(int **)(v153 + 64),
    v159,
    0,
    1);
  v161 = v886;
  if ( v886 == 0 && v906 <= 191999 )
  {
    v162 = v895[(int)v899 - 1];
    if ( v162 <= 107 )
    {
      v163 = 8 * v162 | 1;
      v164 = 8 * v162;
      v165 = 864LL;
      if ( v163 > 864 )
        v165 = v163;
      v166 = v165 - v164;
      v167 = (uint64_t)(v165 - v164) >= 4;
      v168 = v164;
      if ( !v167 )
        goto LABEL_956;
      v168 = (v166 & 0xFFFFFFFFFFFFFFF8LL) + v164;
      v169 = &pre_shared[v164 + 1944];
      v170 = v166 & 0xFFFFFFFFFFFFFFF8LL;
      do
      {
        *(_OWORD *)v169 = 0uLL;
        *((_OWORD *)v169 + 216) = 0uLL;
        v170 -= 4LL;
        v169 += 4;
      }
      while ( v170 );
      if ( v166 != (v166 & 0xFFFFFFFFFFFFFFF8LL) )
      {
LABEL_956:
        v171 = &pre_shared[v168 + 1944];
        do
        {
          ++v168;
          *v171 = 0;
          v171[864] = 0;
          ++v171;
        }
        while ( v168 < 864 );
      }
    }
  }
  if ( v886 )
    uhq_headroom((int64_t)dword_2EDB0, v906, 8, (int64_t)v895);
  else
    normal_headroom((int64_t)dword_2EDB0, v906, 8, v895);
  v879 = (v903 + 1024) * v152;
  compute_band_energies(v153, (int64_t)dword_2EDB0, (int64_t)&v954, v899);
  amp2Log2(v153, v899, *(_DWORD *)(v900 + 20), (int64_t)&v954, (int64_t)v953, v152);
  if ( (int)v882 >= 1 )
    memcpy(&v949, v953, 2 * v882);
  v172 = v911;
  v889 = (int16_t *)(v904 + 4LL * v879);
  if ( (int)(v172 + 3 - (uint64_t)ec_ilog(v912)) > v894 )
  {
    v869 = 0;
    v173 = (int)v899;
    v876 = 0;
    v902 = 0LL;
    if ( v886 )
      goto LABEL_200;
LABEL_252:
    compute_band_energies_for_lastband(v153, (int64_t)dword_2EDB0, (int64_t)&v916, 4, 0, 0);
    if ( v923 + v919 <= 30001 )
    {
      if ( v922 + v918 < 30002 )
        v222 = 4 * (v921 + v917 > 30001);
      else
        v222 = 8;
    }
    else
    {
      v222 = 12;
    }
    v905 = 0LL;
    *(_BYTE *)(v875 + 2) += v222;
    goto LABEL_292;
  }
  v176 = patch_transient_decision((int64_t)v953, v904 + 4LL * v879, v878, *(_DWORD *)(v900 + 20) - previous_uhq_index);
  v177 = patch_transient_decision_temporal(v153, v900, (int64_t)&in_shared) | (unsigned int)v176;
  if ( !(_DWORD)v177 )
  {
    v869 = 0;
    v173 = (int)v899;
    v876 = 0;
    v902 = v177;
    if ( !v886 )
      goto LABEL_252;
    goto LABEL_200;
  }
  v178 = *(int *)(v153 + 28);
  v179 = *(_DWORD *)(v153 + 4);
  v180 = (unsigned int)(8 * v178);
  ssc_mdct_forward(v153 + 72, (int64_t)&in_shared, dword_2EDB0, *(int **)(v153 + 64), v179, 3, 8);
  v181 = 4 * v178;
  ssc_mdct_forward(v153 + 72, (int64_t)&in_shared + 4 * v178, &dword_2EDB0[1], *(int **)(v153 + 64), v179, 3, 8);
  v182 = 8 * v178;
  ssc_mdct_forward(v153 + 72, (int64_t)&in_shared + 8 * v178, &dword_2EDB0[2], *(int **)(v153 + 64), v179, 3, 8);
  v183 = (int64_t)((uint64_t)(unsigned int)(3 * v178) << 32) >> 30;
  ssc_mdct_forward(v153 + 72, (int64_t)&in_shared + v183, &dword_2EDB0[3], *(int **)(v153 + 64), v179, 3, 8);
  v184 = 16 * v178;
  ssc_mdct_forward(v153 + 72, (int64_t)&in_shared + 16 * v178, &dword_2EDB0[4], *(int **)(v153 + 64), v179, 3, 8);
  v185 = (int64_t)((uint64_t)(unsigned int)(5 * v178) << 32) >> 30;
  ssc_mdct_forward(v153 + 72, (int64_t)&in_shared + v185, &dword_2EDB0[5], *(int **)(v153 + 64), v179, 3, 8);
  v186 = (int64_t)((uint64_t)(unsigned int)(6 * v178) << 32) >> 30;
  ssc_mdct_forward(v153 + 72, (int64_t)&in_shared + v186, &dword_2EDB0[6], *(int **)(v153 + 64), v179, 3, 8);
  v187 = (int64_t)((uint64_t)(unsigned int)(7 * v178) << 32) >> 30;
  ssc_mdct_forward(v153 + 72, (int64_t)&in_shared + v187, &dword_2EDB0[7], *(int **)(v153 + 64), v179, 3, 8);
  v188 = (char *)&in_shared + 4 * (int)(v180 + v179);
  v189 = (uint64_t)(int)v180 >> 3;
  ssc_mdct_forward(
    v153 + 72,
    (int64_t)&in_shared + 4 * (int)(v180 + v179),
    (_DWORD *)((char *)dword_2EDB0 + (v180 << 32 >> 30)),
    *(int **)(v153 + 64),
    v179,
    3,
    8);
  ssc_mdct_forward(
    v153 + 72,
    (int64_t)&v188[v181],
    (_DWORD *)((char *)dword_2EDB0 + (32 * v189 | 4)),
    *(int **)(v153 + 64),
    v179,
    3,
    8);
  ssc_mdct_forward(
    v153 + 72,
    (int64_t)&v188[v182],
    (_DWORD *)((char *)dword_2EDB0 + (32 * v189 | 8)),
    *(int **)(v153 + 64),
    v179,
    3,
    8);
  ssc_mdct_forward(
    v153 + 72,
    (int64_t)&v188[v183],
    (_DWORD *)((char *)dword_2EDB0 + (32 * v189 | 0xC)),
    *(int **)(v153 + 64),
    v179,
    3,
    8);
  ssc_mdct_forward(
    v153 + 72,
    (int64_t)&v188[v184],
    (_DWORD *)((char *)dword_2EDB0 + (32 * v189 | 0x10)),
    *(int **)(v153 + 64),
    v179,
    3,
    8);
  ssc_mdct_forward(
    v153 + 72,
    (int64_t)&v188[v185],
    (_DWORD *)((char *)dword_2EDB0 + (32 * v189 | 0x14)),
    *(int **)(v153 + 64),
    v179,
    3,
    8);
  ssc_mdct_forward(
    v153 + 72,
    (int64_t)&v188[v186],
    (_DWORD *)((char *)dword_2EDB0 + (32 * v189 | 0x18)),
    *(int **)(v153 + 64),
    v179,
    3,
    8);
  v190 = 32 * v189 | 0x1C;
  v161 = v886;
  v152 = v896;
  ssc_mdct_forward(
    v153 + 72,
    (int64_t)&v188[v187],
    (_DWORD *)((char *)dword_2EDB0 + v190),
    *(int **)(v153 + 64),
    v179,
    3,
    8);
  v173 = (int)v899;
  if ( v886 == 0 && v906 <= 191999 )
  {
    v191 = v895[(int)v899 - 1];
    if ( v191 <= 107 )
    {
      v192 = 8 * v191 | 1;
      v193 = 8 * v191;
      v194 = 864LL;
      if ( v192 > 864 )
        v194 = v192;
      v195 = v194 - v193;
      v167 = (uint64_t)(v194 - v193) >= 4;
      v196 = v193;
      if ( !v167 )
        goto LABEL_957;
      v196 = (v195 & 0xFFFFFFFFFFFFFFF8LL) + v193;
      v197 = &pre_shared[v193 + 1944];
      v198 = v195 & 0xFFFFFFFFFFFFFFF8LL;
      do
      {
        *(_OWORD *)v197 = 0uLL;
        *((_OWORD *)v197 + 216) = 0uLL;
        v198 -= 4LL;
        v197 += 4;
      }
      while ( v198 );
      if ( v195 != (v195 & 0xFFFFFFFFFFFFFFF8LL) )
      {
LABEL_957:
        v199 = &pre_shared[v196 + 1944];
        do
        {
          ++v196;
          *v199 = 0;
          v199[864] = 0;
          ++v199;
        }
        while ( v196 < 864 );
      }
    }
  }
  if ( v886 )
    uhq_headroom((int64_t)dword_2EDB0, v906, 8, (int64_t)v895);
  else
    normal_headroom((int64_t)dword_2EDB0, v906, 8, v895);
  v151 = v893;
  v143 = v900;
  compute_band_energies(v153, (int64_t)dword_2EDB0, (int64_t)&v954, v899);
  amp2Log2(v153, v899, *(_DWORD *)(v900 + 20), (int64_t)&v954, (int64_t)v953, v896);
  LODWORD(v214) = 2 * v878;
  if ( 2 * v878 >= 1 )
  {
    v214 = (unsigned int)v214;
    if ( (unsigned int)v214 < 0x10 )
    {
      v215 = 0LL;
LABEL_249:
      v220 = &v949 + v215;
      v221 = v214 - v215;
      do
      {
        --v221;
        *v220 += 1536;
        ++v220;
      }
      while ( v221 );
      goto LABEL_251;
    }
    v215 = (unsigned int)v214 & 0xFFFFFFF0;
    v216 = (__int128_t *)&v952;
    v217 = (unsigned int)v214 & 0xFFFFFFF0;
    do
    {
      v218 = *(v216 - 1);
      v219 = *v216;
      v217 -= 16LL;
      LOWORD(v218) = v218 + 1536;
      LOWORD(v219) = *v216 + 1536;
      *(v216 - 1) = v218;
      *v216 = v219;
      v216 += 2;
    }
    while ( v217 );
    if ( v215 != v214 )
      goto LABEL_249;
  }
LABEL_251:
  v876 = 8;
  v869 = 3277;
  v902 = 1LL;
  if ( !v886 )
    goto LABEL_252;
LABEL_200:
  v905 = 4 * (unsigned int)(*(uint8_t *)(v875 + 3) == 230);
  if ( *(uint8_t *)(v875 + 3) == 230 || (v891 ^ 1) & 1 )
    goto LABEL_292;
  compute_band_energies_for_lastband(v153, (int64_t)dword_2EDB0, (int64_t)&v916, 8, v161, 0);
  if ( v931 + v923 <= 12001 )
  {
    if ( v930 + v922 <= 12001 )
    {
      if ( v929 + v921 <= 12001 )
      {
        if ( v928 + v920 <= 12001 )
        {
          if ( v927 + v919 <= 12001 )
          {
            if ( v926 + v918 <= 12001 )
            {
              if ( v925 + v917 <= 12001 )
              {
                if ( v924 + v916 <= 12001 )
                {
                  compute_band_energies_for_lastband(v153, (int64_t)dword_2EDB0, (int64_t)&v916, 8, v161, 1);
                  if ( v931 + v923 < 12002 )
                  {
                    if ( v930 + v922 <= 12001 )
                    {
                      if ( v929 + v921 <= 12001 )
                      {
                        if ( v928 + v920 <= 12001 )
                        {
                          if ( v927 + v919 > 12001 )
                          {
                            v175 = 1LL;
                            v174 = -128;
                            goto LABEL_288;
                          }
                          if ( v926 + v918 > 12001 )
                          {
                            v175 = 1LL;
                            v174 = 96;
                            goto LABEL_288;
                          }
                          if ( v925 + v917 > 12001 )
                          {
                            v175 = 1LL;
                            v174 = 64;
                            goto LABEL_288;
                          }
                          if ( v924 + v916 > 12001 )
                          {
                            v175 = 1LL;
                            goto LABEL_287;
                          }
                          compute_band_energies_for_lastband(v901, (int64_t)dword_2EDB0, (int64_t)&v916, 8, v886, 2);
                          if ( v931 + v923 > 12001 )
                          {
                            v143 = v900;
                            v153 = v901;
                            v152 = v896;
                            v151 = v893;
                            v174 = 0;
                            v175 = 2LL;
                            goto LABEL_289;
                          }
                          if ( v930 + v922 > 12001 )
                          {
                            v175 = 2LL;
                            v174 = -32;
                            goto LABEL_288;
                          }
                          if ( v929 + v921 > 12001 )
                          {
                            v175 = 2LL;
                            v174 = -64;
                            goto LABEL_288;
                          }
                          if ( v928 + v920 <= 12001 )
                          {
                            if ( v927 + v919 > 12001 )
                            {
                              v175 = 2LL;
                              v174 = -128;
                              goto LABEL_288;
                            }
                            if ( v926 + v918 > 12001 )
                            {
                              v175 = 2LL;
                              v174 = 96;
                              goto LABEL_288;
                            }
                            if ( v925 + v917 > 12001 )
                            {
                              v175 = 2LL;
                              v174 = 64;
                              goto LABEL_288;
                            }
                            if ( v924 + v916 > 12001 )
                            {
                              v175 = 2LL;
                              goto LABEL_287;
                            }
                            compute_band_energies_for_lastband(v901, (int64_t)dword_2EDB0, (int64_t)&v916, 8, v886, 3);
                            if ( v931 + v923 > 12001 )
                            {
                              v143 = v900;
                              v153 = v901;
                              v152 = v896;
                              v151 = v893;
                              v174 = 0;
                              v175 = 3LL;
                              goto LABEL_289;
                            }
                            if ( v930 + v922 > 12001 )
                            {
                              v175 = 3LL;
                              v174 = -32;
                              goto LABEL_288;
                            }
                            if ( v929 + v921 > 12001 )
                            {
                              v175 = 3LL;
                              v174 = -64;
                              goto LABEL_288;
                            }
                            if ( v928 + v920 <= 12001 )
                            {
                              if ( v927 + v919 <= 12001 )
                                goto LABEL_945;
                              v175 = 3LL;
                              v174 = -128;
                              goto LABEL_288;
                            }
                            v175 = 3LL;
                          }
                          else
                          {
                            v175 = 2LL;
                          }
                        }
                        else
                        {
                          v175 = 1LL;
                        }
                        v174 = -96;
                        goto LABEL_288;
                      }
                      v175 = 1LL;
                      v174 = -64;
                    }
                    else
                    {
                      v175 = 1LL;
                      v174 = -32;
                    }
                  }
                  else
                  {
                    v174 = 0;
                    v175 = 1LL;
                  }
                }
                else
                {
                  v175 = 0LL;
                  v174 = 32;
                }
              }
              else
              {
                v175 = 0LL;
                v174 = 64;
              }
            }
            else
            {
              v175 = 0LL;
              v174 = 96;
            }
          }
          else
          {
            v175 = 0LL;
            v174 = -128;
          }
        }
        else
        {
          v175 = 0LL;
          v174 = -96;
        }
      }
      else
      {
        v175 = 0LL;
        v174 = -64;
      }
    }
    else
    {
      v175 = 0LL;
      v174 = -32;
    }
  }
  else
  {
    v174 = 0;
    v175 = 0LL;
  }
LABEL_290:
  v223 = v875;
  v905 = v175;
  v224 = *(uint8_t *)(v875 + 2) + 4 * v175;
  while ( 1 )
  {
    v225 = *(_BYTE *)(v223 + 3);
    *(_BYTE *)(v223 + 2) = v224;
    *(_BYTE *)(v223 + 3) = (v174 - 32) | v225 & 0x1F;
LABEL_292:
    v226 = v911;
    if ( (int)(v226 + 3 - (uint64_t)ec_ilog(v912)) <= v894 )
      ec_enc_bit_logp((int64_t *)&v909, v902, 3);
    v227 = v899 - v905;
    normalise_bands(v153, (int64_t)dword_2EDB0, (int64_t)dword_2EDB0, (int64_t)&v954, v899 - v905);
    if ( v161 || v151 < 15 * v152 )
    {
      v357 = *(_DWORD *)(v143 + 20);
      if ( v357 < 1 )
      {
        v313 = v889;
        v314 = v885;
        v340 = 0;
        goto LABEL_475;
      }
      v313 = v889;
      v314 = v885;
      if ( (unsigned int)v357 > 7 )
      {
        v358 = v357 & 0xFFFFFFFFFFFFFFF8LL;
        LODWORD(v228) = v902;
        v359 = &v935;
        v360 = v357 & 0xFFFFFFFFFFFFFFF8LL;
        do
        {
          *((_OWORD *)v359 - 1) = v228;
          *(_OWORD *)v359 = v228;
          v360 -= 8LL;
          v359 += 4;
        }
        while ( v360 );
        if ( v358 == v357 )
          goto LABEL_455;
      }
      else
      {
        v358 = 0LL;
      }
      do
        *(&v933 + v358++) = v902;
      while ( v358 < v357 );
LABEL_455:
      v340 = 0;
      goto LABEL_475;
    }
    v229 = v902;
    if ( v151 < 40 )
    {
      v230 = (char *)&in_shared;
      v231 = 24;
      if ( (int)v173 >= 1 )
        goto LABEL_298;
      goto LABEL_461;
    }
    v230 = (char *)&in_shared;
    if ( v151 < 60 )
    {
      v231 = 12;
      if ( (int)v173 >= 1 )
        goto LABEL_298;
      goto LABEL_461;
    }
    if ( v151 >= 100 )
      v231 = 6;
    else
      v231 = 8;
    if ( (int)v173 >= 1 )
    {
LABEL_298:
      v868 = v231;
      if ( (_DWORD)v902 )
        v232 = 196608;
      else
        v232 = 0;
      v233 = 1311 * ((0x20000000 - (v869 << 16)) >> 16) >> 14;
      v234 = v233 << 16;
      v235 = 0LL;
      v892 = 4 * v233;
      LODWORD(v875) = v899 - v905;
      v898 = v233 * v232 >> 16;
      while ( 2 )
      {
        v236 = *(_QWORD *)(v153 + 16);
        v907 = v235 + 1;
        v237 = *(int16_t *)(v236 + 2 * (v235 + 1)) - *(int16_t *)(v236 + 2 * v235);
        v238 = 8 * v237;
        if ( v237 < 1 )
        {
          v246 = 0;
        }
        else
        {
          *(_WORD *)((char *)&qword_108 + (_QWORD)v230) = pre_shared[4 * *(int16_t *)(v236 + 2 * v235) + 1944];
          v239 = 133LL;
          do
          {
            v272 = __OFSUB__(v239 - 131, v238);
            v271 = v239 - 131 - v238 < 0;
            *(_WORD *)&v230[2 * v239] = *((_WORD *)&pre_shared[1944]
                                        + (int)v239
                                        + 8 * *(int16_t *)(v236 + 2 * v235)
                                        - 132);
            ++v239;
          }
          while ( v271 ^ v272 );
          if ( v237 )
          {
            v240 = (int64_t *)(v230 + 272);
            v241 = ZERO32x4;
            v242 = (unsigned int)(8 * v237);
            v243 = ZERO32x4;
            do
            {
              v244 = *(v240 - 1);
              v245 = *v240;
              v242 -= 8LL;
              v240 += 2;
              v241 = vaddq_s32(vabsq_s32(vmovl_s16(vdup_n_s16(v244))), v241);
              v243 = vaddq_s32(vabsq_s32(vmovl_s16(vdup_n_s16(v245))), v243);
            }
            while ( v242 );
            v246 = vaddvq_s32(vaddq_s32(v243, v241));
          }
          else
          {
            v246 = 0;
            v247 = (int16_t *)(v230 + 264);
            v248 = (unsigned int)(8 * v237);
            do
            {
              v250 = *v247;
              ++v247;
              v249 = v250;
              if ( v250 < 0 )
                v249 = !v249;
              --v248;
              v246 += v249;
            }
            while ( v248 );
          }
        }
        v251 = 0;
        v252 = v246 + ((v246 & 0x7FFF) * v898 >> 15) + (2 * v246 >> 16) * v898;
        if ( !v229 || v237 == 1 )
          goto LABEL_340;
        if ( v237 <= 0 )
        {
          haar1((_WORD *)v230 + 420, (unsigned int)v237, 8LL);
          v230 = (char *)&in_shared;
          v229 = v902;
          v255 = 0;
        }
        else
        {
          if ( v238 <= 1LL )
            v253 = 1LL;
          else
            v253 = v238;
          if ( v253 < 8 )
          {
            v254 = 0LL;
            goto LABEL_326;
          }
          v254 = v253 & 0x7FFFFFFFFFFFFFF8LL;
          v256 = v230 + 264;
          v257 = v253 & 0x7FFFFFFFFFFFFFF8LL;
          do
          {
            v257 -= 8LL;
            v256[36] = *v256;
            ++v256;
          }
          while ( v257 );
          if ( v253 != v254 )
          {
            do
            {
LABEL_326:
              v258 = (int64_t)&v230[2 * v254++];
              *(_WORD *)(v258 + 840) = *(_WORD *)(v258 + 264);
            }
            while ( v254 < v238 );
          }
          v259 = (int16_t *)(v230 + 840);
          v260 = v230;
          haar1((_WORD *)v230 + 420, (unsigned int)v237, 8LL);
          if ( v237 )
          {
            v229 = v902;
            v261 = v260 + 106;
            v262 = ZERO32x4;
            v263 = (unsigned int)(8 * v237);
            v264 = ZERO32x4;
            v230 = (char *)v260;
            do
            {
              v265 = *(v261 - 1);
              v266 = *v261;
              v263 -= 8LL;
              v261 += 2;
              v262 = vaddq_s32(vabsq_s32(vmovl_s16(vdup_n_s16(v265))), v262);
              v264 = vaddq_s32(vabsq_s32(vmovl_s16(vdup_n_s16(v266))), v264);
            }
            while ( v263 );
            v255 = vaddvq_s32(vaddq_s32(v264, v262));
          }
          else
          {
            v229 = v902;
            v255 = 0;
            v267 = (unsigned int)(8 * v237);
            v230 = (char *)v260;
            do
            {
              v269 = *v259;
              ++v259;
              v268 = v269;
              if ( v269 < 0 )
                v268 = !v268;
              --v267;
              v255 += v268;
            }
            while ( v267 );
          }
        }
        v270 = v255 + ((v255 & 0x7FFFu) * v892 >> 15) + (2 * v255 >> 16) * v892;
        v272 = __OFSUB__(v270, v252);
        v271 = v270 - v252 < 0;
        if ( v270 < v252 )
          v252 = v270;
        if ( v271 ^ v272 )
          v251 = -1;
        else
          v251 = 0;
LABEL_340:
        if ( v237 == 1 )
          v273 = 0;
        else
          v273 = v229 == 0;
        if ( v273 )
          v274 = 4;
        else
          v274 = 3;
        if ( v237 < 1 )
        {
          v305 = 0;
          if ( v229 )
          {
            do
            {
              v306 = v305 + 1;
              haar1((_WORD *)v230 + 132, (unsigned int)(v238 >> v305), (unsigned int)(1 << v305));
              v230 = (char *)&in_shared;
              v307 = v252 == 0;
              v308 = v252 < 0;
              if ( v252 > 0 )
                v252 = 0;
              if ( !v308 && !v307 )
                v251 = v305 + 1;
              ++v305;
            }
            while ( v306 < v274 );
          }
          else
          {
            do
            {
              v309 = v305 + 1;
              haar1((_WORD *)v230 + 132, (unsigned int)(v238 >> v305), (unsigned int)(1 << v305));
              v230 = (char *)&in_shared;
              v310 = v252 == 0;
              v311 = v252 < 0;
              if ( v252 > 0 )
                v252 = 0;
              if ( !v311 && !v310 )
                v251 = v305 + 1;
              ++v305;
            }
            while ( v309 < v274 );
          }
        }
        else
        {
          v275 = 0;
          if ( v229 )
          {
            do
            {
              v276 = (int16_t *)(v230 + 264);
              v277 = v230;
              haar1((_WORD *)v230 + 132, (unsigned int)(v238 >> v275), (unsigned int)(1 << v275));
              if ( v237 )
              {
                v278 = v277 + 34;
                v279 = ZERO32x4;
                v280 = (unsigned int)(8 * v237);
                v281 = ZERO32x4;
                v230 = (char *)v277;
                do
                {
                  v282 = *(v278 - 1);
                  v283 = *v278;
                  v280 -= 8LL;
                  v278 += 2;
                  v279 = vaddq_s32(vabsq_s32(vmovl_s16(vdup_n_s16(v282))), v279);
                  v281 = vaddq_s32(vabsq_s32(vmovl_s16(vdup_n_s16(v283))), v281);
                }
                while ( v280 );
                v284 = vaddvq_s32(vaddq_s32(v281, v279));
              }
              else
              {
                v284 = 0;
                v285 = (unsigned int)(8 * v237);
                v230 = (char *)v277;
                do
                {
                  v287 = *v276;
                  ++v276;
                  v286 = v287;
                  if ( v287 < 0 )
                    v286 = !v286;
                  --v285;
                  v284 += v286;
                }
                while ( v285 );
              }
              v288 = v284
                   + ((v284 & 0x7FFF) * ((int)(v234 * (2 - v275)) >> 16) >> 15)
                   + (2 * v284 >> 16) * ((int)(v234 * (2 - v275)) >> 16);
              if ( v288 < v252 )
                v251 = v275 + 1;
              ++v275;
              if ( v288 < v252 )
                v252 = v288;
            }
            while ( v275 < v274 );
          }
          else
          {
            do
            {
              v289 = (int16_t *)(v230 + 264);
              v290 = v230;
              haar1((_WORD *)v230 + 132, (unsigned int)(v238 >> v275), (unsigned int)(1 << v275));
              if ( v237 )
              {
                v291 = v290 + 34;
                v292 = ZERO32x4;
                v293 = (unsigned int)(8 * v237);
                v294 = ZERO32x4;
                v230 = (char *)v290;
                do
                {
                  v295 = *(v291 - 1);
                  v296 = *v291;
                  v293 -= 8LL;
                  v291 += 2;
                  v292 = vaddq_s32(vabsq_s32(vmovl_s16(vdup_n_s16(v295))), v292);
                  v294 = vaddq_s32(vabsq_s32(vmovl_s16(vdup_n_s16(v296))), v294);
                }
                while ( v293 );
                v297 = vaddvq_s32(vaddq_s32(v294, v292));
              }
              else
              {
                v297 = 0;
                v298 = (unsigned int)(8 * v237);
                v230 = (char *)v290;
                do
                {
                  v300 = *v289;
                  ++v289;
                  v299 = v300;
                  if ( v300 < 0 )
                    v299 = !v299;
                  --v298;
                  v297 += v299;
                }
                while ( v298 );
              }
              v301 = v275 + 1;
              v302 = v297 + ((v297 & 0x7FFF) * (v234 * v301 >> 16) >> 15) + (2 * v297 >> 16) * (v234 * v301 >> 16);
              v304 = __OFSUB__(v302, v252);
              v303 = v302 - v252 < 0;
              if ( v302 < v252 )
                v252 = v302;
              if ( v303 ^ v304 )
                v251 = v275 + 1;
              ++v275;
            }
            while ( v301 < v274 );
          }
        }
        v229 = v902;
        v312 = 2 * v251;
        if ( !(_DWORD)v902 )
          v312 = !v312;
        *(_DWORD *)&v230[4 * v235] = v312;
        if ( v237 == 1 && (!v312 || v312 == -6) )
          *(_DWORD *)&v230[4 * v235] = v312 - 1;
        ++v235;
        v153 = v901;
        if ( v907 == v899 )
        {
          v173 = v887;
          v143 = v900;
          v313 = v889;
          v314 = v885;
          if ( (_DWORD)v902 )
            v231 = 0;
          else
            v231 = v868;
          if ( (int)v887 <= 1 )
          {
            v161 = v886;
            v227 = v899 - v905;
            v340 = 0;
            v344 = 0;
          }
          else
          {
            v315 = 4 * v902;
            v161 = v886;
            v227 = v899 - v905;
            v316 = 0;
            v317 = v899 - 1;
            v318 = 2 * tf_select_table[4 * v902];
            v319 = 2 * tf_select_table[4 * v902 | 1];
            v320 = (int *)(v230 + 4);
            v321 = v899 - 1;
            v322 = v231;
            do
            {
              v324 = *v320;
              ++v320;
              v323 = v324;
              v325 = v316 + v868;
              if ( v316 >= v322 + v868 )
                v316 = v322 + v868;
              if ( v325 < v322 )
                v322 = v325;
              v326 = v323 - v318;
              if ( v323 - v318 < 0 )
                v326 = !v326;
              v316 += v326;
              if ( v323 - v319 >= 0 )
                v327 = v323 - v319;
              else
                v327 = !(v323 - v319);
              --v321;
              v322 += v327;
            }
            while ( v321 );
            v328 = 0;
            v329 = (int *)(v230 + 4);
            v330 = 2 * tf_select_table[v315 | 2];
            v331 = 2 * tf_select_table[v315 | 3];
            v332 = v899 - 1;
            do
            {
              v334 = *v329;
              ++v329;
              v333 = v334;
              v335 = v328 + v868;
              if ( v328 >= v231 + v868 )
                v328 = v231 + v868;
              if ( v335 < v231 )
                v231 = v335;
              v336 = v333 - v330;
              if ( v333 - v330 < 0 )
                v336 = !v336;
              v328 += v336;
              if ( v333 - v331 >= 0 )
                v337 = v333 - v331;
              else
                v337 = !(v333 - v331);
              --v332;
              v231 += v337;
            }
            while ( v332 );
            v229 = v902;
            if ( v316 >= v322 )
              v316 = v322;
            if ( v328 < v231 )
              v231 = v328;
            v338 = v231 < v316;
            v339 = v902 != 0;
            v340 = v339 && v338;
            v341 = (unsigned int)v315 | 2 * (v339 && v338);
            v342 = tf_select_table[v341];
            v343 = tf_select_table[v341 | 1];
            v344 = 0;
            if ( (_DWORD)v902 )
              v231 = 0;
            else
              v231 = v868;
            v345 = 2 * v342;
            v346 = 2 * v343;
            v347 = v230 + 92;
            do
            {
              v348 = v231 + v868;
              v349 = v344 + v868;
              if ( v344 < v231 + v868 )
                v348 = v344;
              *v347 = v344 >= v231 + v868;
              v350 = *(v347 - 22);
              v352 = __OFSUB__(v349, v231);
              v351 = v349 - v231 < 0;
              if ( v349 < v231 )
                v231 = v349;
              if ( v351 ^ v352 )
                v353 = 0;
              else
                v353 = 1;
              v347[22] = v353;
              v354 = v350 - v345;
              if ( v350 - v345 < 0 )
                v354 = !v354;
              v355 = v350 - v346;
              v271 = v350 - v346 < 0;
              v344 = v354 + v348;
              if ( v271 )
                v356 = !v355;
              else
                v356 = v355;
              --v317;
              v231 += v356;
              ++v347;
            }
            while ( v317 );
          }
          goto LABEL_463;
        }
        continue;
      }
    }
LABEL_461:
    v313 = v889;
    v314 = v885;
    v340 = 0;
    v344 = 0;
    if ( (_DWORD)v902 )
      v231 = 0;
LABEL_463:
    v272 = __OFSUB__(v344, v231);
    v271 = v344 - v231 < 0;
    v361 = v173 - 1;
    if ( v271 ^ v272 )
      v362 = 0;
    else
      v362 = 1;
    LODWORD(v363) = v899 - 2;
    *(&v933 + v361) = v362;
    if ( (int)v899 - 2 >= 0 )
    {
      v363 = (int)v363;
      do
      {
        v364 = &v933 + v363;
        if ( v364[1] == 1 )
          v365 = (int64_t)(v230 + 176);
        else
          v365 = (int64_t)(v230 + 88);
        v366 = *(_DWORD *)(v365 + 4 * v363 + 4);
        v273 = v363 == 0;
        v271 = v363-- < 0;
        *v364 = v366;
      }
      while ( !v271 && !v273 );
    }
    v933 = v229;
    v934 = v229;
    v357 = *(_DWORD *)(v143 + 20);
    if ( (int)v899 < v357 )
    {
      do
        *(&v933 + v173++) = *(&v933 + v361);
      while ( v173 < v357 );
    }
LABEL_475:
    quant_coarse_energy(
      v153,
      v357,
      v227,
      (int64_t)v953,
      v313,
      v894,
      (int64_t)&v948,
      (int64_t)&v909,
      v314,
      *(_DWORD *)(v143 + 16),
      (int *)(v143 + 36));
    v367 = *(unsigned int *)(v143 + 20);
    if ( v161 )
    {
      v368 = v896;
      v369 = v893;
      v370 = v888;
      if ( (int)v367 >= 1 )
        memset(&v933, 0, 4 * v367);
      goto LABEL_509;
    }
    v371 = v911;
    LODWORD(v875) = v227;
    v372 = 8 * v910;
    v373 = ec_ilog(v912);
    v374 = v902;
    v375 = v371 - v373;
    if ( (_DWORD)v902 )
      v376 = 2;
    else
      v376 = 4;
    v377 = v375 + (v376 | 1);
    if ( (int)v367 < 1 )
    {
      v380 = 0;
      if ( v377 <= v372 )
        goto LABEL_497;
      goto LABEL_489;
    }
    v378 = v372 - (v377 <= v372);
    v379 = (_DWORD)v902 ? 4 : 5;
    if ( v376 + v375 <= v378 )
    {
      ec_enc_bit_logp((int64_t *)&v909, v933, v376);
      v382 = v911;
      v383 = ec_ilog(v912);
      v374 = v902;
      v380 = v933;
      v375 = v382 - v383;
      if ( (_DWORD)v367 == 1 )
        goto LABEL_496;
    }
    else
    {
      v380 = 0;
      v933 = 0;
      if ( (_DWORD)v367 == 1 )
        goto LABEL_496;
    }
    v384 = &v934;
    v385 = v367 - 1;
    v386 = v380;
    do
    {
      while ( v379 + v375 > v378 )
      {
        *v384 = v386;
        --v385;
        ++v384;
        if ( !v385 )
          goto LABEL_496;
      }
      ec_enc_bit_logp((int64_t *)&v909, *v384 ^ v386, v379);
      v387 = v911;
      v388 = ec_ilog(v912);
      v386 = *v384;
      v375 = v387 - v388;
      v153 = v901;
      v374 = v902;
      v380 |= *v384;
      --v385;
      ++v384;
    }
    while ( v385 );
LABEL_496:
    if ( v377 <= v372 )
    {
LABEL_497:
      v227 = v875;
      if ( tf_select_table[4 * v374 + v380] == tf_select_table[v380 + (4LL * (v374 & 1) | 2)] )
      {
        v381 = 0;
      }
      else
      {
        ec_enc_bit_logp((int64_t *)&v909, v340, 1);
        v381 = 2 * v340;
      }
      v143 = v900;
      goto LABEL_501;
    }
LABEL_489:
    v143 = v900;
    v227 = v875;
    v381 = 0;
LABEL_501:
    v368 = v896;
    v369 = v893;
    v370 = v888;
    if ( (int)v367 < 1 )
      goto LABEL_509;
    v389 = v381 & 0xFFFFFFFB | 4 * (v902 & 1);
    if ( (_DWORD)v367 == 1 )
    {
      v390 = 0LL;
LABEL_507:
      v394 = v367 - v390;
      v395 = &v933 + v390;
      do
      {
        --v394;
        *v395 = tf_select_table[v389 + *v395];
        ++v395;
      }
      while ( v394 );
      goto LABEL_509;
    }
    v390 = (unsigned int)v367 & 0xFFFFFFFE;
    v391 = &v934;
    v392 = (unsigned int)v367 & 0xFFFFFFFE;
    do
    {
      v392 -= 2LL;
      v393 = tf_select_table[v389 + *v391];
      *(v391 - 1) = tf_select_table[v389 + *(v391 - 1)];
      *v391 = v393;
      v391 += 2;
    }
    while ( v392 );
    if ( v390 != v367 )
      goto LABEL_507;
LABEL_509:
    v396 = v911;
    if ( (int)(v396 + 4 - (uint64_t)ec_ilog(v912)) <= v894 )
    {
      if ( v885 < 10 * (int)v368 || v876 )
      {
        v398 = 2;
        *(_DWORD *)(v143 + 32) = 2;
      }
      else
      {
        v398 = spreading_decision(
                 v153,
                 (int64_t)dword_2EDB0,
                 (_DWORD *)(v143 + 40),
                 *(_DWORD *)(v143 + 32),
                 (int *)(v143 + 48),
                 (int *)(v143 + 52),
                 v874 ^ 1u,
                 v227);
        *(_DWORD *)(v143 + 32) = v398;
      }
      ec_enc_icdf((int64_t *)&v909, v398, (int64_t)&unk_16B48, 5);
    }
    v399 = *(__int128_t **)(v153 + 56);
    v400 = *(int *)(v143 + 20) - v905;
    if ( (int)v370 >= 1 )
      memset(&v936, 0, 4 * v878);
    if ( (int)v400 >= 1 )
    {
      if ( (unsigned int)v400 < 8 )
      {
        v401 = 0LL;
LABEL_523:
        v413 = ((_DWORD)v401 << 16) + 327680;
        do
        {
          v414 = 2 * v401;
          v415 = eMeans[v401];
          v416 = v413 * (v401 + 5);
          v417 = (*((uint16_t *)v399 + v401++) << 6) + 58880;
          v413 += 0x10000;
          *(_WORD *)&v956[v414] = v417 - (v415 << 6) + 6 * HIWORD(v416);
        }
        while ( (unsigned int)v400 != v401 );
        goto LABEL_525;
      }
      v402 = eMeans;
      v403 = vdupq_n_s32(xmmword_16B10);
      v404 = vdupq_n_s32(xmmword_16A80);
      v401 = (unsigned int)v400 & 0xFFFFFFF8;
      v405 = v956;
      v406 = (unsigned int)v400 & 0xFFFFFFF8;
      v407 = v399;
      do
      {
        v408 = *v407;
        ++v407;
        v409 = vdup_n_s16(v408);
        DWORD1(v408) = DWORD1(v402); // in case I edited the wrong line, this was *(_QWORD *)&v408 = *(_QWORD *)v402;
        v402 += 8;
        LODWORD(v397) = LODWORD(v408);
        v410 = vaddq_s32(v404, vdupq_n_s32(5));
        v411 = vaddq_s32(v403, vdupq_n_s32(5));
        LOWORD(v397) = v408;
        v412 = vshll_high_n_s16(vdupq_n_s16(v397), 6uLL);
        LODWORD(v397) = vgetq_lane_s32(vmlaq_s32(
                          vsubq_s32(vaddq_s32(vshll_n_s16(v409, 6uLL), vdupq_n_s32(58880)), vshll_n_s16(vdup_n_s16(v397), 6uLL)),
                          vshrq_n_s32(vshlq_n_s32(vmulq_s32(v410, v410), 0x10uLL), 0x10uLL),
                          vdupq_n_s32(6)), 0);
        LOWORD(v397) = vmovn_hight_s32(
                         vmovn_s32(vdupq_n_s32(v397)),
                         vmlaq_s32(
                           vsubq_s32(vaddq_s32(vshll_high_n_s16(vcombine_s16(v409, vdup_n_s16(0)), 6uLL), vdupq_n_s32(58880)), v412),
                           vshrq_n_s32(vshlq_n_s32(vmulq_s32(v411, v411), 0x10uLL), 0x10uLL),
                           vdupq_n_s32(6)));
        v404 = vaddq_s32(v404, vdupq_n_s32(8));
        v406 -= 8LL;
        *(_OWORD *)v405 = v397;
        v405 += 16;
        v403 = vaddq_s32(v403, vdupq_n_s32(8));
      }
      while ( v406 );
      if ( v401 != (unsigned int)v400 )
        goto LABEL_523;
    }
LABEL_525:
    if ( v369 < 51 )
      goto LABEL_629;
    if ( (int)v400 > 1 )
    {
      v418 = 0;
      v419 = 0LL;
      v420 = 0;
      v421 = 2 * v370;
      v422 = v957;
      v423 = (char *)v957 + 2;
      v424 = &v956[90];
      v425 = &v949;
      while ( 1 )
      {
        v426 = 2 * v419 * v370;
        LOWORD(v427) = *(int16_t *)((char *)&v949 + v426);
        v428 = 0LL;
        *(_WORD *)((char *)v957 + v426) = v427;
        do
        {
          v429 = 2 * v428;
          v430 = &v425[v428];
          v431 = *v430;
          v432 = v430[1];
          ++v428;
          v427 = (int16_t)v427 + 1536;
          if ( v431 + 512 < v432 )
            v420 = v428;
          if ( v427 >= v432 )
            LOWORD(v427) = v432;
          *(_WORD *)&v423[v429] = v427;
        }
        while ( (unsigned int)v400 - 1LL != v428 );
        if ( v420 >= 1 )
        {
          v433 = v420;
          v434 = (uint64_t)(unsigned int)(v418 + v420) << 32;
          do
          {
            v435 = 2 * v433;
            v436 = v425[v433 - 1];
            v437 = *(int16_t *)&v424[2 * v433];
            v438 = *(int16_t *)((char *)v957 + (v434 >> 31)) + 2048;
            --v433;
            if ( v438 >= v436 )
              v438 = v436;
            if ( v438 > v437 )
              LOWORD(v438) = v437;
            v434 -= 0x100000000LL;
            *(_WORD *)&v424[v435] = v438;
          }
          while ( v433 > 0 );
        }
        if ( (unsigned int)v400 < 8 )
          break;
        v440 = v956;
        v441 = (unsigned int)v400 & 0xFFFFFFF8;
        v442 = v422;
        do
        {
          v443 = *(_OWORD *)v442;
          v444 = *(_OWORD *)v440;
          v440 += 16;
          v441 -= 8LL;
          LOWORD(v443) = ((*(_OWORD *)v442) > v444) ? *(_OWORD *)442 : v444;
          *(_OWORD *)v442 = v443;
          v442 += 4;
        }
        while ( v441 );
        v439 = (unsigned int)v400 & 0xFFFFFFF8;
        if ( v439 != (unsigned int)v400 )
          goto LABEL_546;
LABEL_549:
        ++v419;
        v423 += v421;
        v425 = (int16_t *)((char *)v425 + v421);
        v418 += v370;
        v424 += v421;
        v422 = (int *)((char *)v422 + v421);
        if ( v419 >= v368 )
          goto LABEL_573;
      }
      v439 = 0LL;
      do
      {
LABEL_546:
        v445 = 2 * v439;
        v446 = *((int16_t *)v422 + v439);
        v447 = *(int16_t *)&v956[2 * v439++];
        if ( v446 <= v447 )
          LOWORD(v446) = v447;
        *(_WORD *)((char *)v422 + v445) = v446;
      }
      while ( (unsigned int)v400 != v439 );
      goto LABEL_549;
    }
    if ( (int)v400 >= 1 )
    {
      v448 = 0LL;
      v449 = v957;
      while ( 1 )
      {
        *((_WORD *)v957 + v448 * v370) = *(&v949 + v448 * v370);
        if ( (unsigned int)v400 < 8 )
          break;
        v451 = v956;
        v452 = (unsigned int)v400 & 0xFFFFFFF8;
        v453 = v449;
        do
        {
          v454 = *(_OWORD *)v453;
          v455 = *(_OWORD *)v451;
          v451 += 16;
          v452 -= 8LL;
          LOWORD(v454) = ((*(_OWORD *)v453) > v455) ? *(_OWORD *)v453 : v455;
          *(_OWORD *)v453 = v454;
          v453 += 4;
        }
        while ( v452 );
        v450 = (unsigned int)v400 & 0xFFFFFFF8;
        if ( v450 != (unsigned int)v400 )
          goto LABEL_558;
LABEL_561:
        ++v448;
        v449 = (int *)((char *)v449 + 2 * v370);
        if ( v448 >= v368 )
          goto LABEL_573;
      }
      v450 = 0LL;
      do
      {
LABEL_558:
        v456 = 2 * v450;
        v457 = *((int16_t *)v449 + v450);
        v458 = *(int16_t *)&v956[2 * v450++];
        if ( v457 <= v458 )
          LOWORD(v457) = v458;
        *(_WORD *)((char *)v449 + v456) = v457;
      }
      while ( (unsigned int)v400 != v450 );
      goto LABEL_561;
    }
    if ( v368 <= 1 )
      v459 = 1LL;
    else
      v459 = v368;
    if ( v459 <= 1 )
    {
      v460 = 0LL;
LABEL_571:
      v464 = 2 * v460 * v370;
      do
      {
        ++v460;
        *(_WORD *)((char *)v957 + v464) = *(int16_t *)((char *)&v949 + v464);
        v464 += 2 * v370;
      }
      while ( v460 < v368 );
      goto LABEL_573;
    }
    v460 = v459 & 0x7FFFFFFFFFFFFFFELL;
    v461 = 0LL;
    v462 = v459 & 0x7FFFFFFFFFFFFFFELL;
    do
    {
      v463 = *(int16_t *)((char *)&v949 + 2 * v370 + v461);
      v462 -= 2LL;
      LOWORD(v957[v461 / 4]) = *(int16_t *)((char *)&v949 + v461);
      *(_WORD *)((char *)v957 + 2 * v370 + v461) = v463;
      v461 += 4 * v370;
    }
    while ( v462 );
    if ( v459 != v460 )
      goto LABEL_571;
LABEL_573:
    if ( (_DWORD)v368 == 2 )
    {
      if ( (int)v400 < 1 )
        goto LABEL_629;
      if ( (unsigned int)v400 >= 8 )
      {
        v465 = v902;
        if ( (char *)v957 + 2 * v370 >= (char *)v957 + 2 * (unsigned int)v400
          || v957 >= (int *)((char *)v957 + 2 * (v370 + (unsigned int)v400)) )
        {
          v466 = (unsigned int)v400 & 0xFFFFFFF8;
          v478 = 2 * v370;
          v479 = v953;
          v480 = v957;
          v481 = (unsigned int)v400 & 0xFFFFFFF8;
          do
          {
            v482 = *(_OWORD *)((char *)v480 + v478);
            v483 = *(_OWORD *)v480;
            *((_QWORD *)&v484 + 1) = 64424509455LL;
            v481 -= 8LL;
            v485 = vmovl_high_s16(vdupq_n_s16(v482));
            LODWORD(v483) = 15 + *(_OWORD *)v480;
            LODWORD(v482) = (v483 > v482) ? v483 : v482;
            v486 = vmaxq_s32(vaddw_high_s16(vdupq_n_s32(15), vdupq_n_s16(*(_OWORD *)v480)), v485);
            LOWORD(v483) = vmovn_hight_s32(vmovn_s32(vdupq_n_s32(v482)), v486);
            *(_OWORD *)((char *)v480 + v478) = v483;
            *(_QWORD *)&v484 = ((uint64_t)15) | (((((int64_t)v482 << 16) + 0x8000) >> 16) << 32);
            LODWORD(v482) = (v484 > *(_OWORD *)v480) ? v484 : *(_OWORD *)v480;
            LODWORD(v483) = vgetq_lane_s32(vmaxq_s32(
                              vsraq_n_s32(vdupq_n_s32(15), vshlq_n_s32(v486, 0x10uLL), 0x10uLL),
                              vmovl_high_s16(vdupq_n_s16(*(_OWORD *)v480))), 0);
            v487 = vshlq_n_s32(vdupq_n_s32(v483), 0x10uLL);
            LOWORD(v484) = ((v482 & 0xFFFF0000) >> 16) | (v483 & 0xFFFF);
            v488 = *(_OWORD *)v479;
            *(_OWORD *)v480 = v484;
            v489 = *(_OWORD *)&v479[v478];
            LODWORD(v484) = vgetq_lane_s32(vsubq_s32(vmovl_high_s16(vdupq_n_s16(v488)), vshrq_n_s32(v487, 0x10uLL)), 0);
            v490 = *(_OWORD *)((char *)v480 + v478);
            LODWORD(v482) = (int) (fmaxf(
                        fmaxf(
                            (float)((int32_t)v488 - ((v482 << 16) >> 16)),
                            0.0f),
                        fmaxf(
                            (float)((int32_t)v489 - (int32_t)v490),
                            0.0f))
                        );
            LOWORD(v482) = ((int16_t)((int32_t)v482 >> 1) + 
                  ((v484 > 0 ? v484 : 0) + 
                   ((int32_t)(v489 - v490) > 0 ? (int32_t)(v489 - v490) : 0)) >> 1);
            v479 += 16;
            *(_OWORD *)v480 = v482;
            v480 += 4;
          }
          while ( v481 );
          if ( v466 == (unsigned int)v400 )
            goto LABEL_598;
        }
        else
        {
          v466 = 0LL;
        }
      }
      else
      {
        v465 = v902;
        v466 = 0LL;
      }
      v491 = 2 * (v466 + v370);
      do
      {
        v492 = 2 * v466;
        v493 = *((int16_t *)v957 + v466);
        v494 = *(int16_t *)((char *)v957 + v491);
        v495 = *(int16_t *)&v953[2 * v466++];
        v496 = v493 - 4096;
        if ( v496 < v494 )
          LOWORD(v496) = *(_WORD *)((char *)v957 + v491);
        *(_WORD *)((char *)v957 + v491) = v496;
        v497 = *(int16_t *)((char *)v957 + v492);
        v498 = (int16_t)v496 - 4096;
        if ( v498 < v497 )
          LOWORD(v498) = *(_WORD *)((char *)v957 + v492);
        *(_WORD *)((char *)v957 + v492) = v498;
        v499 = *(int16_t *)&v953[v491];
        v500 = v495 - (int16_t)v498;
        v501 = *(int16_t *)((char *)v957 + v491);
        v491 += 2LL;
        *(_WORD *)((char *)v957 + v492) = ((v500 & ~(v500 >> 31))
                                         + ((v499 - v501) & (unsigned int)~((v499 - v501) >> 31))) >> 1;
      }
      while ( (unsigned int)v400 != v466 );
    }
    else
    {
      if ( (int)v400 < 1 )
        goto LABEL_629;
      if ( (unsigned int)v400 <= 7 )
      {
        v465 = v902;
        v467 = 0LL;
LABEL_586:
        v473 = 2 * v467;
        v474 = (unsigned int)v400 - v467;
        v475 = &v953[2 * v467];
        v476 = (_WORD *)((char *)v957 + v473);
        do
        {
          v477 = *(int16_t *)v475;
          v475 += 2;
          --v474;
          *v476 = (v477 - *v476) & ~((v477 - (int16_t)*v476) >> 31);
          ++v476;
        }
        while ( v474 );
        goto LABEL_598;
      }
      v465 = v902;
      v467 = (unsigned int)v400 & 0xFFFFFFF8;
      v468 = v953;
      v469 = v957;
      v470 = (unsigned int)v400 & 0xFFFFFFF8;
      do
      {
        v471 = *(_OWORD *)v468;
        v468 += 16;
        v472 = *(_OWORD *)v469;
        v470 -= 8LL;
        LODWORD(v472) = (int32_t)(v471 - *(_OWORD *)v469) > 0 ? (int32_t)(v471 - *(_OWORD *)v469) : 0;
        LOWORD(v472) = (int16_t)((v472 & 0xFFFF0000) >> 16) + 
                 (int16_t)(v471 - *(_OWORD *)v469 > 0 ? v471 - *(_OWORD *)v469 : 0);
        *(_OWORD *)v469 = v472;
        v469 += 4;
      }
      while ( v470 );
      if ( v467 != (unsigned int)v400 )
        goto LABEL_586;
    }
LABEL_598:
    if ( !v465 && (int)v400 >= 1 )
    {
      if ( (unsigned int)v400 < 0x10 )
      {
        v502 = 0LL;
LABEL_605:
        v507 = (unsigned int)v400 - v502;
        v508 = (_WORD *)((char *)v957 + 2 * v502);
        do
        {
          --v507;
          *v508 = (unsigned int)(int16_t)*v508 >> 1;
          ++v508;
        }
        while ( v507 );
        goto LABEL_607;
      }
      v502 = (unsigned int)v400 & 0xFFFFFFF0;
      v503 = &v957[4];
      v504 = (unsigned int)v400 & 0xFFFFFFF0;
      do
      {
        v505 = *((_OWORD *)v503 - 1);
        v506 = *(_OWORD *)v503;
        v504 -= 16LL;
        LOWORD(v505) = v505 >> 1uLL;
        LOWORD(v506) = *(_OWORD *)v503 >> 1uLL;
        *((_OWORD *)v503 - 1) = v505;
        *(_OWORD *)v503 = v506;
        v503 += 8;
      }
      while ( v504 );
      if ( v502 != (unsigned int)v400 )
        goto LABEL_605;
    }
LABEL_607:
    if ( (int)v400 >= 1 )
    {
      v509 = v369 + 3;
      if ( v369 >= 0 )
        v509 = v369;
      v510 = 0LL;
      v511 = 0;
      v512 = v509 >> 2;
      v513 = v957;
      do
      {
        if ( v510 > 7 )
        {
          v515 = *(uint16_t *)v513;
          v514 = (int *)((char *)v957 + 2 * v510);
          if ( v510 < 0xC )
            goto LABEL_616;
          v515 = *(uint16_t *)v513 << 16 >> 17;
        }
        else
        {
          v514 = v513;
          v515 = 2 * *(uint16_t *)v513;
        }
        *(_WORD *)v513 = v515;
LABEL_616:
        if ( (int16_t)v515 >= 4096 )
          v515 = 4096;
        *(_WORD *)v514 = v515;
        v516 = (v895[v510 + 1] - v895[v510]) * 8 * v368;
        if ( v516 > 5 )
        {
          v515 = (int16_t)v515;
          if ( v516 < 49 )
          {
            v517 = (int)(((uint64_t)(715827883LL * v516 * v515) >> 32)
                              + ((uint64_t)(715827883LL * v516 * v515) >> 63)) >> 10;
            v518 = 48 * v517 + v511;
            if ( v512 < v518 >> 6 )
              goto LABEL_654;
          }
          else
          {
            v517 = v515 >> 7;
            v519 = 8 * v517 * v516;
            if ( v519 >= 0 )
              v520 = 8 * v517 * v516;
            else
              v520 = v519 | 7;
            v518 = (v520 >> 3) + v511;
            if ( v512 < v518 >> 6 )
            {
LABEL_654:
              *(&v936 + v510) = (v512 << 6) - v511;
              goto LABEL_655;
            }
          }
        }
        else
        {
          v517 = v515 << 16 >> 26;
          v518 = 8 * v517 * v516 + v511;
          if ( v512 < v518 >> 6 )
            goto LABEL_654;
        }
        *(&v936 + v510++) = v517;
        v513 = (int *)((char *)v513 + 2);
        v511 = v518;
      }
      while ( (int64_t)v510 < v400 );
    }
LABEL_629:
    v521 = &v949 + v370;
    v522 = *v521;
    v523 = v521[1];
    v524 = v949 - 6500;
    if ( v524 >= v522 - 6500 )
      v524 = v522 - 6500;
    if ( v949 - v950 >= v522 - v523 )
      v525 = v522 - v523;
    else
      v525 = v949 - v950;
    if ( v524 >= 1 && v525 >= 1 )
    {
      v526 = (uint16_t)v524 / 0xC8u + (((v525 - 1500) & (unsigned int)~((v525 - 1500) >> 31)) >> 7);
      if ( v526 >= 0xA )
        v526 = 10;
      if ( (int)v526 > v936 )
        v936 = v526;
    }
    v527 = v950 - 6100;
    v528 = v523 - 6100;
    v529 = v523 - v522;
    v530 = v950 - v951;
    v531 = v523 - v521[2];
    if ( v527 >= v528 )
      v527 = v528;
    if ( v530 >= v531 )
      v530 = v531;
    if ( v950 - v949 >= v529 )
      v532 = v529;
    else
      v532 = v950 - v949;
    if ( v532 >= 1 && v527 >= 1 && v530 >= 1 )
    {
      v533 = (1717986919LL * (v530 - 1700) >> 38)
           + ((uint64_t)(1717986919LL * (v530 - 1700)) >> 63)
           + (uint16_t)v527 / 0xC8u;
      if ( v533 >= 10 )
        v533 = 10;
      if ( v533 > v937 )
        v937 = v533;
    }
LABEL_655:
    v908 = *(_QWORD *)(v153 + 128);
    LODWORD(v899) = v369 << 6;
    v534 = ec_tell_frac((int64_t)&v909);
    if ( *(_DWORD *)(v143 + 20) <= (int)v905 )
    {
      v538 = 0;
      v548 = v938;
      v549 = v939;
      if ( v938 < 1001 )
        goto LABEL_684;
    }
    else
    {
      v535 = v895;
      v536 = v369 << 6;
      v537 = 0LL;
      v538 = 0;
      v539 = 6;
      do
      {
        v540 = v537 + 1;
        v541 = v536 - v538;
        if ( 16 * (v535[v537 + 1] - v535[v537]) <= 48 )
          v542 = 48;
        else
          v542 = 16 * (v535[v537 + 1] - v535[v537]);
        if ( v534 + 8 * v539 >= v541 )
        {
          v543 = 0;
        }
        else
        {
          if ( *(_DWORD *)(v908 + 4 * v537) < 1 )
          {
            v543 = 0;
          }
          else
          {
            v543 = 0;
            v544 = 0;
            v545 = v539;
            while ( 1 )
            {
              v546 = *(&v936 + v537);
              ec_enc_bit_logp((int64_t *)&v909, v544 < v546, v545);
              v547 = ec_tell_frac((int64_t)&v909);
              v272 = __OFSUB__(v544, v546);
              v271 = v544 - v546 < 0;
              v534 = v547;
              if ( !(v271 ^ v272) )
                break;
              v541 -= v542;
              if ( v547 + 8 >= v541 )
              {
                v535 = v895;
                v536 = v369 << 6;
                v538 += v542 + v543;
                v543 += v542;
                goto LABEL_673;
              }
              v543 += v542;
              ++v544;
              v545 = 1;
              if ( v543 >= *(_DWORD *)(v908 + 4 * v537) )
              {
                v538 += v543;
                v535 = v895;
                v536 = v369 << 6;
                goto LABEL_673;
              }
            }
            v538 += v543;
            v535 = v895;
            v536 = v369 << 6;
            if ( !v544 )
              goto LABEL_676;
LABEL_673:
            if ( v539 - 1 <= 2 )
              v539 = 2;
            else
              --v539;
          }
LABEL_676:
          v143 = v900;
        }
        *(&v936 + v537++) = v543;
      }
      while ( v540 < *(int *)(v143 + 20) - v905 );
      v548 = v938;
      v549 = v939;
      if ( v938 < 1001 )
      {
LABEL_684:
        v550 = v901;
        v552 = v881;
        v553 = v905;
        if ( v549 < 1001 || v940 )
        {
          if ( v940 >= 1001 && !v941 )
          {
            v555 = v889[21];
            if ( v555 > 7000 || v555 > v889[20] >> 1 )
              v941 = v940;
          }
        }
        else
        {
          v554 = v889[20];
          if ( v554 > 7000 || v554 > v889[19] >> 1 )
            v940 = v549;
        }
        goto LABEL_694;
      }
    }
    if ( v549 )
      goto LABEL_684;
    v550 = v901;
    v551 = v889[19];
    v552 = v881;
    v553 = v905;
    if ( v551 > 7000 || v551 > v889[18] >> 1 )
      v939 = v548;
LABEL_694:
    v556 = *(uint16_t **)(v550 + 16);
    v557 = 0LL;
    v558 = *v556;
    v559 = 1;
    v560 = 1;
    do
    {
      while ( 1 )
      {
        v561 = (int16_t)v556[++v557];
        v562 = v558 << 16 >> 13;
        v563 = 8 * v561;
        v558 = (uint16_t)v561;
        if ( 8 * v561 > v562 )
          break;
LABEL_714:
        if ( v557 == 13 )
          goto LABEL_715;
      }
      v564 = v562;
      v565 = v563 - v562;
      if ( !(_DWORD)v565 )
      {
        v575 = (int16_t *)((char *)dword_2EDB0 + 2 * (v552 + v564));
        v576 = (int16_t *)((char *)dword_2EDB0 + 2 * v564);
        do
        {
          v578 = *v576;
          ++v576;
          v577 = v578;
          v580 = *v575;
          ++v575;
          v579 = v580;
          if ( v577 >= 0 )
            v581 = v577;
          else
            v581 = !v577;
          if ( v579 >= 0 )
            v582 = v579;
          else
            v582 = !v579;
          v583 = v581 + v559;
          if ( v579 + v577 >= 0 )
            v584 = v579 + v577;
          else
            v584 = !(v579 + v577);
          v585 = v577 - v579;
          if ( v585 < 0 )
            v585 = !v585;
          v559 = v583 + v582;
          --v565;
          v560 += v585 + v584;
        }
        while ( v565 );
        goto LABEL_714;
      }
      v566 = (int64_t *)((char *)&dword_2EDB0[2] + 2 * v564);
      v567 = ZERO32x4;
      v568 = vdupq_n_s32(v559);
      v569 = vdupq_n_s32(v560);
      v570 = (_QWORD *)((char *)&dword_2EDB0[2] + 2 * (v552 + v564));
      v571 = ZERO32x4;
      do
      {
        v572 = *(v566 - 1);
        v573 = *v566;
        v574 = *(v570 - 1);
        v565 -= 8LL;
        v566 += 2;
        v568 = vaddq_s32(vaddq_s32(vabsq_s32(vmovl_s16(vdup_n_s16(v572))), v568), vabsq_s32(vmovl_s16(vdup_n_s16(v574))));
        v567 = vaddq_s32(vaddq_s32(vabsq_s32(vmovl_s16(vdup_n_s16(v573))), v567), vabsq_s32(vmovl_s16(vdup_n_s16(*v570))));
        v569 = vaddq_s32(vaddq_s32(vabsq_s32(vsubl_s16(vdup_n_s16(v572), vdup_n_s16(v574))), v569), vabsq_s32(vaddl_s16(vdup_n_s16(v574), vdup_n_s16(v572))));
        v571 = vaddq_s32(vaddq_s32(vabsq_s32(vsubl_s16(vdup_n_s16(v573), vdup_n_s16(*v570))), v571), vabsq_s32(vaddl_s16(vdup_n_s16(*v570), vdup_n_s16(v573))));
        v570 += 2;
      }
      while ( v565 );
      v560 = vaddvq_s32(vaddq_s32(v571, v569));
      v559 = vaddvq_s32(vaddq_s32(v567, v568));
    }
    while ( v557 != 13 );
LABEL_715:
    v586 = v556[13];
    v587 = 46340 * (v560 >> 16) + (23170 * (unsigned int)(uint16_t)v560 >> 15);
    v915 = (((int16_t)(16 * v586) | 0xD) * (uint16_t)v587 >> 15)
         + 2 * (v587 >> 16) * ((int16_t)(16 * v586) | 0xD) > ((uint16_t)v559
                                                                   * (int)(int16_t)(16 * v586) >> 15)
                                                                  + 2 * (v559 >> 16) * (int16_t)(16 * v586);
    v588 = (unsigned int *)(v143 + 80);
    v589 = hysteresis_decision(510, (int64_t)&unk_16B4C, (int64_t)&unk_16B7A, 22 - v553, *(unsigned int *)(v143 + 80));
    v590 = *(_DWORD *)(v143 + 20);
    v591 = v534 + 48;
    v592 = v590 - v553;
    if ( v590 - v553 >= (v589 & ~(v589 >> 31)) )
      LODWORD(v593) = v589 & ~(v589 >> 31);
    else
      LODWORD(v593) = v590 - v553;
    *v588 = v593;
    if ( v591 > (int)v899 - v538 )
    {
      v594 = v896;
      v595 = 5;
      goto LABEL_848;
    }
    v596 = *(int16_t **)(v901 + 16);
    v597 = *v596;
    v598 = v596[1];
    v599 = 8 * v597;
    v600 = 8 * v598;
    if ( 8 * (int)v597 >= 8 * (int)v598 )
    {
      v610 = 0;
      v611 = 8LL * v596[2];
      if ( (int)v600 >= (int)v611 )
        goto LABEL_727;
      goto LABEL_731;
    }
    v601 = v600 - v599;
    if ( v600 == v599 )
    {
      v610 = 0;
      v613 = (int16_t *)((char *)dword_2EDB0 + 2 * (v552 + v599));
      v614 = (int16_t *)&dword_2EDB0[v599 / 2];
      do
      {
        v616 = *v614;
        ++v614;
        v615 = v616;
        v617 = *v613;
        ++v613;
        --v601;
        v610 += v617 * v615;
      }
      while ( v601 );
      v611 = 8LL * v596[2];
      if ( (int)v600 < (int)v611 )
        goto LABEL_731;
LABEL_727:
      v612 = 0;
    }
    else
    {
      v602 = ZERO32x4;
      v603 = (int64_t *)&dword_2EDB0[4 * v597 + 2];
      v604 = (int64_t *)((char *)&dword_2EDB0[2] + 2 * (v552 + v599));
      v605 = ZERO32x4;
      do
      {
        v606 = *(v603 - 1);
        v607 = *v603;
        v608 = *(v604 - 1);
        v609 = *v604;
        v601 -= 8LL;
        v603 += 2;
        v604 += 2;
        v602 = vmlal_s16(v602, vdup_n_s16(v608), vdup_n_s16(v606));
        v605 = vmlal_s16(v605, vdup_n_s16(v609), vdup_n_s16(v607));
      }
      while ( v601 );
      v610 = vaddvq_s32(vaddq_s32(v605, v602));
      v611 = 8LL * v596[2];
      if ( (int)v600 >= (int)v611 )
        goto LABEL_727;
LABEL_731:
      v618 = (int)v600;
      v619 = v611 - (int)v600;
      if ( v619 )
      {
        v620 = ZERO32x4;
        v621 = (int64_t *)((char *)&dword_2EDB0[2] + 2 * v618);
        v622 = (int64_t *)((char *)&dword_2EDB0[2] + 2 * (v552 + v618));
        v623 = ZERO32x4;
        do
        {
          v624 = *(v621 - 1);
          v625 = *v621;
          v626 = *(v622 - 1);
          v627 = *v622;
          v619 -= 8LL;
          v621 += 2;
          v622 += 2;
          v620 = vmlal_s16(v620, vdup_n_s16(v626), vdup_n_s16(v624));
          v623 = vmlal_s16(v623, vdup_n_s16(v627), vdup_n_s16(v625));
        }
        while ( v619 );
        v612 = vaddvq_s32(vaddq_s32(v623, v620));
      }
      else
      {
        v612 = 0;
        v628 = (int16_t *)((char *)dword_2EDB0 + 2 * (v552 + v618));
        v629 = (int16_t *)((char *)dword_2EDB0 + 2 * v618);
        do
        {
          v631 = *v629;
          ++v629;
          v630 = v631;
          v632 = *v628;
          ++v628;
          --v619;
          v612 += v632 * v630;
        }
        while ( v619 );
      }
    }
    v633 = (v612 >> 18) + (v610 >> 18);
    v634 = 8LL * v596[3];
    if ( (int)v611 >= (int)v634 )
    {
      v645 = 0;
    }
    else
    {
      v635 = (int)v611;
      v636 = v634 - (int)v611;
      if ( v634 == (int)v611 )
      {
        v645 = 0;
        v646 = (int16_t *)((char *)dword_2EDB0 + 2 * (v552 + v635));
        v647 = (int16_t *)((char *)dword_2EDB0 + 2 * v635);
        do
        {
          v649 = *v647;
          ++v647;
          v648 = v649;
          v650 = *v646;
          ++v646;
          --v636;
          v645 += v650 * v648;
        }
        while ( v636 );
      }
      else
      {
        v637 = ZERO32x4;
        v638 = (int64_t *)((char *)&dword_2EDB0[2] + 2 * (int)v611);
        v639 = (int64_t *)((char *)&dword_2EDB0[2] + 2 * (v552 + v635));
        v640 = ZERO32x4;
        do
        {
          v641 = *(v638 - 1);
          v642 = *v638;
          v643 = *(v639 - 1);
          v644 = *v639;
          v636 -= 8LL;
          v638 += 2;
          v639 += 2;
          v637 = vmlal_s16(v637, vdup_n_s16(v643), vdup_n_s16(v641));
          v640 = vmlal_s16(v640, vdup_n_s16(v644), vdup_n_s16(v642));
        }
        while ( v636 );
        v645 = vaddvq_s32(vaddq_s32(v640, v637));
      }
    }
    v651 = v633 + (v645 >> 18);
    v652 = 8LL * v596[4];
    if ( (int)v634 >= (int)v652 )
    {
      v663 = 0;
    }
    else
    {
      v653 = (int)v634;
      v654 = v652 - (int)v634;
      if ( v652 == (int)v634 )
      {
        v663 = 0;
        v664 = (int16_t *)((char *)dword_2EDB0 + 2 * (v552 + v653));
        v665 = (int16_t *)((char *)dword_2EDB0 + 2 * v653);
        do
        {
          v667 = *v665;
          ++v665;
          v666 = v667;
          v668 = *v664;
          ++v664;
          --v654;
          v663 += v668 * v666;
        }
        while ( v654 );
      }
      else
      {
        v655 = ZERO32x4;
        v656 = (int64_t *)((char *)&dword_2EDB0[2] + 2 * (int)v634);
        v657 = (int64_t *)((char *)&dword_2EDB0[2] + 2 * (v552 + v653));
        v658 = ZERO32x4;
        do
        {
          v659 = *(v656 - 1);
          v660 = *v656;
          v661 = *(v657 - 1);
          v662 = *v657;
          v654 -= 8LL;
          v656 += 2;
          v657 += 2;
          v655 = vmlal_s16(v655, vdup_n_s16(v661), vdup_n_s16(v659));
          v658 = vmlal_s16(v658, vdup_n_s16(v662), vdup_n_s16(v660));
        }
        while ( v654 );
        v663 = vaddvq_s32(vaddq_s32(v658, v655));
      }
    }
    v669 = v651 + (v663 >> 18);
    v670 = 8LL * v596[5];
    if ( (int)v652 >= (int)v670 )
    {
      v681 = 0;
    }
    else
    {
      v671 = (int)v652;
      v672 = v670 - (int)v652;
      if ( v672 )
      {
        v673 = ZERO32x4;
        v674 = (int64_t *)((char *)&dword_2EDB0[2] + 2 * v671);
        v675 = (int64_t *)((char *)&dword_2EDB0[2] + 2 * (v552 + v671));
        v676 = ZERO32x4;
        do
        {
          v677 = *(v674 - 1);
          v678 = *v674;
          v679 = *(v675 - 1);
          v680 = *v675;
          v672 -= 8LL;
          v674 += 2;
          v675 += 2;
          v673 = vmlal_s16(v673, vdup_n_s16(v679), vdup_n_s16(v677));
          v676 = vmlal_s16(v676, vdup_n_s16(v680), vdup_n_s16(v678));
        }
        while ( v672 );
        v681 = vaddvq_s32(vaddq_s32(v676, v673));
      }
      else
      {
        v681 = 0;
        v682 = (int16_t *)((char *)dword_2EDB0 + 2 * (v552 + v671));
        v683 = (int16_t *)((char *)dword_2EDB0 + 2 * v671);
        do
        {
          v685 = *v683;
          ++v683;
          v684 = v685;
          v686 = *v682;
          ++v682;
          --v672;
          v681 += v686 * v684;
        }
        while ( v672 );
      }
    }
    v687 = v669 + (v681 >> 18);
    v688 = 8LL * v596[6];
    if ( (int)v670 >= (int)v688 )
    {
      LOWORD(v700) = 0;
    }
    else
    {
      v689 = (int)v670;
      v690 = v688 - (int)v670;
      if ( v690 )
      {
        v691 = ZERO32x4;
        v692 = (int64_t *)((char *)&dword_2EDB0[2] + 2 * v689);
        v693 = (int64_t *)((char *)&dword_2EDB0[2] + 2 * (v552 + v689));
        v694 = ZERO32x4;
        do
        {
          v695 = *(v692 - 1);
          v696 = *v692;
          v697 = *(v693 - 1);
          v698 = *v693;
          v690 -= 8LL;
          v692 += 2;
          v693 += 2;
          v691 = vmlal_s16(v691, vdup_n_s16(v697), vdup_n_s16(v695));
          v694 = vmlal_s16(v694, vdup_n_s16(v698), vdup_n_s16(v696));
        }
        while ( v690 );
        v699 = vaddvq_s32(vaddq_s32(v694, v691));
      }
      else
      {
        v699 = 0;
        v701 = (int16_t *)((char *)dword_2EDB0 + 2 * (v552 + v689));
        v702 = (int16_t *)((char *)dword_2EDB0 + 2 * v689);
        do
        {
          v704 = *v702;
          ++v702;
          v703 = v704;
          v705 = *v701;
          ++v701;
          --v690;
          v699 += v705 * v703;
        }
        while ( v690 );
      }
      v700 = v699 >> 18;
    }
    v706 = v687 + v700;
    v707 = 8LL * v596[7];
    if ( (int)v688 >= (int)v707 )
    {
      LOWORD(v719) = 0;
    }
    else
    {
      v708 = (int)v688;
      v709 = v707 - (int)v688;
      if ( v709 )
      {
        v710 = ZERO32x4;
        v711 = (int64_t *)((char *)&dword_2EDB0[2] + 2 * v708);
        v712 = (int64_t *)((char *)&dword_2EDB0[2] + 2 * (v552 + v708));
        v713 = ZERO32x4;
        do
        {
          v714 = *(v711 - 1);
          v715 = *v711;
          v716 = *(v712 - 1);
          v717 = *v712;
          v709 -= 8LL;
          v711 += 2;
          v712 += 2;
          v710 = vmlal_s16(v710, vdup_n_s16(v716), vdup_n_s16(v714));
          v713 = vmlal_s16(v713, vdup_n_s16(v717), vdup_n_s16(v715));
        }
        while ( v709 );
        v718 = vaddvq_s32(vaddq_s32(v713, v710));
      }
      else
      {
        v718 = 0;
        v720 = (int16_t *)((char *)dword_2EDB0 + 2 * (v552 + v708));
        v721 = (int16_t *)((char *)dword_2EDB0 + 2 * v708);
        do
        {
          v723 = *v721;
          ++v721;
          v722 = v723;
          v724 = *v720;
          ++v720;
          --v709;
          v718 += v724 * v722;
        }
        while ( v709 );
      }
      v719 = v718 >> 18;
    }
    v725 = v596[8];
    v726 = v706 + v719;
    if ( (int)v707 >= 8 * (int)v725 )
    {
      LOWORD(v738) = 0;
    }
    else
    {
      v727 = (int)v707;
      v728 = 8 * v725 - (int)v707;
      if ( v728 )
      {
        v729 = ZERO32x4;
        v730 = (int64_t *)((char *)&dword_2EDB0[2] + 2 * v727);
        v731 = (int64_t *)((char *)&dword_2EDB0[2] + 2 * (v552 + v727));
        v732 = ZERO32x4;
        do
        {
          v733 = *(v730 - 1);
          v734 = *v730;
          v735 = *(v731 - 1);
          v736 = *v731;
          v728 -= 8LL;
          v730 += 2;
          v731 += 2;
          v729 = vmlal_s16(v729, vdup_n_s16(v735), vdup_n_s16(v733));
          v732 = vmlal_s16(v732, vdup_n_s16(v736), vdup_n_s16(v734));
        }
        while ( v728 );
        v737 = vaddvq_s32(vaddq_s32(v732, v729));
      }
      else
      {
        v737 = 0;
        v739 = (int16_t *)((char *)dword_2EDB0 + 2 * (v552 + v727));
        v740 = (int16_t *)((char *)dword_2EDB0 + 2 * v727);
        do
        {
          v742 = *v740;
          ++v740;
          v741 = v742;
          v743 = *v739;
          ++v739;
          --v728;
          v737 += v743 * v741;
        }
        while ( v728 );
      }
      v738 = v737 >> 18;
    }
    v744 = (((int16_t)(v726 + v738) >> 31) + ((int16_t)(v726 + v738) >> 3)) ^ ((int16_t)(v726 + v738) >> 31);
    if ( v744 >= 1024 )
      v744 = 1024;
    if ( (int)v593 <= 8 )
    {
      v746 = v744;
    }
    else
    {
      LODWORD(v725) = (uint16_t)v725;
      v593 = (unsigned int)v593;
      v745 = 8LL;
      v746 = v744;
      do
      {
        v747 = v596[++v745];
        v748 = (_DWORD)v725 << 16 >> 13;
        LODWORD(v725) = (uint16_t)v747;
        if ( 8 * v747 <= v748 )
        {
          v759 = 0;
        }
        else
        {
          v749 = v748;
          v750 = 8 * v747 - v748;
          if ( (_DWORD)v750 )
          {
            v751 = (int64_t *)((char *)&dword_2EDB0[2] + 2 * v749);
            v752 = ZERO32x4;
            v753 = (int64_t *)((char *)&dword_2EDB0[2] + 2 * (v552 + v749));
            v754 = ZERO32x4;
            do
            {
              v755 = *(v751 - 1);
              v756 = *v751;
              v757 = *(v753 - 1);
              v758 = *v753;
              v750 -= 8LL;
              v751 += 2;
              v753 += 2;
              v752 = vmlal_s16(v752, vdup_n_s16(v757), vdup_n_s16(v755));
              v754 = vmlal_s16(v754, vdup_n_s16(v758), vdup_n_s16(v756));
            }
            while ( v750 );
            v759 = vaddvq_s32(vaddq_s32(v754, v752));
          }
          else
          {
            v759 = 0;
            v760 = (int16_t *)((char *)dword_2EDB0 + 2 * (v552 + v749));
            v761 = (int16_t *)((char *)dword_2EDB0 + 2 * v749);
            do
            {
              v763 = *v761;
              ++v761;
              v762 = v763;
              v764 = *v760;
              ++v760;
              --v750;
              v759 += v764 * v762;
            }
            while ( v750 );
          }
        }
        if ( (((v759 >> 31) + (v759 >> 18)) ^ (v759 >> 31)) <= v746 )
          v746 = ((v759 >> 31) + (v759 >> 18)) ^ (v759 >> 31);
      }
      while ( v745 != v593 );
    }
    if ( v746 >= 0 )
      v765 = v746;
    else
      v765 = !v746;
    v766 = 1049625 - v744 * v744;
    if ( v765 <= 1024 )
      v767 = (int16_t)v765;
    else
      v767 = 1024;
    if ( 1049625 == v744 * v744 )
    {
      v770 = -32767;
      v771 = 1049625 - v767 * v767;
      if ( 1049625 == v767 * v767 )
        goto LABEL_821;
LABEL_817:
      v772 = ec_ilog(v771);
      v773 = v771 << (16 - v772);
      if ( (int16_t)(v772 - 1) - 15 > 0 )
        v773 = v771 >> (v772 - 16);
      if ( v770 >> 1 <= (int16_t)(((v772 - 1) << 10)
                                       + ((int)((2
                                                      * ((int)((2
                                                                     * ((int)((2
                                                                                    * ((-1401
                                                                                      * (((v773 << 16) + 0x40000000) >> 16) >> 15)
                                                                                     + 2545)
                                                                                    * (((v773 << 16) + 0x40000000) >> 16) & 0xFFFF0000)
                                                                                   - 341901312) >> 16)
                                                                     * (((v773 << 16) + 0x40000000) >> 16) & 0xFFFF0000)
                                                                    + 1031929856) >> 16)
                                                      * (((v773 << 16) + 0x40000000) >> 16) & 0xFFFF0000)
                                                     - 445186048) >> 20)
                                       - 13312) )
        ec_ilog(v771);
      goto LABEL_821;
    }
    v768 = ec_ilog(v766);
    v769 = v766 << (16 - v768);
    if ( (int16_t)(v768 - 1) - 15 > 0 )
      v769 = v766 >> (v768 - 16);
    v770 = (int16_t)(((v768 - 1) << 10)
                          + ((int)((2
                                         * ((int)((2
                                                        * ((int)((2
                                                                       * ((-1401 * (((v769 << 16) + 0x40000000) >> 16) >> 15)
                                                                        + 2545)
                                                                       * (((v769 << 16) + 0x40000000) >> 16) & 0xFFFF0000)
                                                                      - 341901312) >> 16)
                                                        * (((v769 << 16) + 0x40000000) >> 16) & 0xFFFF0000)
                                                       + 1031929856) >> 16)
                                         * (((v769 << 16) + 0x40000000) >> 16) & 0xFFFF0000)
                                        - 445186048) >> 20)
                          - 13312);
    v771 = 1049625 - v767 * v767;
    if ( 1049625 != v767 * v767 )
      goto LABEL_817;
LABEL_821:
    v143 = v900;
    if ( 24576 * (((v770 << 14) - 100630528) >> 16) >= -33554432 )
    {
      v774 = (int)((49152 * (((v770 << 14) - 100630528) >> 16) & 0xFFFF0000) + 83886080) >> 16;
      v553 = v905;
      v775 = v592 - 1;
      if ( v592 - 1 >= 1 )
        goto LABEL_825;
LABEL_823:
      v594 = v896;
      v776 = 0;
    }
    else
    {
      v774 = 256;
      v553 = v905;
      v775 = v592 - 1;
      if ( v592 - 1 < 1 )
        goto LABEL_823;
LABEL_825:
      v777 = 2 - v592;
      if ( v775 < 8 )
      {
        v594 = v896;
        v778 = 0LL;
        v776 = 0;
        goto LABEL_830;
      }
      v779 = vdupq_n_s32(xmmword_16A80);
      v778 = v775 & 0xFFFFFFF8;
      v780 = vdupq_n_s32(v777);
      v781 = &v953[8];
      v782 = ZERO32x4;
      v783 = v775 & 0xFFFFFFF8;
      v784 = ZERO32x4;
      do
      {
        v785 = vaddq_s32(vshlq_n_s32(v779, 1uLL), v780);
        v779 = vaddq_s32(v779, vdupq_n_s32(8));
        v783 -= 8LL;
        v782 = vmlaq_s32(v782, v785, vdupq_n_s32(*((_QWORD *)v781 - 1)));
        v784 = vmlaq_s32(v784, vaddq_s32(v785, vdupq_n_s32(8)), vdupq_n_s32(*(_QWORD *)v781));
        v781 += 16;
      }
      while ( v783 );
      v594 = v896;
      v776 = vaddvq_s32(vaddq_s32(v784, v782));
      if ( v778 != v775 )
      {
LABEL_830:
        v786 = v553 + 2 * v778;
        v787 = v775 - v778;
        v788 = &v953[2 * v778];
        v789 = v786 + 2 - v590;
        do
        {
          v790 = *(int16_t *)v788;
          v788 += 2;
          --v787;
          v776 += v789 * v790;
          v789 += 2;
        }
        while ( v787 );
      }
      v791 = *(int *)(v901 + 8);
      if ( v775 < 8 )
      {
        v792 = 0LL;
        goto LABEL_837;
      }
      v793 = vdupq_n_s32(xmmword_16A80);
      v794 = vdupq_n_s32(v777);
      v792 = v775 & 0xFFFFFFF8;
      v795 = vdupq_n_s32(v776);
      v796 = ZERO32x4;
      v797 = &v953[2 * v791 + 8];
      v798 = v775 & 0xFFFFFFF8;
      do
      {
        v799 = vaddq_s32(vshlq_n_s32(v793, 1uLL), v794);
        v793 = vaddq_s32(v793, vdupq_n_s32(8));
        v798 -= 8LL;
        v795 = vmlaq_s32(v795, v799, vdupq_n_s32(*((_QWORD *)v797 - 1)));
        v796 = vmlaq_s32(v796, vaddq_s32(v799, vdupq_n_s32(8)), vdupq_n_s32(*(_QWORD *)v797));
        v797 += 16;
      }
      while ( v798 );
      v776 = vaddvq_s32(vaddq_s32(v796, v795));
      if ( v792 != v775 )
      {
LABEL_837:
        v800 = v775 - v792;
        v801 = &v953[2 * (v792 + v791)];
        v802 = v553 + 2 * v792 + 2 - v590;
        do
        {
          v803 = *(int16_t *)v801;
          v801 += 2;
          --v800;
          v776 += v802 * v803;
          v802 += 2;
        }
        while ( v800 );
      }
    }
    v804 = v774 - (v869 >> 5);
    v805 = v776 / (int)(2 * v775) + 1024;
    v806 = ((uint64_t)(-715827883LL * (v805 >> 2)) >> 32)
         + ((uint64_t)(-715827883LL * (v805 >> 2)) >> 63);
    if ( v805 > 12311 )
      LOWORD(v806) = -512;
    if ( v805 >= -12308 )
      v807 = v806;
    else
      v807 = 512;
    v808 = (((int16_t)(v804 + v807) + 128) >> 8) & ~(((int16_t)(v804 + v807) + 128) >> 31);
    if ( v808 >= 10 )
      v595 = 10;
    else
      v595 = v808;
    ec_enc_icdf((int64_t *)&v909, v595, (int64_t)&unk_16BA8, 7);
    ec_tell_frac((int64_t)&v909);
LABEL_848:
    v809 = v899 + ~(unsigned int)ec_tell_frac((int64_t)&v909);
    v810 = v902 != 0;
    v811 = v809 > 39;
    v273 = (v810 && v811) == 0;
    v812 = ~v553;
    v813 = v810 && v811;
    v814 = v553;
    if ( v273 )
      v815 = 0;
    else
      v815 = 8;
    v816 = compute_allocation(
             v901,
             *(_DWORD *)(v143 + 20) - v814,
             (int64_t)&v936,
             v908,
             v595,
             v588,
             &v915,
             v809 - v815,
             &v914,
             (int32x4_t *)&v942,
             (int64_t)v957,
             (int64_t)v956,
             (int64_t *)&v909,
             *(_DWORD *)(v143 + 44),
             *(_DWORD *)(v143 + 20) + v812,
             v884);
    v817 = *(_DWORD *)(v143 + 44);
    v5 = v873;
    v818 = v816;
    v819 = v816;
    if ( v817 )
    {
      v820 = v817 - 1;
      if ( v817 - 1 <= v816 )
        v820 = v816;
      if ( v817 + 1 < v820 )
        v819 = v817 + 1;
      else
        v819 = v820;
    }
    v821 = *(_DWORD *)(v143 + 20) - v905;
    *(_DWORD *)(v143 + 44) = v819;
    quant_fine_energy((int64_t *)v901, v821, (int64_t)v889, (int64_t)&v948, (int64_t)v957, (int64_t *)&v909, v594);
    quant_all_bands(
      v901,
      *(_DWORD *)(v143 + 20) - v905,
      (int64_t)dword_2EDB0,
      (int64_t)&v932,
      (int64_t)&v954,
      (int64_t)&v942,
      v876,
      *(_DWORD *)(v143 + 32),
      v915,
      *(_DWORD *)(v143 + 80),
      (int64_t)&v933,
      v899 - v815,
      v914,
      (int64_t)&v909,
      v818,
      (int *)(v143 + 28));
    if ( v813 )
      ec_enc_bits((int64_t *)&v909, *(_DWORD *)(v143 + 64) < 2, 1);
    v822 = v911;
    v823 = *(_DWORD *)(v143 + 20) - v905;
    v824 = ec_ilog(v912);
    quant_energy_finalise(
      (int64_t *)v901,
      v823,
      (int64_t)v889,
      (int64_t)&v948,
      (int64_t)v957,
      (int64_t)v956,
      v894 - v822 + v824,
      (int64_t *)&v909,
      v594);
    if ( !((v883 ^ 1 | ((int)v882 < 1)) & 1) )
    {
      if ( (unsigned int)v882 < 0x10 )
      {
        v825 = 0LL;
        goto LABEL_865;
      }
      v825 = (unsigned int)v882 & 0xFFFFFFF0;
      v826 = (_OWORD *)(v143 + 4LL * v879 + 312);
      *(_QWORD *)&v827 = -8070292200157573120LL;
      *((_QWORD *)&v827 + 1) = -8070292200157573120LL;
      v828 = (unsigned int)v882 & 0xFFFFFFF0;
      do
      {
        *(v826 - 1) = v827;
        *v826 = v827;
        v828 -= 16LL;
        v826 += 2;
      }
      while ( v828 );
      if ( v825 != (unsigned int)v882 )
      {
LABEL_865:
        v829 = (unsigned int)v882 - v825;
        v830 = (_WORD *)(v143 + 4LL * v879 + 2 * v825 + 296);
        do
        {
          --v829;
          *v830 = -28672;
          ++v830;
        }
        while ( v829 );
      }
    }
    if ( (_DWORD)v905 )
    {
      v831 = (int)v888 - (int)v905;
      v832 = v831 + 1 > v888 ? v831 + 1 : v888;
      v833 = v832 - v831;
      if ( v833 < 0x10 )
        goto LABEL_958;
      v834 = v831 + 1 > v888 ? v831 + 1 : v888;
      v835 = v143 + 4LL * v879 + 2 * v831;
      v836 = v143 + 4LL * v879 + 2 * (v888 + v831);
      if ( v835 + 296 < (uint64_t)(v143 + 4LL * v879 + 2 * (v834 + v888) + 296)
        && v836 + 296 < (uint64_t)(v143 + 4LL * v879 + 2 * v834 + 296) )
      {
        goto LABEL_958;
      }
      v837 = (_OWORD *)(v835 + 312);
      v838 = (_OWORD *)(v836 + 312);
      v831 += v833 & 0xFFFFFFFFFFFFFFF0LL;
      *(_QWORD *)&v839 = -8070292200157573120LL;
      *((_QWORD *)&v839 + 1) = -8070292200157573120LL;
      v840 = v833 & 0xFFFFFFFFFFFFFFF0LL;
      do
      {
        *(v837 - 1) = v839;
        *v837 = v839;
        *(v838 - 1) = v839;
        *v838 = v839;
        v840 -= 16LL;
        v837 += 2;
        v838 += 2;
      }
      while ( v840 );
      if ( v833 != (v833 & 0xFFFFFFFFFFFFFFF0LL) )
      {
LABEL_958:
        v841 = v143 + 4LL * v879;
        v842 = 2 * (v831 + v888) + 296;
        do
        {
          v843 = v841 + 2 * v831++;
          *(_WORD *)(v843 + 296) = -28672;
          *(_WORD *)(v841 + v842) = -28672;
          v842 += 2LL;
        }
        while ( v831 < v888 );
      }
    }
    previous_uhq_index = v905;
    *(_DWORD *)(v143 + 56) = v870;
    *(_WORD *)(v143 + 60) = v872;
    LODWORD(v844) = 2 * v888;
    if ( !(_DWORD)v902 )
    {
      if ( (int)v844 < 1 )
        goto LABEL_900;
      v844 = (unsigned int)v844;
      if ( (unsigned int)v844 > 0xF
        && ((v852 = 4LL * v879 + 2 * v882, v143 + v852 + 296 >= (uint64_t)(v143 + 4LL * v879 + 2 * v844 + 296))
         || v143 + 4LL * v879 + 296 >= (uint64_t)(v143 + v852 + 2 * v844 + 296)) )
      {
        v853 = (unsigned int)v844 & 0xFFFFFFF0;
        v863 = (__int128_t *)(v143 + 4LL * v879 + 312);
        v864 = (unsigned int)v844 & 0xFFFFFFF0;
        do
        {
          v865 = *(v863 - 1);
          v866 = *v863;
          v867 = (__int128_t *)((char *)v863 + 2 * v882);
          v864 -= 16LL;
          v863 += 2;
          *(v867 - 1) = v865;
          *v867 = v866;
        }
        while ( v864 );
        if ( v853 == v844 )
          goto LABEL_900;
      }
      else
      {
        v853 = 0LL;
      }
      v854 = (_WORD *)(v143 + 4LL * v879 + 2 * v853 + 296);
      v855 = v844 - v853;
      do
      {
        --v855;
        v854[v882] = *v854;
        ++v854;
      }
      while ( v855 );
      goto LABEL_900;
    }
    if ( (int)v844 >= 1 )
    {
      v844 = (unsigned int)v844;
      if ( (unsigned int)v844 > 7
        && ((v845 = 4LL * v879 + 2 * v882, v143 + v845 + 296 >= (uint64_t)(v143 + 4LL * v879 + 2 * v844 + 296))
         || v143 + 4LL * v879 + 296 >= (uint64_t)(v143 + v845 + 2 * v844 + 296)) )
      {
        v846 = (unsigned int)v844 & 0xFFFFFFF8;
        v859 = 2 * v882;
        v860 = (_OWORD *)(v143 + 4LL * v879 + 296);
        v861 = (unsigned int)v844 & 0xFFFFFFF8;
        do
        {
          v862 = *(_OWORD *)((char *)v860 + v859);
          v861 -= 8LL;
          LOWORD(v862) = (v862 < *v860) ? v862 : *v860;
          *(_OWORD *)((char *)v860 + v859) = v862;
          ++v860;
        }
        while ( v861 );
        if ( v846 != v844 )
          goto LABEL_888;
      }
      else
      {
        v846 = 0LL;
LABEL_888:
        v847 = v844 - v846;
        v848 = (_WORD *)(v143 + 4LL * v879 + 2 * v846 + 296);
        v849 = v882;
        do
        {
          v850 = (int16_t)v848[v849];
          v851 = (int16_t)*v848;
          if ( v850 >= v851 )
            LOWORD(v850) = *v848;
          --v847;
          v848[v849] = v850;
          ++v848;
        }
        while ( v847 );
      }
    }
LABEL_900:
    v856 = v902 | v871;
    if ( (unsigned int)v902 | v871 )
      v856 = *(_DWORD *)(v143 + 64) + 1;
    *(_DWORD *)(v143 + 64) = v856;
    *(_DWORD *)(v143 + 28) = v912;
    ec_enc_done((int64_t *)&v909);
    v857 = *(uint16_t *)(v143 + 212);
    v858 = v857 == 255 ? 0 : v857 + 1;
    *(_WORD *)(v143 + 212) = v858;
    result = v913 ? 4294967293LL : (uint64_t)(unsigned int)(v893 + 4);
    ++count_for_debug;
LABEL_909:
    if ( *(_QWORD *)(v5 + 40) == v958 )
      return result;
LABEL_945:
    if ( v926 + v918 > 12001 )
    {
      v175 = 3LL;
      v174 = 96;
      goto LABEL_288;
    }
    if ( v925 + v917 > 12001 )
    {
      v175 = 3LL;
      v174 = 64;
      goto LABEL_288;
    }
    if ( v924 + v916 > 12001 )
    {
      v175 = 3LL;
LABEL_287:
      v174 = 32;
LABEL_288:
      v143 = v900;
      v153 = v901;
      v152 = v896;
      v151 = v893;
LABEL_289:
      v161 = v886;
      v173 = v887;
      goto LABEL_290;
    }
    v223 = v875;
    v143 = v900;
    v153 = v901;
    v152 = v896;
    v151 = v893;
    v161 = v886;
    v173 = v887;
    v174 = 32;
    LOBYTE(v224) = *(_BYTE *)(v875 + 2) + 12;
    v905 = 3LL;
  }
}