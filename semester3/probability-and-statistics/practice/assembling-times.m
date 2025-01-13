clc;
clear all;

standard = [46, 37, 39, 48, 47, 44, 35, 31, 44, 37];
new = [35, 33, 31, 35, 34, 30, 27, 32, 31, 31];

s_var = var(standard);
n_var = var(new);

s_len = length(standard);
n_len = length(new);

alpha = 0.05;

% a) at 5% significance level, do the population variances seem to differ?
% H0: same populations variances
% H1: different population variances (two-tailed test)

tt = s_var / n_var; 

tt_l = finv(alpha / 2, s_len - 1, n_len - 1);
tt_u = finv(1 - alpha / 2, s_len - 1, n_len - 1);

fprintf('Rejection region: (-inf, %3.4f) U (%3.4f, inf)\n', tt_l, tt_u);
fprintf('Statistic: %3.4f\n\n', tt);

if tt < tt_l || tt > tt_u 
    fprintf('H0 rejected - variances are different.\n')
else
    fprintf('H0 not rejected - variances are equal.\n')
end

[h, s, ci, stats] = vartest2(standard, new);
h; 
s; 
ci; 
stats; 

% conclusion: different population variances

% b) 95% confidence interval for the difference of the average assembling
% times

n1 = length(standard);
n2 = length(new);

s_mean = mean(standard);
n_mean = mean(new);

c = (s_var / n1) / (s_var / n1 + n_var / n2);
n = 1 / (c ^ 2 / (n1 - 1) + (1 - c) ^ 2 / (n2 - 1));

t = tinv(1 - alpha / 2, n);

theta_diff_l = s_mean - n_mean - t * sqrt(s_var / n1 + n_var / n2);
theta_diff_u = s_mean - n_mean + t * sqrt(s_var / n1 + n_var / n2);

fprintf('Difference confidence interval: (%3.4f, %3.4f)\n', theta_diff_l, theta_diff_u);

[h, p, ci, stats] = ttest2(standard, new, 'Alpha', 0.05, 'Vartype', 'unequal');
fprintf('Built-in function CI: (%3.4f, %3.4f)\n', ci(1), ci(2));
