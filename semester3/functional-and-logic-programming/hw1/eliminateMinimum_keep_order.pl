% Wrapper function

eliminateMinimumWrapper([Head | Rest], Result):-
    findMinimum(Rest, Head, Minimum),
    eliminateMininum([Head | Rest], Minimum, Result).


% eliminating the minimum

eliminateMininum([], _, []). 

eliminateMininum([Minimum | Rest], Minimum, Rest):- !.

eliminateMininum([Head | Rest], Minimum, [Head | Result]):-
    Head \= Minimum, 
    eliminateMininum(Rest, Minimum, Result).


% Finding the minimum    
    
findMinimum([], Current, Current).
    
findMinimum([Head | Rest], Current, Minimum):-
	Head < Current,
    findMinimum(Rest, Head, Minimum).

findMinimum([Head | Rest], Current, Minimum):-
    Head >= Current,
    findMinimum(Rest, Current, Minimum).
