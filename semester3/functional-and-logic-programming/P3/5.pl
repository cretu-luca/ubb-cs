% Two integers, n and m are given. Write a predicate to determine all possible sequences of numbers
% from 1 to n, such that between any two numbers from consecutive positions, the absolute difference
% to be >= m.

insert(E, L, [E | L]).
insert(E, [H | T], [H | R]):-
    insert(E, T, R). 

perm([], []).
perm([H | T], R2):-
    perm(T, R),
    insert(H, R, R2).

one_sol_perm(N, M, R):-
    numlist(1, N, L),
    perm(L, R),
    check_diff(R, M).

all_perm(N, M, Result):-
    findall(R, one_sol_perm(N, M, R), Result).

seq(C, N, []):-
    C =:= N, !.
seq(C, N, R):-
    C1 is C + 1,
    C1 =< N,
    seq(C1, N, R).
seq(C, N, [C1 | R]):-
    C1 is C + 1,
    C1 =< N,
    seq(C1, N, R).

one_sol_seq(N, M, R):-
    seq(0, N, R), 
    check_diff(R, M).

check_diff([], _).
check_diff([_], _).
check_diff([H, H2 | T], M):-
    D is abs(H2 - H),
    D >= M, 
    check_diff([H2 | T], M).

all_seq(N, M, Result):-
    findall(R, one_sol_seq(N, M, R), Result).
