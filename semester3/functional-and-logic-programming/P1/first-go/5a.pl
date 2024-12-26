% Write a predicate to compute the union of two sets
union([], _, []).

union([H | Tail], T, R):-
    \+ isMember(H, T),
    !,
    union(Tail, T, R).

union([H | Tail], T, [H | R]):-
    union(Tail, T,  R).

isMember(X, [X | _]):- !.
isMember(X, [_ | T]):-
    isMember(X, T).
