clc
clear all;

X = [20, 20, 21, 22, 22, 22, 23 * ones(1, 6), 24 * ones(1, 5), 25 * ones(1, 9), 26, 26, 27, 27];
Y = [75, 75, 75, 76, 76, 77, 77, 78 * ones(1, 5), 79 * ones(1, 8), 80 * ones(1, 8), 81, 82];

length(X)
length(Y)

X_bar = mean(X)
Y_bar = mean(Y)

X_var = var(X, 1)
Y_var = var(Y, 1)

X_std = sqrt(X_var)
Y_std = sqrt(Y_var)
