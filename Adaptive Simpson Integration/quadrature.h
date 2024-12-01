#ifndef QUADRATURE_H
#define QUADRATURE_H

#include <cmath>
#include <stdexcept>
#include <iostream>

template <typename Func>
inline double computeSimpson(Func f, int* evalCounter, double a, double b) {
    *evalCounter += 4;
    return ((b - a) / 6) * (f(a) + 4 * f((a + b) / 2) + f(b));
}

template <typename Func>
double simpsonAdaptive(Func f, int* evalCounter, double a, double b, double tol, int depth = 0, int maxDepth = 1000) {
    if (tol <= 0) {
        throw std::underflow_error("Tolerance too small: " + std::to_string(tol));
    }
    if (depth >= maxDepth) {
        throw std::runtime_error("Maximum recursion depth reached.");
    }

    double mid = (a + b) / 2;
    double I1 = computeSimpson(f, evalCounter, a, b);
    double I2 = computeSimpson(f, evalCounter, a, mid) + computeSimpson(f, evalCounter, mid, b);

    double error = std::abs(I1 - I2);

    if (error < 15 * tol) {
        return I2;
    } else {
        return simpsonAdaptive(f, evalCounter, a, mid, tol / 2, depth + 1, maxDepth) +
               simpsonAdaptive(f, evalCounter, mid, b, tol / 2, depth + 1, maxDepth);
    }
}

#endif