#ifndef CURVE_HPP
#define CURVE_HPP

#include "Point.hpp"

class Curve {
public:

    virtual ~Curve() = default;
    virtual Point at(double t) const = 0;

};

#endif