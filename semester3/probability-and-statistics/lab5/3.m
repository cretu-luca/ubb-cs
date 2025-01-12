clc;
clear all;

A_len = 30;
B_len = 20; 

A_mean = 6.7;
B_mean = 7.5;

A_std = 0.6;
B_std = 1.2;

confidence = 0.95;
alpha = 1 - confidence;

T_1 = tinv(1 - alpha / 2, A_len + B_len - 2);

theta_diff_L = A_mean - B_mean - T_1 * sqrt(A_std ^ 2 / A_len + B_std ^ 2 / B_len);
theta_diff_U = A_mean - B_mean + T_1 * sqrt(A_std ^ 2 / A_len + B_std ^ 2 / B_len);

F_1 = finv(1 - alpha / 2, A_len - 1, B_len - 1);
F_2 = finv(alpha / 2, A_len - 1, B_len - 1);

theta_ratio_L = sqrt(A_std ^ 2 / (F_1 * B_std ^ 2))
theta_ratio_U = sqrt(A_std ^ 2 / (F_2 * B_std ^ 2))

