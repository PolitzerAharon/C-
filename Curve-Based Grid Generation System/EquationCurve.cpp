#include <cmath>
#include <iostream>
#include <boost/math/quadrature/gauss_kronrod.hpp>

#include "EquationCurve.hpp"

using namespace boost::math::quadrature;

Point EquationCurve::at(double t) const {
    
    // Check cache first
    if (cache_enabled) {
        
        auto it = point_cache.find(t);

        if (it != point_cache.end()) {

            return it->second;
        }
    }

    // Compute the total arc length if not already computed -> -1.0 to indicate that it has not been computed yet 
    if (total_arc_length < 0.0) {
        total_arc_length = computeArcLength(0.0, 1.0);
    }

    //Compute the point at parameter t
    double s = t * total_arc_length;

    //NEWTON-RAPHSON METHOD-------------------------------------------------------------------------------------
    double u = t;
    const double tol = 1e-6;
    const int max_iter = 100;
    int iter = 0;

    while (iter < max_iter) {
        double u_length = computeArcLength(0.0, u);
        double func = u_length - s;

        if (std::abs(func) < tol) {
            break;
        }

        double derivative = computeArcLengthIntegrand(u);
        if (derivative == 0.0) {
            std::cerr << "Derivative zero in Newton-Raphson method" << std::endl;
            break;
        }

        u = u - func / derivative;

        // Do not let u go out of bounds!
        if (u < 0.0) u = 0.0;
        if (u > 1.0) u = 1.0;

        iter++;
    }

    Point p = gamma(u);

    // Save the result!
    if (cache_enabled) {
        point_cache[t] = p;
    }

    return p;
}

// https://www.boost.org/doc/libs/1_86_0/libs/math/doc/html/math_toolkit/gauss_kronrod.html
double EquationCurve::computeArcLength(double a, double b) const {

    auto integrand = [this](double t) -> double {
        return computeArcLengthIntegrand(t);
    };

    double error = 0.0;
    unsigned max_depth = 15;
    double tol = 1e-6;

    double result = gauss_kronrod<double, 15>::integrate(
        integrand, a, b, max_depth, tol, &error
    );

    return result;
}

double EquationCurve::computeArcLengthIntegrand(double t) const {
    Point gp = gammaprime(t);
    return std::sqrt(gp.x * gp.x + gp.y * gp.y);
}