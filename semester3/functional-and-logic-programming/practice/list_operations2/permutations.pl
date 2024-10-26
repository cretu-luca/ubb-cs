perm([], []).
perm(L, [H | Perm]):-
    delete(H, L, T),
    perm(T, Perm).
   
delete(X, [X | T], T).
delete(X, [H | T], [H | NT]):-
    delete(X, T, NT).
