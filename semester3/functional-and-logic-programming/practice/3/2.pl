% For any given positive natural number N, generate all the sets of prime numbers that add up to N (including N, if applicable). 
% Write the mathematical model, flow model and the meaning of all variables for each predicate used. 
% Ex: for N = 18 => [[2,3,131, [2,5,111, [5,131, [7,11]].

subsets([], []).
subsets([H | T], [H | R]):-
    subsets(T, R).
subsets([_ | T], R):-
    subsets(T, R).

is_prime(N):-
    N > 1,
    \+ num_factors(N, 2).

num_factors(N, D):-
    D * D =< N,
    (
    	N mod D =:= 0;
    	D1 is D + 1,
        num_factors(N, D1)
    ).

check([], 0). 
check([H | T], N):-
    is_prime(H),
    N1 is N - H,
    check(T, N1).

gen_numbers(0, []).
gen_numbers(N, [N | R]):-
	N1 is N - 1,
    gen_numbers(N1, R).
    
one_sol(L, N, R):-
    subsets(L, R),
    check(R, N).

all_sol(N, Res):-
    gen_numbers(N, L),
    findall(R, one_sol(L, N, R), Res).
    
