/* For a heterogeneous list, formed from integer numbers and list of numbers, write a predicate to sort every
sublist, keeping the doubles. */

% bubbleSortHeterogeneous(L - List, SortedFinal - List)
% flow model: (i, o) 
% deterministic
bubbleSortHeterogeneous([], []).

bubbleSortHeterogeneous([H | T], [HSorted | SortedFinal]):-    
	is_list(H),
    !,
    bubbleSort(H, HSorted),
    bubbleSortHeterogeneous(T, SortedFinal).

bubbleSortHeterogeneous([H | T], [H | SortedFinal]):-
    bubbleSortHeterogeneous(T, SortedFinal).

% --------- Bubble Sort - Homogenous Lists ---------------------
bubbleSort(L, SortedFinal):- 
      bubbleSortAux(L, [], SortedFinal).

bubbleSortAux([], SortedSoFar, SortedSoFar).
bubbleSortAux([H | T], SortedSoFar, SortedFinal):- 
    isolateMax(H, T, ListExceptMax, Max),
    bubbleSortAux(ListExceptMax, [Max | SortedSoFar], SortedFinal).

isolateMax(X, [], [], X).
isolateMax(X, [Y | T], [Y | ListExceptMax], Max):-
    X > Y, 
    !,
    isolateMax(X, T, ListExceptMax, Max).
isolateMax(X, [Y | T], [X | ListExceptMax], Max):-
	isolateMax(Y, T, ListExceptMax, Max).
