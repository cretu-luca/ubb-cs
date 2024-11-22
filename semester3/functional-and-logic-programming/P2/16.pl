/* difference of two numbers in list representation */

diff_main(L1, L2, Rf2):-
    reverse(L1, R1),
    reverse(L2, R2),
   	diff(R1, R2, 0, R),
    reverse(R, Rf),
    remove_leading_zeros(Rf, Rf2).

diff([], [], 0, []).
diff([H | T], [], 0, [H | T]):- !.

diff([H | T], [], Tr, [H2 | R]):-
    !,
    H2 is (H - Tr + 10) mod 10,
    (H - Tr >= 0 -> Tr2 is 0; Tr2 is 1),
	diff(T, [], Tr2, R).

diff([H1 | T1], [H2 | T2], Tr, [Hr | R]):-
    !,
    Hr is (H1 - H2 - Tr + 10) mod 10,
    (H1 - H2 - Tr >= 0 -> Tr2 is 0; Tr2 is 1),
    diff(T1, T2, Tr2, R).

remove_leading_zeros([0|T], R) :- 
    remove_leading_zeros(T, R).
remove_leading_zeros([H|T], [H|T]) :- 
    H \= 0.
remove_leading_zeros([], [0]).
