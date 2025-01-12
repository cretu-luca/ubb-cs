% Generate the list of all arrangements of K elements of a given list.
% Eg: [2, 3, 4] K=2 => [[2,3], [3,2], [2,4], [4,2], [3,4], [4,3]] (not necessary in this order)

insert(E, L, [E | L]).
insert(E, [H | T], [H | R]):-
    insert(E, T, R).

arr([E | _], 1, [E]).
arr([_ | T], K, R):-
    arr(T, K, R).
arr([H | T], K, R2):-
    K > 1,
    K2 is K - 1,
    arr(T, K2, R),
    insert(H, R, R2).

all_sols(L, K, Result):-
    findall(R, arr(L, K, R), Result).
