% For a heterogeneous list, formed from integer numbers and list of numbers, write a predicate to replace
% every sublist with the position of the maximum element from that sublist.

replace([], []).
replace([H | T], [Rez2 | R]):-
    is_list(H),
    !,
    find_max(H, Max),
    find_max_pos(H, Max, 1, [], Rez),
    reverse(Rez, Rez2),
    replace(T, R).
replace([H | T], [H | R]):-
    replace(T, R).

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

% [1, [2], [1, 3], 3, 6, [2], 5, [1, 2, 3], 7]
