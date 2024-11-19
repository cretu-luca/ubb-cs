clear all
clc

p = 1;
while p > 0.05
    p = input("prob. of succes (p <= 0.05) = ");
end

for n=30:35
    k = 0:n;
    poisson = poisspdf(k, n * p);
    plot(k, poisson, "o");
    hold on;

    px = binopdf(k, n, p);
    plot(k, px, "+");
    hold off;
    pause(0.5)
end
