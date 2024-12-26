% Write a predicate to select the n-th element of a given list.
% -1 -> invalid index

nthElement([], _, -1).
nthElement([Head | _], 1, Head).
nthElement([_ | Tail], N, Ans):-
    N1 is N - 1,
    nthElement(Tail, N1, Ans).
