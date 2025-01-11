clc;
clear all;

P = [22.4, 24.5, 21.6, 22.4, 24.8, 21.7, 23.4, 23.3, 21.6, 20.0];
R = [17.7, 19.6, 12.1, 15.4, 14.0, 14.8, 19.6, 14.8, 12.6, 12.2];

P_len = length(P);
R_len = length(R);

P_var = var(P, 1);
R_var = var(R, 1);

P_mean = mean(P);
R_mean = mean(R);

alpha = 0.05;

T_1 = tinv(1 - alpha / 2, P_len + R_len - 2);
T_2 = tinv(alpha / 2, P_len + R_len - 2);

s_p_squared = ((P_len - 1) * P_var + (R_len - 1) * R_var) / (P_len + R_len - 2);

theta_diff_L = P_mean - R_mean - T_1 * s_p_squared * sqrt(1 / P_len + 1 / R_len)
theta_diff_U = P_mean - R_mean + T_1 * s_p_squared * sqrt(1 / P_len + 1 / R_len)


