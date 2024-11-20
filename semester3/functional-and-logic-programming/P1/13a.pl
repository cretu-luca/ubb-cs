% Transform a list in a set, in the order of the last occurrences of elements.

transform([], []).
transform([H | T], [H | R]):-
    transform(T, R),
    \+ is_member(H, R).

transform([H | T], R):-
    transform(T, R),
    is_member(H, R).

is_member(X, [X | _]).
is_member(X, [_ | T]):-
    is_member(X, T).
