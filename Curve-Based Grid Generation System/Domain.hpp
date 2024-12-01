#ifndef DOMAIN_HPP
#define DOMAIN_HPP

#include <array>
#include <vector>
#include <memory>
#include <string>

#include "Curve.hpp"
#include "Point.hpp"

class Domain {

private:

    std::array<std::shared_ptr<Curve>, 4> boundaries;
    std::vector<std::vector<Point>> grid;

public:

    Domain(std::shared_ptr<Curve> bottom, std::shared_ptr<Curve> right,
           std::shared_ptr<Curve> top, std::shared_ptr<Curve> left)
        : boundaries{bottom, right, top, left} {}

    void generateGrid(int n);
    void saveToFiles(const std::string& x_file, const std::string& y_file) const;

private:

    Point computeGridPoint(double r, double s) const;
    
};

#endif