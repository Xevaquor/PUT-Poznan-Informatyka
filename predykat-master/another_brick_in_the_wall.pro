%DISCLAIMER
%Treœæ jest ma³o precyzyjna wiêc pewnie
%chodzi³o o coœ innego

%http://www.youtube.com/watch?v=YR5ApYxkU-U

%nieparzysta
odd([S],S) :- !.
odd([S,_],S) :- !.
odd([S,_,S|T],S) :- odd([S|T],S).

%parzysta
even([_|T], S) :- odd(T,S).

brick_odd([],_).
brick_odd([H|T], S) :- odd(H, S), brick_even(T, S).

brick_even([],_).
brick_even([H|T], S) :- even(H, S), brick_odd(T, S).


bbrick(IN, S) :- brick_odd(IN, S).
bbrick(IN, S) :- brick_even(IN,S).

brick(IN) :- IN=[[S|_]|_], bbrick(IN, S).
brick(IN) :- IN=[[_,S]|_], bbrick(IN, S).
