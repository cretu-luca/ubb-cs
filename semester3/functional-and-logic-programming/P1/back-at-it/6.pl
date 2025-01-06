% a. Write a predicate to test if a list is a set.
% b. Write a predicate to remove the first three occurrences of an element in a list. If the element occurs less
% than three times, all occurrences will be removed.

is_set([]).
is_set([H | T]):-
    \+ is_member(T, H),
    is_set(T). 
    
is_member([E | _], E).
is_member([_ | T], E):-
    is_member(T, E).

remove_three_aux(L, E, R):-
    remove_three(L, E, 3, R).

remove_three([], _, _, []).
remove_three(L, _, 0, L).
remove_three([E | T], E, C, R):-
    C > 0,
    C2 is C - 1,
    remove_three(T, E, C2, R).
remove_three([H | T], E, C, [H | R]):-
    remove_three(T, E, C, R).
