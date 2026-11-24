#include <iostream>
#include <vector>
#include "Interpolation.h"

int main() {
    // Вузлові точки для f(x) = x^2
    std::vector<double> xs = {0.0, 1.0, 2.0, 3.0};
    std::vector<double> ys = {0.0, 1.0, 4.0, 9.0};

    double x = 1.5;
    double exact = x * x; // 2.25
    double y_lagr = interp::lagrange(xs.data(), ys.data(), xs.size(), x);
    double y_lin  = interp::linearInterpolation(xs.data(), ys.data(), xs.size(), x);

    std::cout << "Point x = " << x << " (exact = " << exact << ")\n";
    std::cout << "Lagrange = " << y_lagr
              << ", error = " << interp::interpolationError(exact, y_lagr) << "\n";
    std::cout << "Linear   = " << y_lin
              << ", error = " << interp::interpolationError(exact, y_lin) << "\n";

    std::vector<double> queries = {0.5, 1.5, 2.5};
    std::vector<double> results(queries.size(), 0.0);
    std::size_t count = 0;

    int rc = interp::interpolate(xs.data(), ys.data(), xs.size(),
                                 queries.data(), queries.size(),
                                 results.data(), results.size(), &count, 1);
    std::cout << "Batch Lagrange rc = " << rc << ", count = " << count << ": ";
    for (std::size_t i = 0; i < count; ++i) std::cout << results[i] << " ";
    std::cout << "\n";

    return 0;
}