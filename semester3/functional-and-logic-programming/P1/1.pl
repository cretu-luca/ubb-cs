% 1.
% a) Write a predicate to determine the lowest common multiple of a list formed from integer numbers. 
lcm_aux([H1, H2], R):-
    lcm(H1, H2, R).
lcm_aux([H | T], Rf):-
    lcm_aux(T, R),
    lcm(H, R, Rf).

lcm(M, N, R):-
    MN is M * N,
    gcd(M, N, G),
    R is div(MN, G).

gcd(M, M, M).
gcd(M, N, R):-
    M > N,
    MM is M - N,
    gcd(MM, N, R).
gcd(M, N, R):-
    M < N,
    NN is N - M,
    gcd(M, NN, R).

% b) Write a predicate to add a value v after 1-st, 2-nd, 4-th, 8-th, … element in a list.
insert_aux(L, V, R):-
    my_insert(L, V, 1, 1, [], R).

my_insert([], _, _, _, Acc, Acc).

my_insert([H | R], V, Expected, Expected, Acc, Res):-
	!,
    NewExpected is Expected * 2,
    NewCurrent is Expected + 1,
    append(Acc, [H], NewAcc),
    append(NewAcc, [V], NewNewAcc), 
    my_insert(R, V, NewCurrent, NewExpected, NewNewAcc, Res).

my_insert([H | R], V, Current, Expected, Acc, Res):-
	NewCurrent is Current + 1,
	append(Acc, [H], NewAcc),
	my_insert(R, V, NewCurrent, Expected, NewAcc, Res).
