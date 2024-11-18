/* Write a predicate to substitute in a list a value with all the 
 * elements of another list. */

sub(_, [], _, []).

sub(X, [X | T], L2, C2):-
    !,
    sub(X, T, L2, C),
    merge(L2, C, C2).
    
sub(X, [Y | T], L2, [Y | C]):-
    sub(X, T, L2, C).

merge([], L2, L2).

merge([H | T], L2, [H | R]):-
    merge(T, L2, R).
