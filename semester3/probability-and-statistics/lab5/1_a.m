clc
clear all;

X=[7,7,4,5,9,9,4,12,8,1,8,7,3,13,2,1,17,7,12,5,6,2,1,13,14,10,2,4,9,11,3,5,12,6,10,7];

sigma = 5

X_len = length(X);
X_bar = mean(X);

confidence = input("confidence: ");
alpha = 1 - confidence;

Z_1 = norminv(1 - alpha / 2, 0, 1);
Z_2 = norminv(alpha / 2, 0, 1);

thetaL = X_bar - sigma / sqrt(X_len) * Z_1
thetaU = X_bar - sigma / sqrt(X_len) * Z_2
