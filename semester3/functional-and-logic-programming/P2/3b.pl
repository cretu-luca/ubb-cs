% For a heterogeneous list, formed from integer numbers and list of numbers, 
% merge all sublists with removing the double values.

merge_wrapper(L, R):-
    merge_main(L, [], R).

merge_main([], Acc, Acc).

merge_main([H | T], Acc, R):-
    is_list(H),
    !,
    merge(H, Acc, Acc2),
    merge_main(T, Acc2, R).
    
merge_main([_ | T], Acc, R):-
    merge_main(T, Acc, R).

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
