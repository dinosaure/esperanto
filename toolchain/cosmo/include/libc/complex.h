#ifndef _COMPLEX_H
#define _COMPLEX_H
COSMOPOLITAN_C_START_
#if __STDC_VERSION__ + 0 >= 201112 && !defined(__STDC_NO_COMPLEX__)

#define complex   _Complex
#define imaginary _Imaginary

double cabs(complex double);
double carg(complex double);
double cimag(complex double);
double creal(complex double);

float cabsf(complex float);
float cargf(complex float);
float cimagf(complex float);
float crealf(complex float);

long double cabsl(complex long double);
long double cargl(complex long double);
long double cimagl(complex long double);
long double creall(complex long double);

complex double cacos(complex double);
complex double cacosh(complex double);
complex double casin(complex double);
complex double casinh(complex double);
complex double catan(complex double);
complex double catanh(complex double);
complex double ccos(complex double);
complex double ccosh(complex double);
complex double cexp(complex double);
complex double cexp2(complex double);
complex double clog(complex double);
complex double conj(complex double);
complex double cpow(complex double, complex double);
complex double cproj(complex double);
complex double csin(complex double);
complex double csinh(complex double);
complex double csqrt(complex double);
complex double ctan(complex double);
complex double ctanh(complex double);

complex float cacosf(complex float);
complex float cacoshf(complex float);
complex float casinf(complex float);
complex float casinhf(complex float);
complex float catanf(complex float);
complex float catanhf(complex float);
complex float ccosf(complex float);
complex float ccoshf(complex float);
complex float cexpf(complex float);
complex float cexp2f(complex float);
complex float clogf(complex float);
complex float conjf(complex float);
complex float cpowf(complex float, complex float);
complex float cprojf(complex float);
complex float csinf(complex float);
complex float csinhf(complex float);
complex float csqrtf(complex float);
complex float ctanf(complex float);
complex float ctanhf(complex float);

complex long double cprojl(complex long double);
complex long double csinhl(complex long double);
complex long double csinl(complex long double);
complex long double csqrtl(complex long double);
complex long double ctanhl(complex long double);
complex long double ctanl(complex long double);
complex long double cacoshl(complex long double);
complex long double cacosl(complex long double);
complex long double casinhl(complex long double);
complex long double casinl(complex long double);
complex long double catanhl(complex long double);
complex long double catanl(complex long double);
complex long double ccoshl(complex long double);
complex long double ccosl(complex long double);
complex long double cexpl(complex long double);
complex long double cexp2l(complex long double);
complex long double clogl(complex long double);
complex long double conjl(complex long double);
complex long double cpowl(complex long double, complex long double);

#ifndef __cplusplus
#define __CIMAG(x, t)   \
  (+(union {            \
      _Complex t __z;   \
      t __xy[2];        \
    }){(_Complex t)(x)} \
        .__xy[1])
#define creal(x)  ((double)(x))
#define crealf(x) ((float)(x))
#define creall(x) ((long double)(x))
#define cimag(x)  __CIMAG(x, double)
#define cimagf(x) __CIMAG(x, float)
#define cimagl(x) __CIMAG(x, long double)
#endif

#ifdef __GNUC__
#define _Complex_I (__extension__(0.0f + 1.0fi))
#else
#define _Complex_I (0.0f + 1.0fi)
#endif

#ifdef _Imaginary_I
#define __CMPLX(x, y, t) ((t)(x) + _Imaginary_I * (t)(y))
#elif defined(__clang__)
#define __CMPLX(x, y, t) (+(_Complex t){(t)(x), (t)(y)})
#else
#define __CMPLX(x, y, t) (__builtin_complex((t)(x), (t)(y)))
#endif

#define CMPLX(x, y)  __CMPLX(x, y, double)
#define CMPLXF(x, y) __CMPLX(x, y, float)
#define CMPLXL(x, y) __CMPLX(x, y, long double)

#endif /* C11 */
COSMOPOLITAN_C_END_
#endif /* _COMPLEX_H */
