#include <fstream>
#include <iostream>

#include "Domain.hpp"

void Domain::generateGrid(int n) {

    double h = 1.0 / n;
    grid.resize(n + 1, std::vector<Point>(n + 1));

    for (int i = 0; i <= n; i++) {
        double r = i * h;
        for (int j = 0; j <= n; j++) {
            double s = j * h;
            grid[i][j] = computeGridPoint(r, s);
        }
    }
}

Point Domain::computeGridPoint(double r, double s) const {

    // C0: bottom, C1: right, C2: top, C3: left

    Point C0_s = boundaries[0]->at(s);        // Bottom curve at s (left to right)

    Point C1_s = boundaries[1]->at(s);        // Right curve at s (bottom to top)

    Point C2_r = boundaries[2]->at(1.0 - r);  // Top curve at (1 - r) (right to left)

    Point C3_r = boundaries[3]->at(r);        // Left curve at r (bottom to top)

    // Compute corner points
    Point P0 = boundaries[0]->at(0.0); // Bottom-left corner
    Point P1 = boundaries[0]->at(1.0); // Bottom-right corner

    Point P2 = boundaries[2]->at(0.0); // Top-right corner
    Point P3 = boundaries[2]->at(1.0); // Top-left corner

    //Interpolation
    Point term1 = Point((1 - r) * C0_s.x + r * C1_s.x, (1 - r) * C0_s.y + r * C1_s.y);

    Point term2 = Point((1 - s) * C3_r.x + s * C2_r.x, (1 - s) * C3_r.y + s * C2_r.y);

    Point term3 = Point(
        (1 - r) * (1 - s) * P0.x + r * (1 - s) * P1.x + r * s * P2.x + (1 - r) * s * P3.x,
        (1 - r) * (1 - s) * P0.y + r * (1 - s) * P1.y + r * s * P2.y + (1 - r) * s * P3.y
    );

    double x = term1.x + term2.x - term3.x;
    double y = term1.y + term2.y - term3.y;

    return Point(x, y);
}

void Domain::saveToFiles(const std::string& x_file, const std::string& y_file) const {

    std::ofstream x_out(x_file);
    std::ofstream y_out(y_file);

    if (!x_out.is_open() || !y_out.is_open()) {
        std::cerr << "Error opening output files." << std::endl;
        return;
    }

    int n = grid.size() - 1;

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            x_out << grid[i][j].x;
            y_out << grid[i][j].y;
            if (j < n) {
                x_out << " ";
                y_out << " ";
            }
        }
        x_out << "\n";
        y_out << "\n";
    }
}