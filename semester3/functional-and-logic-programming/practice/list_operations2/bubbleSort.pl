bubbleSortWrapper(L, SortedFinal):- 
      bubbleSortAux(L, [], SortedFinal).

bubbleSortAux([], SortedSoFar, SortedSoFar).

bubbleSortAux([H | T], SortedSoFar, SortedFinal):- 
    swap(H, T, ListExceptMax, Max),
    bubbleSortAux(ListExceptMax, [Max | SortedSoFar], SortedFinal).

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
