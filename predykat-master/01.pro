prepend(L, Y, X) :- Y = [X|L].

last([X], X).
last([_|T], X) :- last(T, X).

first([X|_], X).

prelast([X, _], X).
prelast([_|T], X) :- prelast(T, X).

nolast([_], []).
nolast([H|T], X) :- X = [H|Z],
	nolast(T, Z).

mid([X], X).
mid([_|T], X) :- nolast(T, Z),
	mid(Z, X).

count([], N) :- N = 0.
count([_|T], N) :- count(T, N1),
	N is N1 + 1.

kth([X|_], 1, X).
kth([_|T], K, X) :- K1 is K - 1,
	kth(T, K1, X).

rev([X], [X]).
rev([H|T], X) :- X = [H1|T1],
	last(T, H1),
	first(H, T1),
	nolast(T, Z),
	rev(Z, T1).
