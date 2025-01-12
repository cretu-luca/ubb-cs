subsets([], []).
subsets([_ | T], R):-
    subsets(T, R).
subsets([H | T], [H | R]):-
    subsets(T, R).

