% 3.
% a. Define a predicate to remove from a list all repetitive elements.
% Eg.: l=[1,2,1,4,1,3,4] => l=[2,3])

remove_repetitive_aux(L, R):-
    remove_repetitive(L, L, R).

remove_repetitive([], _, []).
remove_repetitive([H | T], L, R):-
    no_occ(L, H, A),
    A > 1,
    !,
    remove_repetitive(T, L, R).
remove_repetitive([H | T], L, [H | R]):-
    remove_repetitive(T, L, R).

no_occ([], _, 0).
no_occ([E | T], E, C1):-
    !,
    no_occ(T, E, C),
    C1 is C + 1.
no_occ([_ | T], E, C):-
    no_occ(T, E, C).

% b. Remove all occurrence of a maximum value from a list on integer numbers.
remove_max_aux(L, R):-
    find_max(L, M),
    remove_max(L, M, R).

remove_max([], _, []).
remove_max([M | T], M, R):-
    remove_max(T, M, R), 
    !.
remove_max([H | T], M, [H | R]):-
    remove_max(T, M, R).

find_max([L], L).
find_max([H | T], H):-
    find_max(T, M),
    H > M,
    !.
find_max([_ | T], M):-
    find_max(T, M).
