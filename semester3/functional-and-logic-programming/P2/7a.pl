% Determine the position of the maximal element of a linear list.

find_max([Max], Max).
find_max([H | T], H):-
    find_max(T, Max),
    H > Max.
find_max([H | T], Max):-
    find_max(T, Max),
    H =< Max.

find_max_pos([], _, _, R, R).
find_max_pos([Max | T], Max, C, Curr, R):-
    !,
    C1 is C + 1,
    find_max_pos(T, Max, C1, [C | Curr], R).
find_max_pos([_ | T], Max, C, Curr, R):-
    C1 is C + 1,
    find_max_pos(T, Max, C1, Curr, R).
