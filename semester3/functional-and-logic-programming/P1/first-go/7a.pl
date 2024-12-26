% Write a predicate to compute the intersection of two sets.

intersection([], _, []).
intersection([H | T], S, [H | R]):-
    isMember(H, S),
    !,
    intersection(T, S, R).
intersection([_ | T], S, R):-
    intersection(T, S, R).

isMember(X, [X | _]).
isMember(X, [_ | T]):-
    isMember(X, T).
