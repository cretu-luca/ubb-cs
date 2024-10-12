eliminateMinimumWrapper([Head | Rest], Result):-
    eliminateMinimum(Head, Rest, [], Result).

eliminateMinimum(_, [], ListWithoutMinimum, ListWithoutMinimum).

eliminateMinimum(X, [Head | Rest], ListWithoutMinimum, Result):-
    X < Head, 
    eliminateMinimum(X, Rest, [Head | ListWithoutMinimum], Result).

eliminateMinimum(X, [Head | Rest], ListWithoutMinimum, Result):-
    X >= Head, 
    eliminateMinimum(Head, Rest, [X | ListWithoutMinimum], Result).
