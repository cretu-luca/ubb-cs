/* Remove the n-th element of a list */

remove_n_th(1, [_ | T], T). 
remove_n_th(N, [H | T], [H | R]):-
    M is N - 1,
    remove_n_th(M, T, R).
