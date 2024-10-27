% Sort a list with keeping double values in resulted list. E.g.: [4 2 6 2 3 4] --> [2 2 3 4 4 6]

% bubbleSort(L - List, SortedFinal - List)
% flow model: (i, o)
% deterministic
bubbleSort(L, SortedFinal):- 
      bubbleSortAux(L, [], SortedFinal).

% bubbleSortAux(L - List, SortedSoFar - List, SortedFinal - List)
% flow model: (i, i, o)
% deterministic
bubbleSortAux([], SortedSoFar, SortedSoFar).
bubbleSortAux([H | T], SortedSoFar, SortedFinal):- 
    swap(H, T, ListExceptMax, Max),
    bubbleSortAux(ListExceptMax, [Max | SortedSoFar], SortedFinal).

% swap (X - Element, L - List, L - List, Max - Element) 
% flow model: (i, i, o, o)
% deterministic
isolateMax(X, [], [], X).
isolateMax(X, [Y | T], [Y | ListExceptMax], Max):-
    X > Y, 
    !,
    isolateMax(X, T, ListExceptMax, Max).
isolateMax(X, [Y | T], [X | ListExceptMax], Max):-
	isolateMax(Y, T, ListExceptMax, Max).

%isolateMax(X, [Y | T], ListExceptMax, Max):-
%	X == Y,
%	isolateMax(Y, T, ListExceptMax, Max).
