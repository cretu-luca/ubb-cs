% arr(l1l2..ln, k) = { l1, k = 1
% 		     { arr(l2..ln, k), k >= 1
% 		     { insert(l1, arr(l2..ln, k - 1)), k > 1

arr([E | _], 1, [E]).
arr([_ | T], K, R):-
    arr(T, K, R).
arr([H | T], K, A):-
    K > 1,
    K2 is K - 1,
    arr(T, K2, R),
    insert(H, R, A).
