/* difference of two numbers in list representation */

diff_main(L1, L2, Rf):-
    reverse(L1, R1),
    reverse(L2, R2),
   	diff(R1, R2, 0, R),
    reverse(R, Rf).

diff([], [], 0, []).
diff([H | T], [], 0, [H | T]):- !.

diff([H | T], [], Tr, [H2 | R]):-
    !,
    H2 is (H - Tr) mod 10,
    (H - Tr >= 0 -> Tr2 is 0; Tr2 is 1),
	diff(T, [], Tr2, R).

diff([H1 | T1], [H2 | T2], Tr, [Hr | R]):-
    !,
    Hr is (H1 - H2 - Tr) mod 10,
    (H1 - H2 - Tr >= 0 -> Tr2 is 0; Tr2 is 1),
    diff(T1, T2, Tr2, R).
