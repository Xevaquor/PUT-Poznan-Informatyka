

divisors(_, 0, []) :- !.
divisors(N, I, [I|Tout]) :- N mod I =:= 0, I2 is I - 1,
	divisors(N, I2, Tout).
divisors(N, I, Lout) :- N mod I =\= 0, I2 is I - 1,
	divisors(N, I2, Lout).

divisors(N, L) :- NN is N - 1, divisors(N, NN, L).

sumlist([], 0).
sumlist([H|T], S) :- sumlist(T, InnerSum), S is H + InnerSum.


perfect(N) :- divisors(N, D), sumlist(D, S), N =:= S, !.
