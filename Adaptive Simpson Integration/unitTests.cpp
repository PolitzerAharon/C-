#include <iostream>
#include <stdexcept>
#include <cmath>
#include "utest.h"
#include "quadrature.h" 
using namespace std;

UTEST(simpson, check_integral_value) {
    int evalCounter = 0;
    auto identityFunction = [](double x) {
        return x;
    };

    double integralValue = simpsonAdaptive(identityFunction, &evalCounter, 0, 1, 1e-9);
    double expectedValue = 0.5;

    ASSERT_NEAR(integralValue, expectedValue, 1e-9);
}

UTEST(simpson, check_negative_tau) {
    int evalCounter = 0;
    auto identityFunction = [](double x) {
        return x;
    };

    ASSERT_EXCEPTION(simpsonAdaptive(identityFunction, &evalCounter, 0, 1, 0), std::underflow_error);
    ASSERT_EXCEPTION(simpsonAdaptive(identityFunction, &evalCounter, 0, 1, -1e-9), std::underflow_error);
}

UTEST_MAIN();