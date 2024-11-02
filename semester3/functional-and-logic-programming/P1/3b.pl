% Remove all occurrence of a maximum value from a list on integer numbers
removeMax([H | T], R):-
    findMaximum(H, T, Max),
    remove(Max, [H | T], R).

remove(_, [], []).
remove(X, [H | T], [H | R]):-
    X =\= H,
    !,
    remove(X, T, R).

remove(X, [_ | T], R):-
    remove(X, T, R).

findMaximum(Max, [], Max).
findMaximum(X, [H | T], Max):-
    X > H,
    !,
    findMaximum(X, T, Max).

findMaximum(_, [H | T], Max):-
    findMaximum(H, T, Max).
