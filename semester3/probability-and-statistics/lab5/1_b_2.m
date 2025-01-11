clc;
clear all;

X = [7, 7, 4, 5, 9, 9, 4, 12, 8, 1, 8, 7, 3, 13, 2, 1, 17, 7, 12, 5, 6, 2, 1, 13, 14, 10, 2, 4, 9, 11, 3, 5, 12, 6, 10, 7];
n = length(X);

% population variance is no longer known (we use second formula, which uses sample variance)

X_var = sqrt(var(X, 1));

X_mean = mean(X);
alpha = 0.05

T_1 = tinv(1 - alpha / 2, n - 1);
T_2 = tinv(alpha / 2, n - 1);

theta_L = X_mean - X_var / sqrt(n) * T_1
theta_U = X_mean - X_var / sqrt(n) * T_2

