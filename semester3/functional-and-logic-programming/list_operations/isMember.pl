isMember(X, [X | _]):- !.
    
isMember(X, [_ | Rest]):- 
	isMember(X, Rest).
