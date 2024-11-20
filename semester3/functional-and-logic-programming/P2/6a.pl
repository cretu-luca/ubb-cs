% Determine the product of a number represented as digits in a list to a given digit.

mult_init(L, X, R):-
	reverse(L, Lr),
  mult(Lr, X, 0, [], R).

mult([], _, 0, Acc, Acc).
mult([], _, T, Acc, [T | Acc]):- 
    T > 0.

mult([H | T], X, Tr, Acc, R):-
    H2 is (H * X + Tr) mod 10,
    Tr2 is (H * X + Tr) div 10,
    mult(T, X, Tr2, [H2 | Acc], R).
