/* Write a predicate to create the sublist (lm, …, ln) from the list (l1,…, lk). */

sublist_init(L, M, N, O):-
    sublist(L, M, N, O, 1).
    
sublist([_ | T], M, N, O, C):-
    C < M,
    C1 is C + 1,
    sublist(T, M, N, O, C1).

sublist([H | T], M, N, [H | O], C):-
    C >= M,
    C =< N,
    C1 is C + 1,
    sublist(T, M, N, O, C1).

sublist(_, _, N, [], C):-
    C > N.
