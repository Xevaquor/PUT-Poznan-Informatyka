lshift([H|T], OUT) :- append(T, [H], OUT).

count([], 0).
count([_|T], C) :- count(T, IC), C is IC + 1.

is_last([X], X).
is_last([_|T], X) :- is_last(T, X).

is_nth(X, [X|_], 1).
is_nth(X, [H|_], 1) :- X \= H, fail, !.
is_nth(X, [H|T], N) :- X \= H, NN is N - 1, is_nth(X, T, NN), !.

set(List, X, Index, List) :- is_nth(X, List, Index), !.
set(List, X, Index, Lout) :- lshift(List, Mid), set(Mid, X, Index, Lout), !.
wave([], _, [], _, _) :- !.
wave([Hin|Tin], X, [Hout|Tout], Index, _) :-
	count(Hin, C),
	C =:= Index,
	set(Hin, X, Index, Hout),
	Step2 is -1,
	Index2 is Index + Step2,
	wave(Tin, X, Tout, Index2, Step2),!.

wave([Hin|Tin], X, [Hout|Tout], Index, _) :-
	Index =:= 1,
	set(Hin, X, Index, Hout),
	Step2 is 1,
	Index2 is Index + Step2,
	wave(Tin, X, Tout, Index2, Step2), !.

wave([Hin|Tin], X, [Hout|Tout], Index, Step) :-
	set(Hin, X, Index, Hout),
	Index2 is Index + Step,
	wave(Tin, X, Tout, Index2, Step),!.



