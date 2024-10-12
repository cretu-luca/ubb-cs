isMember(X, [X | Rest]):- !.
    
isMember(X, [Head | Rest]):- 
	isMember(X, Rest).
