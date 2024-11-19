clear all
clc

pause(1)
S = input("no. simulations: "); 
p = input("prob. of success: ");

U = rand(1, S);
X = U < p

U_X = unique(X);

n_X = hist(X, length(U_X));
rel_freq = n_X / S;

[U_X; rel_freq]
