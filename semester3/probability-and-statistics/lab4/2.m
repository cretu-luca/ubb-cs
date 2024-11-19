clear all
clc

pause(1)
S = input("no. simulations: "); 
n = input("no. trials: ");
p = input("prob. of success: ");

U = rand(n, S);
X = U < p
sum_X = sum(X)

U_sum_X = unique(sum_X)
n_X =  hist(sum_X, length(U_sum_X));

x = 0:n;
pdf = binopdf(x, n, p);

plot(x, pdf, "-");
hold on;
plot(n_X, n_X / S, "*")
hold off;

[U_sum_X; n_X / S]
