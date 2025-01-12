% The list a1... an is given. Write a predicate to determine all sublists strictly ascending of this list a.

subsets([], []).
subsets([_ | T], R):-
    subsets(T, R).
subsets([H | T], [H | R]):-
    subsets(T, R).

one_sol(L, R):-
    subsets(L, R),
    is_ascending(R).

is_ascending([]):- !.
is_ascending([_]):- !.
is_ascending([H, H2 | T]):- 
    H < H2,
    is_ascending([H2 | T]).

asc_subsets(L, Result):-
    findall(R, one_sol(L, R), Result).
    

