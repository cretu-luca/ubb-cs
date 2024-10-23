nOc([], _, 0).
nOc([E|T], E, R):-!,
    nOc(T, E, R1),
    R is R1 + 1.
nOc([_|T], E, R):-
    nOc(T, E, R).

rmAppear1([], _, []).
rmAppear1([H|T], C, R):-
    nOc(C, H, N),
    N > 1, !,
    rmAppear1(T, C, R1),
    R = [H|R1].
rmAppear1([_|T], C, R):-
    rmAppear1(T, C, R).

mainrm(L, R):- rmAppear1(L, L, R).