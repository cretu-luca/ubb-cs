LCM_List([], 1).

LCM_List([Head | Rest], Result):-
    LCM_List(Rest, Result1),
    Result is LCM(Result1, Head).

LCM(_, _, N, N, N).

LCM(A, B, N, M, Ans):-
    N < M,
    N1 is N + A,
    LCM(A, B, N1, M, Ans).

LCM(A, B, N, M, Ans):-
    N > M,
    M1 is M + B,
    LCM(A, B, N, M1, Ans).
