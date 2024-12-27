% 5.
% a. Write a predicate to compute the union of two sets.
% b. Write a predicate to determine the set of all the pairs of elements in a list.
% Eg.: L = [a b c d] => [[a b] [a c] [a d] [b c] [b d] [c d]].

% a)
my_union([], P, P). 
my_union([H | T], P, [H | R]):-
    \+ is_member(P, H),
    !,
    my_union(T, P, R).
my_union([_ | T], P, R):-
    my_union(T, P, R).
    
is_member([E | _], E).
is_member([_ | T], E):-
    is_member(T, E).

% b)
% my_pairs_aux(L, R2):-
%	my_pairs(L, R),
%   list_to_set(R, R2).
 
my_pairs_aux([H | T], R):-
    my_pairs(T, H, R).

% misses some pairs :/
my_pairs([], _, []).
my_pairs([H], E, [[E, H]]).
my_pairs([H1, H2 | T], E, [[E, H1] | R3]):-
	my_pairs([H2 | T], E, R1),
  	my_pairs(T, H2, R2),
    append(R1, R2, R3).

% works!? (but gives some duplicates ew)
% my_pairs([H1, H2], [[H1, H2]]).
% my_pairs([H1, H2 | T], [[H1, H2] | R3]):-
%    my_pairs([H1 | T], R1),
%    my_pairs([H2 | T], R2),
%    append(R1, R2, R3).
