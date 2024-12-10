clc
clear all;

pr = [22.4, 24.5, 21.6, 22.4, 24.8, 21.7, 23.4, 23.3, 21.6, 20.0];
reg = [17.7, 19.6, 12.1, 15.4, 14.0, 14.8, 19.6, 14.8, 12.6, 12.2];

N1 = length(pr);
N2 = length(reg); 

% H_0: teta  = 1
% H_1: teta != 1
% right-tailed test

alpha = input("alpha: ");

tt_1 = finv(alpha / 2, N1 - 1, N2 - 1)
tt_2 = finv(1 - alpha / 2, N1 - 1, N2 - 1)

% H = 1, we reject H_0
% H = 0, we don't reject H_0

[H, P, Ci Stats] = vartest2(pr, reg, alpha, 0)

if H == 1
    fprintf("hypothesis rejected")
else
    fprintf("hypothesis not rejected")
end
