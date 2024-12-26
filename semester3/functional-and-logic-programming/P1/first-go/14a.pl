% Write a predicate to test equality of two sets without using the set difference.

setEqualityWrapper(Set1, Set2):-
    listLength(Set1, L1), 
    listLength(Set2, L2),
    L1 =:= L2,
    setEquality(Set1, Set2).


setEquality([], _).
setEquality([Head | Tail], Set2):-
	isMember(Head, Set2),
    setEquality(Tail, Set2).


isMember(X, [X | _]).
isMember(X, [_ | Tail]):-
    isMember(X, Tail).


listLength([], 0).
listLength([_ | Rest], N):-
    listLength(Rest, N1),
    N is N1 + 1.
