% p(N, sum, prod)

p(0, 0, 1).
p(N, S, P):-N>0,
    N1 is N - 1,
    p(N1, S1, P1),
    S is S1 + N,
    P is P1 * N.
