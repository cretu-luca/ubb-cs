% function wrapper

eliminateMinimumWrapper([Head | Rest], Result):-
    eliminateMinimum(Head, Rest, [], Result).


% eliminating the minimum by holding two buckets: one for those left to procees, another for the result so far

eliminateMinimum(_, [], ListWithoutMinimum, ListWithoutMinimum).

eliminateMinimum(X, [Head | Rest], ListWithoutMinimum, Result):-
    X < Head, 
    eliminateMinimum(X, Rest, [Head | ListWithoutMinimum], Result).

eliminateMinimum(X, [Head | Rest], ListWithoutMinimum, Result):-
    X >= Head, 
    eliminateMinimum(Head, Rest, [X | ListWithoutMinimum], Result).
