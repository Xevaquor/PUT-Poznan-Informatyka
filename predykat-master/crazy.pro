%lastdigit(0, _) :- !, fail.
lastdigit(N, L) :- L is N mod 10.

nto(N, []) :- N =:= 0.
nto(N, [Y|Ys]) :- N > 0, lastdigit(N, Y), NN is N div 10, nto(NN, Ys).

cnt(_, [], 0).
cnt(Y, [Y|Ys], COUNT) :- cnt(Y, Ys, CC), COUNT is CC + 1.
cnt(N, [Y|Ys], COUNT) :- N \= Y, cnt(N, Ys, COUNT).

crazy_digit(N, L) :- cnt(N, L, OCCURENCES), OCCURENCES =< N.

crazy(N) :- nto(N, L),
	crazy_digit(1, L),
	crazy_digit(2, L),
	crazy_digit(3, L),
	crazy_digit(4, L),
	crazy_digit(5, L),
	crazy_digit(6, L),
	crazy_digit(7, L),
	crazy_digit(8, L),
	crazy_digit(9, L).
