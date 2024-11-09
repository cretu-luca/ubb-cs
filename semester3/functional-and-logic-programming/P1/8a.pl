% Write a predicate to determine if a list has even numbers of elements without counting the elements from
% the list

evenLength([]).
evenLength([_, _| T]):-
    evenLength(T).
