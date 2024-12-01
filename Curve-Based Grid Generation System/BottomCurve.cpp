// Finally it is the implementation of the class BottomCurve!

#include <cmath>

#include "BottomCurve.hpp"

// My function from the Assignment 3
double BottomCurve::f(double x) const {
    if (x < -3.0) {
        return 0.5 / (1.0 + std::exp(-3.0 * (x + 6)));
    } else {
        return 0.5 / (1.0 + std::exp(3.0 * x));
    }
}

double BottomCurve::fprime(double x) const {

    if (x < -3.0) {
        double exp_term = std::exp(-3.0 * (x + 6));
        double denom = 1.0 + exp_term;
        double numerator = 3.0 * exp_term;
        return numerator / (2.0 * denom * denom);
    } 
    
    else {
        double exp_term = std::exp(3.0 * x);
        double denom = 1.0 + exp_term;
        double numerator = 3.0 * exp_term;
        return -numerator / (2.0 * denom * denom);
    }
}

// Implement the pure virtual functions from the EquationCurve class.
Point BottomCurve::gamma(double t) const {

    double x = -10.0 * (1.0 - t) + 5.0 * t;
    double y = f(x);
    return Point(x, y);
}

Point BottomCurve::gammaprime(double t) const {

    double x = -10.0 * (1.0 - t) + 5.0 * t;

    double dx_dt = 15.0;
    double dy_dt = fprime(x) * dx_dt; //Chain rule!
    
    return Point(dx_dt, dy_dt);
}