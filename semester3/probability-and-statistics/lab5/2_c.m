clc;
clear all;

P = [22.4, 24.5, 21.6, 22.4, 24.8, 21.7, 23.4, 23.3, 21.6, 20.0];
R = [17.7, 19.6, 12.1, 15.4, 14.0, 14.8, 19.6, 14.8, 12.6, 12.2];

P_len = length(P);
R_len = length(R);

P_var = var(P, 1);
R_var = var(R, 1);

alpha = 0.05;

F_1 = finv(1 - alpha / 2, P_len - 1, R_len - 1);
F_2 = finv(alpha / 2, P_len - 1, R_len - 1);

theta_ratio_L = P_var / (F_1 * R_var)
theta_ratio_U = P_var / (F_2 * R_var)
