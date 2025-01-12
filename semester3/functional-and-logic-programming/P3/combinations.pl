% comb(l1l2..ln, k) = { ll, k = 1, n >= 1
% 		      { comb(l2..ln, k), k >= 1
% 		      { l1 U comb(l2..ln, k - 1), k > 1

comb([H | _], 1, [H]).
comb([_ | T], K, R):-
    comb(T, K, R).
comb([H | T], K, [H | R]):-
    K > 1, 
    K2 is K - 1,
    comb(T, K2, R).
