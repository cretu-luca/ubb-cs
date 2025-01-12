% perm(l1l2..ln) = { [], n = 0
%		   { insert(l1, perm(l2..ln), otherwise

% insert(e, l1l2..ln) = { e U l1l2..ln
% 		        { l1 U insert(e, l2..ln)

% inserts E on every position of L
insert(E, L, [E | L]).
insert(E, [H | T], [H | R]):-
    insert(E, T, R).

perm([], []).
perm([H | T], P):-
    perm(T, R),
    insert(H, R, P).
