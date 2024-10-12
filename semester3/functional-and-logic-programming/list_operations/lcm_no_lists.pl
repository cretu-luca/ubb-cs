lcmWrapper(A, B, Ans):-
    lcm(A, B, A, B, Ans).

lcm(_, _, N, N, N).

lcm(A, B, N, M, Ans):-
    N < M,
    N1 is N + A,
    lcm(A, B, N1, M, Ans).

lcm(A, B, N, M, Ans):-
    N > M,
    M1 is M + B,
    lcm(A, B, N, M1, Ans).
