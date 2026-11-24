#pragma once
#include <cstddef>

namespace interp {

// Обчислення полінома Лагранжа у точці x за вузлами (xs[i], ys[i]) довжини n
double lagrange(const double* xs, const double* ys, std::size_t n, double x);

// Кусково-лінійна інтерполяція у точці x за впорядкованими за зростанням xs вузлами
double linearInterpolation(const double* xs, const double* ys, std::size_t n, double x);

// Пакетна інтерполяція для масиву точок query_xs (розміру m) у буфер out_ys (місткості out_cap)
// mode: 0 — лінійна інтерполяція, 1 — інтерполяція Лагранжа
// Повертає: 0 — успіх, -1 — некоректні вхідні дані, -2 — замалий буфер out_ys
int interpolate(const double* xs, const double* ys, std::size_t n,
                const double* query_xs, std::size_t m,
                double* out_ys, std::size_t out_cap, std::size_t* out_count,
                int mode);

// Абсолютна похибка |approx_y - exact_y|
double interpolationError(double exact_y, double approx_y);

} // namespace interp