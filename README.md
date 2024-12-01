# Adaptive Simpson Integration

An implementation of the Adaptive Simpson Algorithm in C++ for numerical integration with error control. 

![Simpson's Rule Visualization](https://upload.wikimedia.org/wikipedia/commons/0/0f/Simpsons_method_illustration.svg)

## Features

- Adaptive Simpson integration method implementation
- Error-controlled integration
- Support for custom integrand functions
- Unit testing with utest framework
- Performance metrics tracking (function calls)
- Exception handling for invalid inputs

## Requirements

- C++ compiler (g++ recommended)
- Standard C++ libraries
- utest.h (included in the repository)

## Project Structure

```
.
├── my_functions.h       # Core integration functions and utilities
├── compute.cpp         # Main program implementation
├── tests.cpp          # Unit tests implementation
├── utest.h           # Unit testing framework
└── README.md         # This file
```

## Building and Running

### Compiling the Main Program

```bash
g++ -o computename compute.cpp
```

### Running the Program

```bash
./computename
```

### Compiling and Running Tests

```bash
g++ -o testname tests.cpp
./testname
```

## Usage Example

The program is designed to compute integrals numerically. Here's a basic example:

```cpp
// Define your function
inline double function(double x) {
    return x + cos(pow(x, 5));
}

// Use the quadrature function
int countFunctionCalls = 0;
double integralValue = quadrature(function, &countFunctionCalls, 0, M_PI, 1e-9);
```

## Integration Parameters

- `function`: The integrand function
- `countFunctionCalls`: Pointer to track function evaluations
- `a`: Lower integration bound
- `b`: Upper integration bound
- `tolerance`: Error tolerance (must be > 0)

## Error Control

The algorithm implements error control through:
- Adaptive subdivision of intervals
- Error estimation between successive approximations
- Tolerance-based termination criteria

## Performance Characteristics

The implementation shows the following characteristics based on tolerance levels:

| Tolerance (τ) | Accuracy | Function Calls |
|--------------|----------|----------------|
| 10^-2        | ~0.17    | 1380          |
| 10^-3        | ~0.001   | 4332          |
| 10^-4        | ~10^-6   | 8412          |

## Testing

The project includes unit tests to verify:
- Correctness of integration for known cases
- Proper error handling for invalid inputs
- Numerical accuracy within specified tolerances

Run the tests to ensure everything is working correctly:

```bash
./testname
```

## Acknowledgments

- [Reference implementation of Simpson's rule](https://en.wikipedia.org/wiki/Simpson%27s_rule)
- utest framework developers

## References

1. [Inline Functions (C++) — Microsoft Learn](https://learn.microsoft.com/en-us/cpp/cpp/inline-functions-cpp?view=msvc-170)
2. [std::function - cppreference.com](https://en.cppreference.com/w/cpp/utility/functional/function)