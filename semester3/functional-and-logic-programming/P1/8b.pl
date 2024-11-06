% Write a predicate to delete first occurrence of the minimum number from a list.
eliminateMinimumWrapper([Head | Tail], Result):-
    findMin([Head | Tail], Minimum),
    eliminateMin([Head | Tail], Minimum, Result).

eliminateMin([], _, []). 
eliminateMin([Minimum | Rest], Minimum, Rest):- !.
eliminateMin([Head | Rest], Minimum, [Head | Result]):-
    Head \= Minimum, 
    eliminateMin(Rest, Minimum, Result).

findMin([Min], Min).
findMin([Head | Tail], Head):-
    findMin(Tail, TailMin),
    Head =< TailMin.
findMin([Head | Tail], TailMin):-
    findMin(Tail, TailMin),
    Head > TailMin.
