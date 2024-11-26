clc
clear all;

X=[7,7,4,5,9,9,4,12,8,1,8,7,3,13,2,1,17,7,12,5,6,2,1,13,14,10,2,4,9,11,3,5,12,6,10,7];

X_len = length(X);
X_bar = mean(X);

s = var(X);

confidence = input("confidence: ");
alpha = 1 - confidence;

thetaL = (X_len - 1) * s / chi2inv(1 - alpha / 2, X_len - 1);
thetaU = (X_len - 1) * s / chi2inv(alpha / 2, X_len - 1);

thetaL, thetaU
