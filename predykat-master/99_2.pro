
is_prime(_, 1) :- !.
is_prime(N, DIVIDOR) :- N mod DIVIDOR =\= 0, DD is DIVIDOR - 1,
	is_prime(N, DD).

is_prime(N) :- NN is N - 1, is_prime(N, NN).

gen_prime(2, []) :- !.
gen_prime(N, [N|L]) :- is_prime(N), NN is N - 1, gen_prime(NN, L), !.
gen_prime(N, L) :- NN is N - 1, gen_prime(NN, L).

rev([X],[X]).
rev(IN, LOUT) :- append([First|MID], [Last], IN),
	rev(MID, ACC), append([Last|ACC], [First], LOUT).

gcd(A, 0, A) :- A > 0.
gcd(A, B, Y) :- B > 0, C is A mod B, gcd(B, C, Y), !.

coprime(A, B) :- gcd(A, B, 1).

phi(_, 1, 1) :- !.
phi(M, R, I) :- I > 0, coprime(M, I),  I2 is I - 1,
	phi(M, RR, I2), R is RR + 1, !.
phi(M, R, I) :- I > 0, I2 is I - 1, phi(M, R, I2).
phi(_, 0, 0).
phi(M, R) :- MM is M - 1, phi(M, R, MM).


factorize(1, [], _).
factorize(N, [ACC|T], ACC) :- N mod ACC =:= 0,
	NN is N div ACC, factorize(NN, T, ACC).
factorize(N, T, ACC) :- N mod ACC =\=0, A2 is ACC + 1,
	factorize(N, T, A2).

factorize(N, L) :- factorize(N, L, 2).


unflat([], ACC, ACC).
unflat([H|T], [[H|OCCURS]|ACC], [[H,NO]|LOUT]) :-
	NO is OCCURS + 1, unflat(T, [[H, NO]|ACC], LOUT).
unflat([H|T], [[H2|OCCURS]|ACC], [[H2|OCCURS],[H, 1]|LOUT).

