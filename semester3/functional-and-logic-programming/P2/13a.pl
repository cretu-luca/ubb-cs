/* Given a linear numerical list write a predicate to remove all sequences of consecutive values */

remove_cons([H1], [H1]).
remove_cons([H1, H2], []):-
	H1 + 1 =:= H2,
	!.
remove_cons([H1, H2], [H1, H2]).

remove_cons([H1, H2, H3 | T], R):-
    H1 + 1 =:= H2,
    H2 + 1 =:= H3,
    !,
    remove_cons([H2, H3 | T], R).

remove_cons([H1, H2, H3 | T], R):-
    H1 + 1 =:= H2,
    \+ H2 + 1 =:= H3,
    !,
    remove_cons([H3 | T], R).

remove_cons([H1, H2, H3 | T], [H1 | R]) :-
    H1 + 1 =\= H2,
    remove_cons([H2, H3 | T], R).
