% Given a seq a1a2..an conposed of distinct integer numbers,
% display all subsequences with a valley aspect

subset([], []).
subset([H|T], [H|R]):-
    subset(T, R).
subset([_|T], R):-
    subset(T, R).

insertEl(E, L, [E|L]).
insertEl(E, [H|T], [H|R]):-
    insertEl(E, T, R).

perm([], []).
perm([H|T], R):-
    perm(T, P),
    insertEl(H, P, R).

valleyAux([_], 1).
valleyAux([H1,H2|T], F):-
    F =:= 0,
    H1 > H2, !,
    valleyAux([H2|T], 0).
valleyAux([H1,H2|T], _):-
    H1 < H2, !,
    valleyAux([H2|T], 1).

valley([H1,H2|T]):-
    H1 > H2,
    valleyAux([H2|T], 0).


oneSol(L, P):-
    subset(L, S),
    perm(S, P),
    valley(P).
allSol(L, R):-
    findall(P, oneSol(L, P), R).
