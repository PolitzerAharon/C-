#ifndef BOTTOM_CURVE_HPP
#define BOTTOM_CURVE_HPP

#include "EquationCurve.hpp"

class BottomCurve : public EquationCurve {
public:

    BottomCurve(bool enable_cache = true)
        : EquationCurve(enable_cache) {}

protected:

    // Overridden pure virtual functions
    Point gamma(double t) const override;
    Point gammaprime(double t) const override;

private:

    double f(double x) const;
    double fprime(double x) const;
};

#endif