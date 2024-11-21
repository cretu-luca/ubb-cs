% Define a predicate to add after every element from a list, the divisors of that number

insert_divisors([], []).
insert_divisors([H | T], Rr):-
    insert_divisors(T, R),
    find_divisors(H, 1, Ds),
    merge([H | Ds], R, Rr).

find_divisors(N, N, [N]).
find_divisors(N, D, [D | R]):-
    N mod D =:= 0,
    !,
    D1 is D + 1, 
    find_divisors(N, D1, R).
find_divisors(N, D, R):-
    D1 is D + 1,
    find_divisors(N, D1, R).

merge([], L2, L2).
merge([H | T], L2, [H | R]):-
    merge(T, L2, R).
