deldiff(_, [], []).
deldiff(X, [X|Tin], [X|Tout]) :- deldiff(X, Tin, Tout), !.
deldiff(X, [_|Tin], Tout) :- deldiff(X, Tin, Tout).

allafter([H|T], H, T):- !.
allafter([_|Tin], X, Tout) :- allafter(Tin, X, Tout).

occur(_, [], 0).
occur(X, [X|T], C) :- CC is C - 1, occur(X, T, CC), !.
occur(X, [_|T], C) :- occur(X, T, C).

sum_n(_, 0, 0).
sum_n([H|T],N, S) :- NN is N - 1 ,sum_n(T, NN, IS), S is IS + H.

adduplist(Lin, [Hout|Tout], N) :- sum_n(Lin, N, Hout), NN is N + 1,
	adduplist(Lin, Tout, NN), !.
adduplist(_, [], _).

adjacent(X, Y, [X,Y|_]).
adjacent(X, Y, [Y,X|_]).
adjacent(X, Y, [_|T]) :- adjacent(X, Y, T).

sumpair([], []).
sumpair([A,B|Tin], [C|Tout]) :- C is A + B, sumpair(Tin, Tout), !.
sumpair([X], [X]).

altersign(1, [-1]).
altersign(N, [N|Tout]) :- N mod 2 =:= 0, NN is N - 1, altersign(NN, Tout),!.
altersign(N, [Hout|Tout]) :- Hout is -N,  NN is N - 1, altersign(NN, Tout).

altersign2(1, [-1]).
altersign2(N, Tout) :- N mod 2 =:= 0, NN is N - 1, altersign2(NN, Acc),
	append(Acc, [N], Tout), !.
altersign2(N, Tout) :- NN is N - 1, altersign2(NN, Acc),
	append(Acc, [-N], Tout).

head([H|_], H).
heads([], []).
heads([Hin|Tin], [Hout|Tout]) :- head(Hin, Hout), heads(Tin, Tout).

prepend(_, [], []).
prepend(E, [Hin|Tin], [Hout|Tout]) :- Hout = [E|Hin], prepend(E, Tin, Tout).
