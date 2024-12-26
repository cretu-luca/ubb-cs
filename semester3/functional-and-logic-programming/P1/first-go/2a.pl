%  Write a predicate to remove all occurrences of a certain atom from a list
removeElement(_, [], []).
removeElement(X, [H | T], [H | Result]):-
    X =\= H,
    !,
    removeElement(X, T, Result).

removeElement(X, [_ | T], Result):-
    removeElement(X, T, Result).
