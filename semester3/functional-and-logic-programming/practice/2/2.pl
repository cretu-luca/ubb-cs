chair(r).
chair(y).

row(N, []) :- N >= 5.
row(N, [C | R]):-
    N < 5,
    chair(C),
    N1 is N + 1,
    row(N1, R).

count_yellow([], 0).
count_yellow([y | T], C):-
    count_yellow(T, C1),
    C is C1 + 1.
count_yellow([r | T], C):-
    count_yellow(T, C).

one_sol(R):-
    row(0, R),
    count_yellow(R, C),
    C =< 3.

all_sol(Res):-
    findall(R, one_sol(R), Res).
