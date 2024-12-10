clc
clear all;

X=[7,7,4,5,9,9,4,12,8,1,8,7,3,13,2,1,17,7,12,5,6,2,1,13,14,10,2,4,9,11,3,5,12,6,10,7];

% H_0: mu = 8.5
% H_1: mu < 8.5
% left-tailed test

alpha = input("alpha: ");

tt_alpha = norminv(alpha, 0, 1)
[H, P, C_i, Z_val] = ztest(X, 8.5, 5, alpha, -1);
H
P
C_i

% H = 1, we reject H_0
% H = 0, we don't reject H_0

if H == 1
    fprintf("hypothesis rejected")
else
    fprintf("hypothesis not rejected")
end
