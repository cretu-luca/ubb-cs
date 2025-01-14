clc; 
clear all;

A = [21.8, 22.6, 21.0, 19.7, 21.9, 21.6, 22.5, 23.1, 22.2, 20.1, 21.4, 20.5];
B = [36.5, 35.2, 36.2, 34.0, 36.4, 36.1, 37.5, 38.0, 36.3, 35.9, 35.7, 34.9];

A_var = var(A);
B_var = var(B);

A_len = length(A);
B_len = length(B);

A_mean = mean(A);
B_mean = mean(B);

% a) at 5% significance level, do the variances seem to differ?
% H0: population variances seem to be the same (the null hypothesis)
% H1: population variances seem to differ (the alternative hypothesis)
% two-tailed test

% significance level
alpha = 0.05;

% will compute the statistic tt using the formula for the 
% ratio of two population variances, considering that the population 
% variances are the same, so they simplify in the ratio

tt = A_var / B_var;

% this is a two-tailed test, so we need to compute two critical points 
% for the rejection region

tt_l = finv(alpha / 2, A_len - 1, B_len);
tt_u = finv(1 - alpha / 2, A_len - 1, B_len);

% afterwards, we check if tt is inside or outside the rejection region 
h = tt < tt_l || tt > tt_u;

fprintf("The test statistic (tt): %3.4f.\n", tt);
fprintf("Rejection region: (-inf, %3.4f) U (%3.4f, +inf)\n\n", tt_l, tt_u);

if h == 1 
    fprintf('H0 rejected - variances seem to diff.\n');
else 
    fprintf('H0 not rejected - variances seem to be the same.\n');
end

[h, s, ci, stats] = vartest2(A, B);
h;
s;
ci;
stats;

fprintf("The observed value of the statistical test: %3.4f\n", stats.fstat);

% h = 0, therefore, we do not have enough information to reject the 
% null hypothesis; that means, the population variances seem to be the same

% b) find a 95% confidence level for the difference of the average printing
% times; therefore, the significance level is 5%

% the populations variances seem to be the same (as observed at a))
% since we're interested in a confidence interval for the difference of the
% average printing times, we will use the second formula from point 3, 
% confidence intervals file

s_p = sqrt(((A_len - 1) * A_var + (B_len - 1) * B_var) / (A_len + B_len - 2));

% student distribution is symetric, no need to compute both critical points
t_1 = tinv(1 - alpha / 2, A_len + B_len - 2);

theta_diff_l = A_mean - B_mean - t_1 * s_p * sqrt(1 / A_len + 1 / B_len);
theta_diff_u = A_mean - B_mean + t_1 * s_p * sqrt(1 / A_len + 1 / B_len);

fprintf('Difference confidence interval: (%3.4f, %3.4f)\n', theta_diff_l, theta_diff_u);

[h, p, ci, stats] = ttest2(A, B, 'Alpha', 0.05, 'Vartype', 'equal');
h
p % the p value
ci
stats
fprintf('Built-in function CI: (%3.4f, %3.4f)\n', ci(1), ci(2));

