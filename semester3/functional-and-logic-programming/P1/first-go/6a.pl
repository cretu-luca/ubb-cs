% Write a predicate to test if a list is a set

isSet([]).
isSet([H | T]):-
    \+ isMember(H, T),
    isSet(T).

isMember(X, [X | _]):- !.
isMember(X, [_ | T]):-
    isMember(X, T).
