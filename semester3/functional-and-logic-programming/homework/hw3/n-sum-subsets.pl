/* For a list a1... an with integer and distinct numbers, define a predicate to determine all subsets with
sum of elements divisible with n. */

% subsets_init(List, Numeral, List)
% flow model: (i, i, o)
% non-deterministic
subsets_init(L, N, S2):-
    subsets(L, N, _, [], S),
    remove_duplicates(S, S2).

% subsets(List, Numeral, List, List, List)
% flow model: (i, i, i, i, o)
% non-deterministic
subsets([], _, [], Acc, Acc).
subsets([H | T], N, [H | Curr], Acc, FinalAcc):-
    subsets(T, N, Curr, [[H | Curr] | Acc], FinalAcc), 
    sum_of_list([H | Curr], Sum),
    Sum mod N =:= 0.
subsets([H | T], N, [H | Curr], Acc, FinalAcc):-
    subsets(T, N, Curr, Acc, FinalAcc), 
    sum_of_list([H | Curr], Sum),
    Sum mod N =\= 0.
subsets([_ | T], N, Curr, Acc, FinalAcc):-
    subsets(T, N, Curr, Acc, FinalAcc).

% sum_of_list(List, Numeral)
% flow model: (i, o)
% deterministic
sum_of_list([], 0).
sum_of_list([H | T], S1):-
    sum_of_list(T, S),
    S1 is S + H.

% remove_duplicates(List, List)
% flow model: (i, o)
% deterministic
remove_duplicates([], []).
remove_duplicates([H | T], [H | R]):-
	\+ is_member(H, T),
    remove_duplicates(T, R).
remove_duplicates([H | T], R):-
    is_member(H, T),
    remove_duplicates(T, R).

% is_member(Numeral, List)
% flow model: (i)
% deterministic
is_member(X, [X | _]).
is_member(X, [_ | T]):-
    is_member(X, T).
