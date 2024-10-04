isPrime(N, D):- D >= N.
isPrime(N, D):- 
    N mod D =\= 0,
    D1 is D + 1,
    isPrime(N, D1). 

isPrime(N):- N > 1, isPrime(N, 2).

filterPrimes([], []).

filterPrimes([H|T], Rez):-
    isPrime(H, 2),
    filterPrimes(T, Rez).

filterPrimes([H|T], Rez):- 
    isPrime(H, 2),
    filterPrimes(T, Rez).
