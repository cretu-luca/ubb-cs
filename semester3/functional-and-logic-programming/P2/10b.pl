/* For a list of integer numbers, define a predicate to write twice in list every prime number. */

double_primes_init([], []).
double_primes_init([H | T], [Hr | R]):-
    is_list(H),
    !,
    double_primes(H, Hr),
    double_primes_init(T, R).
        
double_primes_init([H | T], [H | R]):-
    double_primes_init(T, R).
        
double_primes([], []).
double_primes([H | T], [H, H | R]):-
    is_prime(H),
    double_primes(T, R).

double_primes([H | T], [H | R]):-
    \+ is_prime(H),
    double_primes(T, R).

is_prime(N):-
    N > 1,
    \+ has_divisor(N, 2).

has_divisor(N, D) :-
    D * D =< N,
    (N mod D =:= 0;
    has_divisor(N, D + 1)).
