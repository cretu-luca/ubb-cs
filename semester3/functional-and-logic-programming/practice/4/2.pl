% subsets with at least n elements, having sum divisible with 3

subsets([], []).
subsets([H | T], [H | R]):-
    subsets(T, R).
subsets([_ | T], R):-
    subsets(T, R).

check([], N, S):-
    S mod 3 =:= 0, 
    N =< 0, !.
check([H | T], N, S):-
    S1 is S + H,
    N1 is N - 1,  
    check(T, N1, S1).

one_sol(L, N, R):-
    subsets(L, R),
    check(R, N, 0).

all_sol(L, N, Res):-
    findall(R, one_sol(L, N, R), Res).
