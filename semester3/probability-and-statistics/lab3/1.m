clear all;
clc;

alpha = input('alpha:\n');
beta = input('beta:\n');
option = input('Enter dist. model (Normal, Student, Chi2, Fisher):\n', 's');

switch option
    case 'Normal'
        fprintf("Normal Distr. model\n");
        mu = input("mu:\n");
        sigma = input("sigma:\n");
        cdf = normcdf(0, mu, sigma);
        fprintf("cdf = %f, 1 - cdf = %f\n", cdf, 1 - cdf);
        cdf2 = normcdf(1, mu, sigma) - normcdf(-1, mu, sigma);
        fprintf("cdf2 = %f, 1 - cdf2 = %f\n", cdf2, 1 - cdf2);
        quintile = norminv(alpha, mu, sigma);
        fprintf("quintile = %f\n", quintile);
        quintile2 = norminv(1 - beta, mu, sigma);
        fprintf("quintile2 = %f\n", quintile2);
    case 'Student'
        fprintf("Student distr. model\n");
        n = input("n:\n");
        cdf = tcdf(0, n);
        fprintf("cdf = %f, 1 - cdf = %f", cdf, 1 - cdf);
    case 'Chi2'
        fprintf("Chi2 distr. model\n");
        n = input("n:\n");
        cdf = chi2cdf(0, n);
        fprintf("cdf = %f, 1 - cdf = %f", cdf, 1 - cdf);
    case 'Fisher'
        fprintf("Fisher distr. model\n");
        m = input("m:\n");
        n = input("n:\n");
        cdf = fcdf(0, n);
        fprintf("cdf = %f, 1 - cdf = %f", cdf, 1 - cdf);
    otherwise
        fprintf("Invalid input.\n")
end
