clc;
clear all;

% x = 0:0.03:3
x = linspace(0, 3, 100);
y1 = x .^ 5 / 10;
y2 = x .* sin(x);
y3 = cos(x);

% plot(x, y1, "r-", x, y2, "b--", x, y3, "g:");
% title("Function plots");
% xlabel("x");
% ylabel("x^5 / 10, x sin(x), cos(x)");
% legend('x^5 / 10', "x sin(x)", "cos(x)", "Location", "northwest");

subplot(3, 1, 1);
plot(x, y1, "r-");
title("x^5 / 10");
xlabel("x");
ylabel("x^5 / 10");
legend("x^5 / 10");

hold on;

subplot(3, 1, 2);
plot(x, y2, "b--");
title("x sin(x)");
xlabel("x");
ylabel("x sin(x)");
legend("x sin(x)");

subplot(3, 1, 3);
plot(x, y3, "g:");
title("cos(x)");
xlabel("x");
ylabel("cos(x)");
legend("cos(x)");

hold off;
