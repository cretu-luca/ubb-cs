% write a program to generate all the subsets of a set with the
% property that the difference between any 2 consecutive elements
% is a multiple of 3; subsets must have at least 2 elements
%
% subsets(L1L2..Ln) = { [], n = 0
% 					  {	L1 U subsets(L2..Ln), n >= 1
%	 				  { subsets(L2..Ln), n >= 1
%
% check(L1L2..Ln) = { true, n = 2 and |L1 - L2| % 3 = 0
% 					{ check(L2..Ln), n >= 2 and |L1 - L2| % 3 = 0
% 					{ false, otherwise

subsets([], []).
subsets([H | T], [H | R]):-
    subsets(T, R). 
subsets([_ | T], R):-
    subsets(T, R).

check([H1, H2 | T]):-
	D is H1 - H2,
    D mod 3 =:= 0,
    (T = [] -> true; check([H2 | T])).
    
one_sol(L, R):-
    subsets(L, R),
    check(R).
    
all_sol(L, Res):-
    findall(R, one_sol(L, R), Res).
