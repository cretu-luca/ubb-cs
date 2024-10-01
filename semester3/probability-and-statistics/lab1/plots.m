clc;
clear all;
clf;
x = 0:0.01:3;
y1 = x .^ 5 / 10;
y2 = x .* sin(x);
y3 = cos(x);

% plot(x, y1);
% hold on;
% plot(x, y2);
% plot(x, y3);
% hold off;

% plot(x, y1, "r", x, y2, "--b", x, y3, ":g")

subplot(3, 1, 1);
plot(x, y1, 'r');
xlabel('x');
ylabel('x^5 / 10');
title('Graph of x^5 / 10');
legend('x^5 / 10');

subplot(3, 1, 2);
plot(x, y2, '--b');
xlabel('x');
ylabel('x sin(x)');
title('Graph of x sin(x)');
legend('x sin(x)');

subplot(3, 1, 3);
plot(x, y3, ':g');
xlabel('x');
ylabel('cos(x)');
title('Graph of cos(x)');
legend('cos(x)');
