clc;
clear all;

p = 0.5;
n_values = [10 30 100];
x = 0:1:max(n_values);

hold on;

for n = n_values
    binom_prob = binopdf(0:n, n, p);
    
    mu = n * p;
    sigma = sqrt(n * p * (1 - p));
    
    plot(0:n, binom_prob, 'o');
    
    x_normal = linspace(0, n, 1000);
    y_normal = normpdf(x_normal, mu, sigma);
    plot(x_normal, y_normal, '-');
end
