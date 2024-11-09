% Write a predicate to create a list (m, ..., n) of all integer numbers from the interval [m, n].

interval(N, N, [N]).
interval(M, N, [M | R]):-
    M1 is M + 1,
    interval(M1, N, R).
