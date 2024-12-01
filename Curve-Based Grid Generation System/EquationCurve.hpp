#ifndef EQUATION_CURVE_HPP
#define EQUATION_CURVE_HPP

#include <unordered_map> 
#include "Curve.hpp"

class EquationCurve : public Curve {
    
public:

    EquationCurve(bool enable_cache = true)
        : cache_enabled(enable_cache) {}

    virtual ~EquationCurve() = default;

    Point at(double t) const override;

protected:

    // Pure virtual functions that must be implemented by the subclasses
    virtual Point gamma(double t) const = 0;
    virtual Point gammaprime(double t) const = 0;

private:

    // 1. Will need to compute the point at parameter t
    Point computePoint(double t) const; 

    // 2. Will need to compute the arc length between two points
    double computeArcLength(double a, double b) const; 

    // 3. Will need to compute the integrand of the arc length
    double computeArcLengthIntegrand(double t) const;

    // Private member variables:
    mutable std::unordered_map<double, Point> point_cache;
    mutable double total_arc_length = -1.0;
    bool cache_enabled;
};

#endif