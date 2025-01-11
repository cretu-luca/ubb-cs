clc;
clear all;

X=[7, 7, 4, 5, 9, 9, 4, 12, 8, 1, 8, 7, 3, 13, 2, 1, 17, 7, 12, 5, 6, 2, 1, 13, 14, 10, 2, 4, 9, 11, 3, 5, 12, 6, 10, 7];
n = length(X);

sigma = 5; % population variance is known

X_mean = mean(X); 
alpha = 0.05;
confidence = 1 - alpha;

Z_1 = norminv(1 - alpha / 2, 0, 1);
Z_2 = norminv(alpha / 2, 0, 1);

theta_L = X_mean - sigma / sqrt(n) * Z_1
theta_U = X_mean - sigma / sqrt(n) * Z_2
