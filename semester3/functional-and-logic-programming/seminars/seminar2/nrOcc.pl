nOc([], _, 0).
nOc([E | T],  E, R):-!,
    nOc(T, E, R1),
    R is R1 + 1.

nOc([H | T], E, R):-
    H =\= E,
    nOc(T, E, R).