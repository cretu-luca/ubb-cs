clc;
clear all;

steel = [4.5, 0.7, 4.2, 1.9, 4.8, 6.1, 4.7, 5.5, 5.4];
glass = [2.5, 1.3, 2.0, 1.8, 2.7, 3.2, 3.0, 3.5, 3.4];

alpha = 0.05;

steel_sample_var = var(steel);
glass_sample_var = var(glass);

n1 = length(steel);
n2 = length(glass);

% H0: same variance 
% H1: different population variances

tt = steel_sample_var / glass_sample_var;

f_1 = finv(alpha / 2, n1 - 1, n2 - 1);
f_2 = finv(1 - alpha / 2, n1 - 1, n2 - 1);

f_1;
tt;
f_2;

fprintf('Rejection interval: (-inf, %3.4f) U (%3.4f, inf)\n', f_1, f_2);
fprintf('tt value is %3.4f\n\n', tt);

if tt < f_1 || tt > f_2
    fprintf('H0 is rejected - H1: different population variances\n')
else
    fprintf('H0 is not rejected: same variances\n')
end

[h, p, ci, stats] = vartest2(steel, glass, alpha);
h; 
p; 
ci; 
stats;

if h == 1
    fprintf('(vartest2) H0 is rejected - H1: different population variances\n\n')
else
    fprintf('(vartest2) H0 is not rejected: same variances\n\n')
end

% h = 1 -> we refute the null hypothesis, the variances are different 

% looking at the population average
% H0: steel_mean = glass_mean
% H1: steel_mean > glass_mean (right tailed test)
% previous result shows the population variances are different

steel_mean = mean(steel);
glass_mean = mean(glass);

% µ1−µ2 = 0, according to the null hypothesis
tt = (steel_mean - glass_mean) / (sqrt(steel_sample_var / n1 + glass_sample_var / n2));

c = (steel_sample_var / n1) / (steel_sample_var / n1 + glass_sample_var / n2);
n = 1 / (c ^ 2 / (n1 - 1) + (1 - c) ^ 2 / (n2 -  1));

t = tinv(1 - alpha, n);

t;  
tt;

fprintf('Rejection interval: (%3.4f, inf) (right-tailed test)\n', t);
fprintf('tt value is %3.4f\n\n', tt);

if abs(tt) > t 
    fprintf('H0 is rejected - H1: steel_mean > glass_mean\n')
else
    fprintf('H0 is not rejected: steel_mean = glass_mean\n')
end

[h, p, ci, stats] = ttest2(steel, glass, alpha, 1, 'unequal');
h;
p;
ci;
stats;

if h == 1
    fprintf('(ttest2) H0 is rejected - H1: steel_mean > glass_mean\n')
else
    fprintf('(ttest2) H0 is not rejected: steel_mean = glass_mean\n')
end
