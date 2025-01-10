% combinations of n taken k
% comb(l1l2..ln, k) = [], if k = 0
% 					  e U comb(l2l3..ln, k - 1), 
% 					  comb(l2l3..ln, k)
comb(_, 0, []).
comb([H | T], K, [H | R]):-
    K > 0,
    K1 is K - 1,
    comb(T, K1, R).
comb([_ | T], K, R):-
    K > 0,
    comb(T, K, R).

% combinations of n taken k, elements in ascending order
% comb(l1l2..ln, k, c1c2..cm) = c1c2..cm, k = 0
%							    comb(L, k - 1, X U c1c2..cm), X < c1, (X, L) = getElem(l1l2..ln) 
%                               comb(L, k, c1c2..cn)
getElem([H | _], H, []).
getElem([H | T], Elem, [H | Res]):-
    getElem(T, Elem, Res).

comb2(_, 0, Col, Col).
comb2(L, K, [H | Col], Res):-
    getElem(L, X, L1),
    X < H,
    K1 is K - 1,
    comb2(L1, K1, [X, H | Col], Res).
comb2(L, K, [H | Col], Res):-
    K > 0,
    getElem(L, _, L1),
    comb2(L1, K, [H | Col], Res).

comb2_aux(L, K, Res):-
    K1 is K - 1, 
    getElem(L, E, L1),
   	comb2(L1, K1, [E], Res). 
