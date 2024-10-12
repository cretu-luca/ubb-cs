listLength([], 0).

listLength([_ | Rest], N):-
    listLength(Rest, N1),
    N is N1 + 1.
