/* For a list a1... an with integer and distinct numbers, define a predicate to determine all subsets with
sum of elements divisible with n. */

/*
 * 
 * subset_main(L1L2...Ln, N) = U (subset(L1L2...Ln), sum(subset(L1L2...Ln)) mod N = 0)
 * 
 * subset(L1L2...Ln) = [], n = 0
 * 					   subset(L2...Ln), n > 0 
 * 					   L1 U subset(L2...Ln), n > 0
 * 
 * sum(L1L2...Ln) = 0, n = 0
 * 					L1 + sum(L2...Ln), n > 0
 * 
*/

subset_main(L, N, Rf):-
    findall(R, one_sol(L, N, R), Rf).

one_sol(L, N, R):-
    subset(L, R), 
    sum(R, 0, S),
    S mod N =:= 0.

subset([], []).
subset([H | T], [H | R]):-
    subset(T, R).
subset([_ | T], R):-
    subset(T, R).

sum([], S, S).
sum([H | T], S, Sf):-
    S2 is S + H,
    sum(T, S2, Sf).
