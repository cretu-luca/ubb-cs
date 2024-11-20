% Determine the successor of a number represented as digits in a list.

succ_init(L, R2):-
    reverse(L, Lr),
    succ(Lr, 1, R),
    reverse(R, R2).

succ([], 1, [1]).
succ([], 0, []).
succ([H | T], Tr, [H1 | R]):-
    H1 is (H + Tr) mod 10,
    Tr2 is (H + Tr) div 10,
    succ(T, Tr2, R).
