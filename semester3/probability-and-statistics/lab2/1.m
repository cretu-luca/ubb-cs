clear all;
clc;
n=input("enter number of trials: ");
p=input("enter probability of success: ");

k=0:n;
px=binopdf(k, n, p);

plot(k, px);

kk = 0:0.01:n;
fx = binocdf(kk, n, p);

plot(k, px, 'x');
hold on;
plot(kk, fx);
hold off;
title("the binomial model");
legend("pdf", "cdf");
