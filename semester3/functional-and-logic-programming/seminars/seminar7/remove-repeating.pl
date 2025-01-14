% remove repeating elements from a list
remove_repeating_aux(L, R):-
    remove_repeating(L, L, R).

remove_repeating(_, [], []).
remove_repeating(L, [H | T], R):- 
   	find_occ_aux(L, H, C),
    C > 1,
    !,
    remove_repeating(L, T, R).
remove_repeating(L, [H | T], [H | R]):-
    remove_repeating(L, T, R).

find_occ_aux(L, E, R):-
    find_occ(L, E, 0, R).
find_occ([], _, C, C):- !.
find_occ([E | T], E, C, R):-
   	!,
    C1 is C + 1,
    find_occ(T, E, C1, R).
find_occ([_ | T], E, C, R):-
    find_occ(T, E, C, R).

exists_in(E, [E | _]):- !.
exists_in(E, [_ | T]):-
	exists_in(E, T).

remove_elem(_, [], []):- !.
remove_elem(E, [E | T], R):- 
    !,
    remove_elem(E, T, R).
remove_elem(E, [H | T], [H | R]):-
    remove_elem(E, T, R).

solve([], []).
solve([H | T], R1):-
    exists_in(H, T),
    !,
    remove_elem(H, T, R), 
    solve(R, R1).
solve([H | T], [H | R]):-
    solve(T, R).
