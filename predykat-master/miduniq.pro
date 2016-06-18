
mid([X], X).
mid([], _) :- fail.
mid(IN, Y) :- append([_|CENTER], [_], IN), mid(CENTER, Y).

middles([], []) :- !.
middles([H|T], [Middle|LOUT]) :- mid(H, Middle), middles(T, LOUT), !.
middles([_|T], LOUT) :- middles(T, LOUT), !.

contains([], _) :- fail.
contains([H|_], H).
contains([H|T], Q) :- H \= Q, contains(T, Q).

uniq([], ACC, ACC).
uniq([Hin|Tin], RES, ACC) :- contains(ACC, Hin), uniq(Tin, RES, ACC).
uniq([Hin|Tin], RES, ACC) :- not(contains(ACC, Hin)), uniq(Tin, RES, [Hin|ACC]).

uniq(IN, OUT) :- uniq(IN, OUT, []).

miduniq(LL, Y) :- middles(LL, MIDS), uniq(MIDS, Y).
