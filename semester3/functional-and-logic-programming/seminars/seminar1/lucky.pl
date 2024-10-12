lucky(4).
lucky(7).

lucky(N):- N mod 10 =:= 4, 
	N1 is N div 10, 
    lucky(N1).

lucky(N):- N mod 10 =:= 7, 
    N1 is N div 10, 
    lucky(N1).
