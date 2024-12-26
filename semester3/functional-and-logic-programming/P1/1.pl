% 2.
% a. Write a predicate to remove all occurrences of a certain atom from a list.
% b. Define a predicate to produce a list of pairs (atom n) from an initial list of atoms. 
% In this initial list atom has n occurrences.
% Eg.: numberatom([1, 2, 1, 2, 1, 3, 1], X) => X = [[1, 4], [2, 2], [3, 1]].

% a)
remove_occ([], _, []).

remove_occ([E | T], E, R):-
    remove_occ(T, E, R).

remove_occ([H | T], E, [H | R]):-
    remove_occ(T, E, R).

% b)
get_occur([], _, 0).

get_occur([E | T], E, C):-
    !,
    get_occur(T, E, C1),
    C is C1 + 1.

get_occur([_ | T], E, C):-
    get_occur(T, E, C).

make_pairs_aux(L, R):-
    make_pairs(L, L, [], R).

make_pairs(_, [], C, C).

make_pairs(L, [H | T], C, R):-
	get_occur(L, H, N), 
	\+ is_member(C, [H, _]),
    !,
    append(C, [[H, N]], C1),
   	make_pairs(L, T, C1, R).
    
make_pairs(L, [_ | T], C, R):-
    make_pairs(L, T, C, R).

is_member([E | _], E):- !.
is_member([_ | T], E):-
	is_member(T, E).
