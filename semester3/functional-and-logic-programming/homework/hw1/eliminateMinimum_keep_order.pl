% wrapper function
% eliminateMinimumWrapper(List, List)
% (i, o) -> deterministic
eliminateMinimumWrapper([Head | Tail], Result):-
    findMinimum([Head | Tail], Minimum),
    eliminateMin([Head | Tail], Minimum, Result).


% eliminating the minimum
% eliminateMin(List, Element, List)
% (i, i, o) -> deterministic
eliminateMin([], _, []). 
eliminateMin([Minimum | Rest], Minimum, Rest):- !.
eliminateMin([Head | Rest], Minimum, [Head | Result]):-
    Head \= Minimum, 
    eliminateMin(Rest, Minimum, Result).


% finding the minimum
% findMin(List, Element)
% (i, o) -> deterministic
findMin([Min], Min).
findMin([Head | Tail], Head):-
    findMin(Tail, TailMin),
    Head =< TailMin.
findMin([Head | Tail], TailMin):-
    findMin(Tail, TailMin),
    Head > TailMin.
