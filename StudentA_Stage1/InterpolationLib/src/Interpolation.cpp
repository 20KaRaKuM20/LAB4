#include "Interpolation.h"
#include <cmath>
#include <limits>

namespace interp {

namespace {
constexpr double kNaN = std::numeric_limits<double>::quiet_NaN();

bool isValidNodes(const double* xs, const double* ys, std::size_t n) {
    if (!xs || !ys || n == 0) return false;
    for (std::size_t i = 0; i < n; ++i) {
        if (!std::isfinite(xs[i]) || !std::isfinite(ys[i])) return false;
    }
    return true;
}

bool hasDuplicateX(const double* xs, std::size_t n) {
    for (std::size_t i = 0; i < n; ++i) {
        for (std::size_t j = i + 1; j < n; ++j) {
            if (std::fabs(xs[i] - xs[j]) < 1e-12) return true;
        }
    }
    return false;
}
} // namespace

double lagrange(const double* xs, const double* ys, std::size_t n, double x) {
    if (!isValidNodes(xs, ys, n) || !std::isfinite(x)) return kNaN;
    if (n == 1) return ys[0];
    if (hasDuplicateX(xs, n)) return kNaN;

    double result = 0.0;
    for (std::size_t i = 0; i < n; ++i) {
        double term = ys[i];
        for (std::size_t j = 0; j < n; ++j) {
            if (i == j) continue;
            double denom = xs[i] - xs[j];
            if (std::fabs(denom) < 1e-15) return kNaN;
            term *= (x - xs[j]) / denom;
        }
        result += term;
    }
    return result;
}

double linearInterpolation(const double* xs, const double* ys, std::size_t n, double x) {
    if (!isValidNodes(xs, ys, n) || !std::isfinite(x)) return kNaN;
    if (n == 1) return ys[0];

    if (x <= xs[0]) {
        double dx = xs[1] - xs[0];
        if (std::fabs(dx) < 1e-15) return ys[0];
        return ys[0] + (ys[1] - ys[0]) * (x - xs[0]) / dx;
    }
    if (x >= xs[n - 1]) {
        double dx = xs[n - 1] - xs[n - 2];
        if (std::fabs(dx) < 1e-15) return ys[n - 1];
        return ys[n - 2] + (ys[n - 1] - ys[n - 2]) * (x - xs[n - 2]) / dx;
    }

    for (std::size_t i = 0; i + 1 < n; ++i) {
        if (x >= xs[i] && x <= xs[i + 1]) {
            double dx = xs[i + 1] - xs[i];
            if (std::fabs(dx) < 1e-15) return ys[i];
            return ys[i] + ((x - xs[i]) / dx) * (ys[i + 1] - ys[i]);
        }
    }
    return kNaN;
}

int interpolate(const double* xs, const double* ys, std::size_t n,
                const double* query_xs, std::size_t m,
                double* out_ys, std::size_t out_cap, std::size_t* out_count,
                int mode) {
    if (out_count) *out_count = 0;
    if (!isValidNodes(xs, ys, n) || !query_xs || !out_ys || m == 0 || !out_count) return -1;
    if (out_cap < m) return -2;
    if (mode != 0 && mode != 1) return -1;
    if (mode == 1 && hasDuplicateX(xs, n)) return -1;

    for (std::size_t i = 0; i < m; ++i) {
        if (!std::isfinite(query_xs[i])) return -1;
        double val = (mode == 0)
            ? linearInterpolation(xs, ys, n, query_xs[i])
            : lagrange(xs, ys, n, query_xs[i]);
        if (!std::isfinite(val)) return -1;
        out_ys[i] = val;
    }
    *out_count = m;
    return 0;
}

double interpolationError(double exact_y, double approx_y) {
    if (!std::isfinite(exact_y) || !std::isfinite(approx_y)) return kNaN;
    return std::fabs(exact_y - approx_y);
}

} // namespace interp