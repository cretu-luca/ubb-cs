% at each iteration, we try to jump over 
% left with one element -> odd number of elements
% left with no elements -> even number of elements
evenNumberOfElements([], true).
evenNumberOfElements([_], false).

evenNumberOfElements([_ | [_ | Rest]], Ans):-
    evenNumberOfElements(Rest, Ans).
