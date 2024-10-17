elimMin(List, Ans):-
    elimMin_aux(List, 100000, _, Ans).
    
% MinD -> minimum going down recursion spiral
% MinU -> minimum coming up recursion spiral
    
elimMin_aux([], MinD, MinD, []).
    
elimMin_aux([Head | Tail], MinD, MinU, [Head | Ans]):-
    Head =< MinD,
    elimMin_aux(Tail, Head, MinU, Ans),
    Head =\= MinU.

elimMin_aux([Head | Tail], MinD, MinU, Ans):-
    Head =< MinD,
    elimMin_aux(Tail, Head, MinU, Ans),
    Head =:= MinU.
    
elimMin_aux([Head | Tail], MinD, MinU, Ans):-
    Head > MinD,
    elimMin_aux(Tail, MinD, MinU, Ans),
    Head =:= MinU.

elimMin_aux([Head | Tail], MinD, MinU, [Head | Ans]):-
    Head > MinD,
    elimMin_aux(Tail, MinD, MinU, Ans),
    Head =\= MinU.
