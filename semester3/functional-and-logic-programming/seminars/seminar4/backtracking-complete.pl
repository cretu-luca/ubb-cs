% subset(L - List, R - List) (i, o)
subset([], []).
subset([H | T], [H | R]):-
    subset(T, R).
subset([_ | T], R):-
    subset(T, R).

% comb(L - List, K - Number, R - List)
comb([H | _], 1, [H]).
comb([_ | T], K, R):-
    K >= 1,
    comb(T, K, R).
comb([H | T], K, [H | R]):-
    K > 1,
    K1 is K - 1,
    comb(T, K1, R).

% insertEl(E - Elem, L - List, R - List) (i, i, o)
insertEl(E, L, [E | L]).
insertEl(E, [H | T], [H | R]):-
    insertEl(E, T, R).

% perm(L1L2...Ln) = [], n = 0
%					insertEl(L1, perm(L2...Ln), n > 0

perm([], []).
perm([H | T], R):-
    perm(T, P),
    insertEl(H, P, R).

arr([H | _], 1, [H]).
arr([_ | T], K, R):-
    K >= 1,
    arr(T, K, R).
arr([H | T], K, R):-
    K > 1,
    K1 is K - 1,
    arr(T, K1, A),
    insertEl(H, A, R).

/* comb(L1L2...Ln, k) = L1, k = 1
 * 						comb(L2...Ln, k), k >= 1
 * 						L1 U comb(L2....Ln, k - 1), k > 1
 * 
 * insertEl(e, L1L2...Ln) = e U L1L2...Ln, n >= 0
 * 							L1 U insertEl(e, L2...Ln), n > 0
 * 
 * perm(L1L2...Ln) = [], n = 0
 * 					 insertEl(L1, perm(L2...Ln), n > 0
 * 
 * arr(L1L2...Ln, k) = L1, k = 1
 * 					   arr(L2...Ln, k), k >= 1, n > 0
 * 					   insertEl(L1, arr(L2...Ln, k - 1), k > 1, n > 0
 */
