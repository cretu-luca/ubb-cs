insertEnd([], X, [X]).

insertEnd([Head | Rest], X, [Head | Ans]):-
    insertEnd(Rest, X, Ans).
