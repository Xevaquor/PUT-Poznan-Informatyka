

dividors(N, N, 1) :- !.
dividors(N, I, C) :-  N mod I =:= 0, I2 is I + 1,
	dividors(N, I2, CC), C is CC + 1.
dividors(N, I, C) :- N mod I =\= 0, I2 is I + 1,
	dividors(N, I2, C).
dividors(N, C) :- dividors(N, 1, C).

antiprime(0, _) :- !.
antiprime(NN, NC) :- dividors(NN, NNC), NNC >= NC, fail, !.
antiprime(NN, NC) :- dividors(NN, NNC), NC > NNC, XD is NN - 1,
	antiprime(XD, NC).
antiprime(N) :- dividors(N, NC), NN is N - 1, antiprime(NN, NC).
