/* Find the longest sequence of consecutive even numbers */

even_seq_main(L, R):-
	even_seq(L, none, [], 0, [], 0, R).

even_seq([], _, _, _, MaxSeq, _, MaxSeq).

even_seq([H | T], LastEl, CurrAcc, CurrLen, MaxSeq, MaxLen, Res) :-
    H mod 2 =:= 0,
    (LastEl = none ; H =:= LastEl + 2),
    !, 
    merge(CurrAcc, H, NewCurrAcc),
    CurrLen1 is CurrLen + 1,
    (CurrLen1 > MaxLen -> NewMaxSeq = NewCurrAcc, NewMaxLen = CurrLen1; 
        				  NewMaxSeq = MaxSeq, NewMaxLen = MaxLen),
    even_seq(T, H, NewCurrAcc, CurrLen1, NewMaxSeq, NewMaxLen, Res).

even_seq([H | T], _, _, _, MaxSeq, MaxLen, Res) :-
    H mod 2 =:= 0,
    !,
    CurrAcc = [H],
    CurrLen = 1,
    (CurrLen > MaxLen -> NewMaxSeq = CurrAcc, NewMaxLen = CurrLen; 
        				 NewMaxSeq = MaxSeq, NewMaxLen = MaxLen),
    even_seq(T, H, CurrAcc, CurrLen, NewMaxSeq, NewMaxLen, Res).

even_seq([_ | T], _, _, _, MaxSeq, MaxLen, Res) :-
    even_seq(T, none, [], 0, MaxSeq, MaxLen, Res).

merge([], E, [E]).
merge([H | T], E, [H | R]):-
    merge(T, E, R).
