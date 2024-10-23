nOc([], _, 0).
nOc([E|T], E, R):-!,
    nOc(T, E, R1),
    R is R1 + 1.
nOc([_|T], E, R):-
    nOc(T, E, R).

remEc([], _, C, C).
remEc([H | T], CP, C, R):-
    nOc(CP, H, 1),
    remEc(T, CP, C, R).

remEc([H | T], CP, C, R):-
    nOc(CP, H, N),
    N > 1,
    remEc(


mainrm(L, R):- rmAppear1(L, L, R).