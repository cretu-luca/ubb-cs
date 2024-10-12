merge([], L2, L2).

merge([X | L1], L2, [X | L3]) :-
    merge(L1, L2, L3).
