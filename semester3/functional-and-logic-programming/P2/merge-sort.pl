merge_sort([], []).
merge_sort([A], [A]).
merge_sort([A, B | T], R):-
   divide([A, B | T], L1, L2),
   merge_sort(L1, S1),
   merge_sort(L2, S2),
   my_merge(S1, S2, R).

divide([], [], []).
divide([A], [A], []).
divide([H1, H2 | T], [H1 | L1], [H2 | L2]):-
   divide(T, L1, L2).

my_merge([], L, L).
my_merge(L, [], L).
my_merge([A | TA], [B | TB], [A | S]):-
   A =< B,
   !,
   my_merge(TA, [B | TB], S).
my_merge([A | TA], [B | TB], [B | S]):-
   my_merge([A | TA], TB, S).
