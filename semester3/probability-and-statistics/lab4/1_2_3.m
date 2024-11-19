clc;
pause(1);

% equivalent:
rand(2,3);
unifrnd(0,1,2,3);


binornd(3, 0.5, 2, 3);


% Bernoulli distribution

%S=input("What is the number of simulations?");
%p=input("What is the probability of success?");

%U=rand(1, S);
%X=U<p;

%uniqueX = unique(X);
%numsX = hist(X, length(uniqueX));
%[uniqueX; numsX/S]


% Binomial distribution

%S=input("What is the number of simulations?");
%n=input("How many trials?");
%p=input("What is the probability of success?");

%U=rand(n, S);
%X=U<p;
%sumX=sum(X);

%uniqueSumX = unique(sumX);
%numsSumX = hist(sumX, length(uniqueSumX));

%xvals=0:n;
%pdf_xvals=binopdf(xvals, n, p);

%plot(xvals, pdf_xvals, "o");
%hold on;
%plot(uniqueSumX, numsSumX/S, "*");
%hold off;

%[uniqueSumX; numsSumX/S]


% Geometric distribution

S=input("What is the number of simulations?");
p=input("What is the probability of success?");

X = zeros(1, S);

for i=1:S
    numberOfFailures = 0;
    %%% inside the i-th simulation
    while rand() >= p
        %%% while we have a failure
        numberOfFailures = numberOfFailures + 1;
    end
    X(i) = numberOfFailures;
end

uniqueX = unique(X);
numsX = hist(X, length(uniqueX));

xvals=0:max(uniqueX);
pdf_xvals=geopdf(xvals, p);

plot(xvals, pdf_xvals, "o");
hold on;
plot(uniqueX, numsX/S, "*");
hold off;

[uniqueX; numsX/S]
