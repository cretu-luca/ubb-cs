evenNumberOfElements([], 1, false).
evenNumberOfElements([], 0, true).

evenNumberOfElements([_ | Rest], Flag, Ans):-
    NewFlag is 1 - Flag,
    evenNumberOfElements(Rest, NewFlag, Ans).
