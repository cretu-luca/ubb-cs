% at each iteration, we try to jump over two elements at once
% left with one element -> odd number of elements
% left with no elements -> even number of elements

% evenNumberOfElements (List, Boolean)
% (i, o) -> deterministic

evenNumberOfElements([], true).
evenNumberOfElements([_], false).

evenNumberOfElements([_ | [_ | Tail]], Ans):-
    evenNumberOfElements(Rest, Ans).
