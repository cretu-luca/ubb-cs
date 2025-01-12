% Write a program to generate the list of all subsets of sum S with the elements of a list (S - given).
% Eg: [1,2,3,4,5,6,10] si S=10 => [[1,2,3,4], [1,4,5], [2,3,5], [4,6], [10]] (not necessary in this order)

subseq([], []).
subseq([_ | T], R):-
    subseq(T, R).
subseq([H | T], [H | R]):-
    subseq(T, R).

sum([], 0).
sum([H | T], S2):-
    sum(T, S),
    S2 is S + H.

one_sol(L, S, R):-
    subseq(L, R),
    sum(R, S2),
    S2 =:= S.

all_sols(L, S, Result):-
    findall(R, one_sol(L, S, R), Result).
