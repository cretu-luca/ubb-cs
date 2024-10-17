% wrapper function
% eliminateMinimum(List, List)
% (i, o) -> deterministic
eliminateMinimum([Head | Tail], Result):-
    findMinimum([Head | Tail], Minimum),
    eliminateMinimumAux([Head | Tail], Minimum, Result).


% eliminating the minimum
% eliminateMininumAux(List, Element, List)
% (i, i, o) -> deterministic
eliminateMinimumAux([], _, []). 
eliminateMinimumAux([Minimum | Rest], Minimum, Rest):- !.
eliminateMinimumAux([Head | Rest], Minimum, [Head | Result]):-
    Head \= Minimum, 
    eliminateMinimumAux(Rest, Minimum, Result).


% finding the minimum
% findMinimum(List, Element)
% (i, o) -> deterministic
findMinimum([Min], Min).
findMinimum([Head | Tail], Head):-
    findMinimum(Tail, TailMin),
    Head =< TailMin.
findMinimum([Head | Tail], TailMin):-
    findMinimum(Tail, TailMin),
    Head > TailMin.
