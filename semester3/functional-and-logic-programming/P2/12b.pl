/* For a heterogeneous list, formed from integer numbers and list of numbers, define a predicate to add in
every sublist the divisors of every element. */

solve([], []).
solve([H | T], [Hr | R]):-
    is_list(H),
    !,
    solve(T, R), 
    insert_divisors(H, Hr).
solve([H | T], [H | R]):-
    solve(T, R).

insert_divisors([], []).
insert_divisors([H | T], Rr):-
    insert_divisors(T, R),
    find_divisors(H, 2, Ds),
    merge([H | Ds], R, Rr).

find_divisors(1, 2, []).
find_divisors(N, N, []).
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
