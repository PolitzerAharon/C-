#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>

class Point {
public:

    double x;
    double y;

    Point() : x(0.0), y(0.0) {}

    Point(double xCoord, double yCoord) : x(xCoord), y(yCoord) {}

    void print() const{
      std::cout << "Point(" << x << ", " << y << ")" << std::endl;
    }

};

#endif