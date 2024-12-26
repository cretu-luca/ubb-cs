% Write a predicate to add value 1 after every even element from a list.

addOne([], []).

addOne([H | T], [H | [1 | R]]):-
    H mod 2 =:= 0,
    !,
    addOne(T, R).

addOne([H | T], [H | R]):-
    addOne(T, R).
    
