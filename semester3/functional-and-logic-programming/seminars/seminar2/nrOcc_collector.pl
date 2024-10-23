nOcc([], _, C, C).
nOcc([E | T], E, C, R):-
    NC is C + 1,
    nOcc(T, E, NC, R).

nOcc([H | T], E, C, R):-
    H =\= E, 
    nOcc(T, E, C, R).