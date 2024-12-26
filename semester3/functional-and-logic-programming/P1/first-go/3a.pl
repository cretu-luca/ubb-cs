% Define a predicate to remove from a list all repetitive elements.
removeRepetitive([], []).
removeRepetitive([H | T], [H | R]):-
    getFrequency(H, [H | T], C),
    C =:= 1,
    !,
    removeRepetitive(T, R).

removeRepetitive([H | T], R):-
    remove(H, T, NewT),
    removeRepetitive(NewT, R).

remove(_, [], []).
remove(X, [H | T], [H | R]):-
    X =\= H,
    !,
    remove(X, T, R).

remove(X, [_ | T], R):-
    remove(X, T, R).

getFrequency(_, [], 0).
getFrequency(X, [H | T], Value):-
    X =:= H, 
    !,
    getFrequency(X, T, Value2),
    Value is Value2 + 1.

getFrequency(X, [_ | T], Value):-
    getFrequency(X, T, Value2),
    Value is Value2.
