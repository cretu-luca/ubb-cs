clc;
clear all;

mu = 0;
sigma = 1;

x = linspace(-4, 4, 1000);

normal_cdf_le_0 = normcdf(x, mu, sigma);
normal_cdf_ge_0 = 1 - normcdf(x, mu, sigma);

% plot(x, normal_cdf_le_0, "-r");
% hold on;
% plot(x, normal_cdf_ge_0, "-b");

normal_cdf_1 = normcdf(1, mu, sigma) - normcdf(-1, mu, sigma);
normal_cdf_1_c = 1 - normcdf(1, mu, sigma) - normcdf(-1, mu, sigma);

alpha = 0.75;
quintile_le = norminv(alpha, mu, sigma);
quintile_ge = norminv(1 - alpha, mu, sigma);
