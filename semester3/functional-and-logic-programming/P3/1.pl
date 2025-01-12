% Write a predicate to generate the list of all subsets with all elements of a given list.
% Eg: [2, 3, 4] N=2 => [[2,3],[2,4],[3,4]]

% comb(l1..ln, k) = { l1, k = 1, n >= 1 
%  		    { comb(l2..ln, k), k >= 1
%		    { l1 U comb(l2..ln, k - 1), k > 1

comb([E | _], 1, [E]).
comb([_ | T], K, R):-
    comb(T, K, R).
comb([H | T], K, [H | R]):-
    K > 1,
    K2 is K - 1,
    comb(T, K2, R).
    
all_combs(L, K, Result):-
    findall(R, comb(L, K, R), Result).
