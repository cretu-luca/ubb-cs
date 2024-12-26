/* Calculate the alternate sum of list’s elements */

alternate_sum([], 0).
alternate_sum([H], H).
alternate_sum([H1, H2 | T], S):-
    alternate_sum(T, S2), 
    S is S2 + H1 - H2.
