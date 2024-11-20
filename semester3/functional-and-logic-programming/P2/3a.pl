% Merge two sorted lists with removing the double values.

merge([], [], []).
merge(A, [], A).
merge([], B, B).
merge([H1 | T1], [H2 | T2], [H2 | M]):-
    H1 > H2,
    !,
    merge([H1 | T1], T2, M).

merge([H1 | T1], [H2 | T2], [H1 | M]):-
    H1 =:= H2,
    !,
    merge(T1, T2, M).

merge([H1 | T1], [H2 | T2], [H1 | M]):-
    merge(T1, [H2 | T2], M).
