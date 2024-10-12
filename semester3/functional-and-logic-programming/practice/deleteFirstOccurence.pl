deleteElement([], _, []).

deleteElement([X, Rest], X, Rest):- !.

deleteElement([Head | Rest], X, [Head | Result]):-
    Head \= X,
    deleteElement(Rest, X, Result).
