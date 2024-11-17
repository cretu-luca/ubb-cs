/* Write a predicate to substitute an element from a list with another 
 * element in the list. */

substitute([O | T], O, N, [N | T]).
substitute([H | T], O, N, [H | R]):-
    substitute(T, O, N, R).
