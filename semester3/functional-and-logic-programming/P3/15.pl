% For a given n, positive, determine all decompositions of n as a sum of consecutive natural numbers

subseq(C, N, []):-
    C =:= N, !.
subseq(C, N, R):-
    C < N,
    C2 is C + 1,
    subseq(C2, N, R).
subseq(C, N, [C | R]):-
    C < N,
    C2 is C + 1,
    subseq(C2, N, R).

one_sol(N, R):-
    subseq(1, N, R),
    sum(R, R2),
    R2 =:= N.
           
sum([], 0).
sum([H | T], S):-
	sum(T, S2), 
    S is S2 + H.

all_sols(N, Result):-
  	findall(R, one_sol(N, R), Result).
