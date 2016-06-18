lshift([H|T], LOUT) :- append(T, [H], LOUT).
rshift(IN, [LAST|X] ) :- append(X, [LAST], IN).

inmiddle(X, [X]).
inmiddle(X, [H|T]) :- X \= H, append(MID, [_], T), inmiddle(X, MID), !.

center_list(X, List, List) :- inmiddle(X, List), !.
center_list(X, List, Out) :- lshift(List, Mid), center_list(X, Mid, Out).


center([], _, []).
center([Hin|Tin],X, [Hout|Tout]) :- center_list(X, Hin, Hout),
	center(Tin,X, Tout), !.
