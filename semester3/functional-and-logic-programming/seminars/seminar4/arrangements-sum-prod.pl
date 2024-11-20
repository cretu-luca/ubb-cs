% arrangements for given sum and product of elements

insertEl(E, L, [E | L]).
insertEl(E, [H | T], [H | R]):-
    insertEl(E, T, R).

arr([H | _], 1, [H]).
arr([_ | T], K, R):-
    K >= 1,
    arr(T, K, R).
arr([H | T], K, R):-
    K > 1,
    K1 is K - 1,
    arr(T, K1, A),
    insertEl(H, A, R).

sum([], 0).
sum([H | T], S):-
    sum(T, TS),
    S is H + TS.

prod([], 1).
prod([H | T], P):-
    prod(T, TP),
    P is H * TP.

% one_sol(L, K, S, P) = a1a2...ak, a1a2...ak = arr(L, K) and 
% 								   sum(a1a2...ak) = S and
% 								   prod(a1a2...ak) = P

% main(L, K, S, P) = findall(one_sol(L, K, S, P))
% one_sol(L - List, K - Number, S - Number, P - Number, A - List) (i, i, i, i, o)

one_sol(L, K, S, P, A):-
    arr(L, K, A),
    sum(A, S),
    prod(A, P).

main(L, K, S, P, R):-
    findall(A, one_sol(L, K, S, P, A), R).
