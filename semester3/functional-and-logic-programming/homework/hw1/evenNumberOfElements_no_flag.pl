% at each iteration, we try to jump over two elements at once
% left with one element -> odd number of elements
% left with no elements -> even number of elements

% evenLength (List, Boolean)
% (i, o) -> deterministic

evenLength([], true).
evenLength([_], false).

evenLength([_ | [_ | Tail]], Ans):-
    evenLength(Tail, Ans).
