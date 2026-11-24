#pragma once
#include <stddef.h>

#if defined(_WIN32) || defined(_WIN64)
  #ifdef INTERPOLATION_EXPORTS
    #define INTERP_API extern "C" __declspec(dllexport)
  #else
    #define INTERP_API extern "C" __declspec(dllimport)
  #endif
#else
  #define INTERP_API extern "C"
#endif

INTERP_API double interp_lagrange(const double* xs, const double* ys, size_t n, double x);
INTERP_API double interp_linear(const double* xs, const double* ys, size_t n, double x);
INTERP_API int interp_batch(const double* xs, const double* ys, size_t n,
                            const double* query_xs, size_t m,
                            double* out_ys, size_t out_cap, size_t* out_count,
                            int mode);
INTERP_API double interp_error(double exact_y, double approx_y);