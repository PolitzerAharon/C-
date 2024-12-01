#include <memory>
#include <iostream>
#include <chrono>

#include "Point.hpp"

#include "Curve.hpp"
#include "StraightLine.hpp"
#include "BottomCurve.hpp"

#include "Domain.hpp"


int main() {
    // Define corner points
    Point p0(-10.0, 0.0); // Bottom-left
    Point p1(5.0, 0.0);   // Bottom-right
    Point p2(5.0, 3.0);   // Top-right
    Point p3(-10.0, 3.0); // Top-left

    // Create boundary curves with caching enabled
    std::shared_ptr<Curve> bottomCurve = std::make_shared<BottomCurve>(true);
    std::shared_ptr<Curve> rightCurve = std::make_shared<StraightLine>(p1, p2); // Bottom to top
    std::shared_ptr<Curve> topCurve = std::make_shared<StraightLine>(p2, p3);   // Right to left
    std::shared_ptr<Curve> leftCurve = std::make_shared<StraightLine>(p0, p3);  // Bottom to top (corrected)

    // Create domain with cache
    Domain domain_with_cache(bottomCurve, rightCurve, topCurve, leftCurve);

    // Generate grid with cache
    int n = 25;
    auto start_time = std::chrono::high_resolution_clock::now();
    domain_with_cache.generateGrid(n);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_with_cache = end_time - start_time;
    std::cout << "Grid generation time with cache: " << elapsed_with_cache.count() << " seconds" << std::endl;

    // Save to files
    domain_with_cache.saveToFiles("x_grid_cache.txt", "y_grid_cache.txt");

    // Create bottom curve without caching
    std::shared_ptr<Curve> bottomCurve_no_cache = std::make_shared<BottomCurve>(false);

    // Create domain without cache
    Domain domain_no_cache(bottomCurve_no_cache, rightCurve, topCurve, leftCurve);

    // Generate grid without cache
    start_time = std::chrono::high_resolution_clock::now();
    domain_no_cache.generateGrid(n);
    end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_no_cache = end_time - start_time;
    std::cout << "Grid generation time without cache: " << elapsed_no_cache.count() << " seconds" << std::endl;

    // Save to files
    domain_no_cache.saveToFiles("x_grid_no_cache.txt", "y_grid_no_cache.txt");

    return 0;
}