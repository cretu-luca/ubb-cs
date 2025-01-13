clc;
clear all;

sizes = [3.26, 1.89, 2.42, 2.03, 3.07, 2.95, 1.39, 3.06, 2.46, 3.35, 1.56, 1.79, 1.76, 3.82, 2.42, 2.96];
 
% a) 95% confidence interval for the average size of a nickel particle
alpha = 0.05; 

s_mean = mean(sizes);
s_len = length(sizes);
s_var = var(sizes); 

t_1 = tinv(1 - alpha / 2, s_len - 1);
t_2 = tinv(alpha / 2, s_len - 1);

theta_l = s_mean - sqrt(s_var) / sqrt(s_len) * t_1; 
theta_u = s_mean - sqrt(s_var) / sqrt(s_len) * t_2;

fprintf("Confidence interval: (%3.4f, %3.4f)\n\n", theta_l, theta_u);

[h, p, ci] = ttest(sizes);
ci(1); 
ci(2);

% b) 
% H0: size = 3
% H1: size < 3 (left-tailed test)

sign = 0.01;

tt = (s_mean - 3) / (sqrt(s_var) / sqrt(s_len));

t_l = tinv(sign, s_len - 1);

tt;
t_l;

h = tt < t_l;
if h == 1 
    fprintf("H0 rejected - size < 3\n");
else 
    fprintf("H0 not rejected - size = 3\n");
end

[h, p, ci, stats] = ttest(sizes, 3, 'Alpha', sign, 'Tail', 'left');
if h == 1 
    fprintf("H0 rejected - size < 3\n");
else 
    fprintf("H0 not rejected - size = 3\n");
end
