mplicate(X, 1, [X]) :- !.
mplicate(X, N, [X|T]) :- NN is N - 1, mplicate(X, NN, T).

stepgrow([], _, L, L).
stepgrow([Hin|Tin], INDEX, PREVRES, LOUT) :-
	mplicate(Hin, INDEX, NE), append(PREVRES, NE, MID),
	I2 is INDEX + 1,
	stepgrow(Tin, I2, MID, LOUT).


stepgrow(La, L) :- stepgrow(La, 1, [], L).


