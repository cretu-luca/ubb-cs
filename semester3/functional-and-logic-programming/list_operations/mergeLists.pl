appendList([], L2, L2).    

appendList([X | L1], L2, [X | L3]) :-
    append_list(L1, L2, L3).