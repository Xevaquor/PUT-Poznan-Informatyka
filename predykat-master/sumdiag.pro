count([], 0).
count([_|T], C) :- count(T, CC), C is CC + 1.

kth([H|_], 1, H).
kth([_|T], K, Y) :- KK is  K - 1, kth(T, KK, Y).

sumdiag(_, 0, 0).
sumdiag(MATRIX, S, INDEX) :- kth(MATRIX, INDEX, ROW),
	kth(ROW, INDEX, CELL), II is INDEX - 1,
	sumdiag(MATRIX, SUBSUM, II), S is CELL + SUBSUM.

sumdiag(MATRIX, SUM) :- count(MATRIX, SIZE), sumdiag(MATRIX, SUM, SIZE).
