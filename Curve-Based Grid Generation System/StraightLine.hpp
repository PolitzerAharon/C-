#ifndef STRAIGHT_LINE_HPP
#define STRAIGHT_LINE_HPP

#include "Curve.hpp"

class StraightLine : public Curve {

private:

    Point start_;
    Point end_;

public:

    StraightLine(const Point& start, const Point& end)
        : start_(start), end_(end) {}
    
    Point at(double t) const override {
        // Have to be careful to keep the parameter t in the range [0,1]
        if (t < 0.0 || t > 1.0) { 
            throw std::domain_error("Parameter t must be in [0,1]");
        }
        // Basic linear interpolation
        return Point(
            start_.x * (1 - t) + end_.x * t,
            start_.y * (1 - t) + end_.y * t
        );
    }
};

#endif