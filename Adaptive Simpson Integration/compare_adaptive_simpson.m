% Define the function to integrate
f = @(x) x + cos(x.^5);

% Set the integration limits
a = 0;
b = pi;

% Set the desired tolerance
tolerance = 1e-8;

% Use MATLAB's integral function with specified tolerance
I = integral(f, a, b, 'AbsTol', tolerance);

% Display the result
fprintf('The integral value computed by MATLAB is: %.10f\n', I);
