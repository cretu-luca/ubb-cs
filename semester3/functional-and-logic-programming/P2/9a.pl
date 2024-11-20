% For a list of integer number, write a predicate to add in list after 1-st, 3-rd, 7-th, 15-th element a given value e.

insert_e(L, E, R):-
    insert_aux(L, E, 1, 1, R).

insert_aux([], _, _, _, []).

insert_aux([H | T], E, Curr, Curr, [H, E | R]):-
    !,
    Tar is Curr * 2 + 1,
    Curr2 is Curr + 1,
    insert_aux(T, E, Curr2, Tar, R).

insert_aux([H | T], E, Curr, Tar, [H | R]):-
    Curr2 is Curr + 1,
    insert_aux(T, E, Curr2, Tar, R).
