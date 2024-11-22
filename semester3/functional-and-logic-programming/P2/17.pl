/* sum of number in list representation with digit */

sum_main(L, D, Rf):-
    reverse(L, Lr),
    sum(Lr, D, 0, R),
    reverse(R, Rf).

sum([], _, 0, []).
sum([], _, 1, [1]).

sum([H | T], D, Tr, [H2 | R]):-
    H2 is (H + D + Tr) mod 10,
    Tr2 is (H + D + Tr) div 10,
    sum(T, 0, Tr2, R).
