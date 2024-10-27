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
    swap(H, T, ListExceptMax, Max),
    bubbleSortAux(ListExceptMax, [Max | SortedSoFar], SortedFinal).

swap(X, [], [], X).
swap(X, [Y | T], [Y | ListExceptMax], Max):-
    X > Y, 
    !,
    swap(X, T, ListExceptMax, Max).
swap(X, [Y | T], [X | ListExceptMax], Max):-
	swap(Y, T, ListExceptMax, Max).
