bubbleSortWrapper(List, SortedFinal):- 
    bubbleSort(List, [], SortedFinal).

bubbleSort([], SortedSoFar, SortedSoFar).

bubbleSort([Head | Rest], SortedSoFar, SortedFinal):- 
    swap(Head, Rest, ListExceptMax, Max),
    bubbleSort(ListExceptMax, [Max | SortedSoFar], SortedFinal).

swap(X, [], [], X).

swap(X, [Y | T], [Y | ListExceptMax], Max):-
    X > Y, 
    swap(X, T, ListExceptMax, Max).

swap(X, [Y | T], [X | ListExceptMax], Max):-
	X < Y,
	swap(Y, T, ListExceptMax, Max).

swap(X, [Y | T], ListExceptMax, Max):-
	X == Y,
	swap(Y, T, ListExceptMax, Max).
