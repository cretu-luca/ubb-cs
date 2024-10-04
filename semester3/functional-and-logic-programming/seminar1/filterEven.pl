filterEven([], []).

filterEven([H|T], Rez):-
    H mod 2 =:= 0,
    filterEven(T, Rez).

filterEven([H|T], [H|Rez1]):- 
    H mod 2 =:= 1,
    filterEven(T, Rez1).
