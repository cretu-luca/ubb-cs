% Insert an element on the position n in a list.

insert([H | L], X, N, [H, X | L]):-
    N =:= 1.

insert([H | L], X, N, [H | R]):-
    N1 is N - 1,
    insert(L, X, N1, R).
