lcmListWrapper([], 1).

lcmListWrapper([Head | Rest], Result):-
    lcmListWrapper(Rest, Result1),
    Result is lcm(Result1, Head).

lcm(_, _, N, N, N).

lcm(A, B, N, M, Ans):-
    N < M,
    N1 is N + A,
    lcm(A, B, N1, M, Ans).

lcm(A, B, N, M, Ans):-
    N > M,
    M1 is M + B,
    lcm(A, B, N, M1, Ans).