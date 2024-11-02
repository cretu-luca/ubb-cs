% Define a predicate to produce a list of pairs (atom n) from an initial list of atoms. In this initial list atom has
% n occurrences.

setify([], []).
setify([H | T], [H | R]):-
    isMember(H, T),
    !,
    setify(T, R).

setify([_ | T], R):-
    setify(T, R).

isMember(_, []).
isMember(X, [H | T]):-
    X =\= H,
    isMember(X, T).

addFrequencyWrapper(L, R):-
    setify(L, L2),
	addFrequency(L2, R).e

addFrequency([], _).
addFrequency([H | T], [[H | Value] | Result]):-
    getFrequency(H, T, Value),
    addFrequency(T, Result).

getFrequency(_, [], 0).
getFrequency(X, [H | T], Value):-
    X =:= H, 
    !,
    getFrequency(X, T, Value2),
    Value is Value2 + 1.

getFrequency(X, [_ | T], Value):-
    getFrequency(X, T, Value2),
    Value is Value2.
