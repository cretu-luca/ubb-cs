% generate the list of all permutations with elements
% N, N + 1,..., 2 * N - 1 with the property that the absolute value
% of difference between the consecutive elements from each permutation
% is <= 2

insert(E, L, [E | L]).
insert(E, [H | T], [H | R]):-
	insert(E, T, R).

perm([], []).
perm([H | T], R2):-
    perm(T, R),
    insert(H, R, R2).

abs(X, R):-
    X < 0,
    !,
    R is -X.
abs(X, X).

check_diff([]).
check_diff([_]).
check_diff([H1, H2 | T]):-
    D is H1 - H2,
    abs(D, D2),
    D2 =< 2,
    check_diff([H2 | T]).

gen_list(S, S, []):- !.
gen_list(S, E, [S | R]):-
    S1 is S + 1,
    gen_list(S1, E, R).

one_sol(L, R):-
    perm(L, R),
    check_diff(R).

all_sol(N, Result):-
    N2 is 2 * N,
    gen_list(N, N2, L),
    findall(R, one_sol(L, R), Result).
         
        
        
        
        
        
        
        
        
    
