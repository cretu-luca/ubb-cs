% Write a predicate to determine the sum of two numbers written in list representation.

sum_init(L1, L2, R):-
    reverse(L1, R1),
    reverse(L2, R2),
    sum(R1, R2, 0, [], R).

sum([], [], 1, Acc, [1 | Acc]).
sum([], [], 0, Acc, Acc).

sum(A, [], T, Acc, R):-
    sum(A, [T], 0, Acc, R).

sum([], A, T, Acc, R):-
    sum([T], A, 0, Acc, R).

sum([H1 | T1], [H2 | T2], T, Acc, R):-
    S is (H1 + H2 + T) mod 10,
    NewT is (H1 + H2 + T) div 10,
    sum(T1, T2, NewT, [S | Acc], R).
