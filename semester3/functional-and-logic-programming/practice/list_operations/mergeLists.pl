<<<<<<< HEAD:semester3/functional-and-logic-programming/list_operations/mergeLists.pl
appendList([], L2, L2).    

appendList([X | L1], L2, [X | L3]) :-
    append_list(L1, L2, L3).
=======
merge([], L2, L2).

merge([X | L1], L2, [X | L3]) :-
    merge(L1, L2, L3).
>>>>>>> 196acbbbc7fd5de70c8ab5ac349255833563b0bd:semester3/functional-and-logic-programming/practice/mergeLists.pl
