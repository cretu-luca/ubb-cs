% given an heterogenous list composed of numbers, symbols and lists of numbers, remove the sublists
process([], []).
process([H | T], R):-
	is_list(H),
	process(T, R).
process([H | T], [H | R]):-
    \+ is_list(H),
    process(T, R).
