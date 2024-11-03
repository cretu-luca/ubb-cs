% Write a predicate to determine the difference of two sets

setDiff(S, T, R):-
    diff(S, T, R).

diff([], _, []).

diff([H | Tail], T, R):-
    isMember(H, T),
    !,
    diff(Tail, T, R).

diff([H | Tail], T, [H | R]):-
    \+	isMember(H, T),
    diff(Tail, T,  R).

isMember(X, [X | _]):- !.
isMember(X, [_ | T]):-
    isMember(X, T).
