% 4.
% a. Write a predicate to determine the difference of two sets.
% b. Write a predicate to add value 1 after every even element from a list.

% a)
diff([], _, []).
diff([H | T], P, [H | R]):-
    \+ is_member(P, H),
    !,
    diff(T, P, R).
diff([_ | T], P, R):-
    diff(T, P, R).
    
is_member([E | _], E).
is_member([_ | T], E):-
    is_member(T, E).

% b)
add_one([], []).
add_one([H | T], [H, 1 | R]):-
    H mod 2 =:= 0,
    !,
    add_one(T, R).
add_one([H | T], [H | R]):-
    add_one(T, R).
