% Define a predicate to determine the predecessor of a number represented as digits in a list.

pred_init(L, R2):-
    reverse(L, Lr),
    pred(Lr, -1, R),
    reverse(R, R2).

pred([H], -1, []):-
    H2 is H - 1,
    H2 is 0.
pred([H], -1, [H2]):-
    H2 is H - 1.
pred([], 0, []).
pred([H | T], Tr, [H1 | R]):-
    H1 is (H + Tr) mod 10,
    Tr2 is (H + Tr) div 10,
    pred(T, Tr2, R).
