clear all;
clc;

n=3;
p=0.5;
S=input("number of simulations: ");

U=rand(n, S);
U=(U < 0.5)

X=sum(U);

histogram(X);
