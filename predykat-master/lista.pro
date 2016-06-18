count([], 0).
count([_|T], C) :- count(T, CC), C is CC + 1.


countr([H|T], C) :- countr(H, HC),!, countr(T,TC),!, C is HC + TC.
%countr([_], 1).
countr([],0).
countr(_, 1).

countof([],_,0).
countof([H|T], X, C) :- countof(H, X, CC), countof(T, X, CT),!, C is CC + CT.
countof(X, X, 1).
countof(_, _, 0).

del([] , _, []).
del([H|T], X, L) :- H=:= X, append(T, [], L).
del([H|T], X, L) :- X =\=H, del(T, X, O), append([H],O, L).

del2([], _, []) :-!.
del2([H|T], H, T) :- !.
del2([H|T], X, [H|Y]) :- del2(T,X,Y),!.

last([X],X).
last([_|T], X) :- last(T,X).

nolast([_],[]).
nolast([H|T], [H|X]):- nolast(T,X).

rev([X],[X]).
rev(IN, [Last|Lout]) :- last(IN, Last), nolast(IN, Rest), rev(Rest, Lout).


mid([X],[X]).
mid([_|Tin], X) :- nolast(Tin, Y), mid(Y,X).

palikot([_]).
palikot([]).
palikot([H|T]) :- last(T, L), H =:= L,nolast(T, LL), palikot(LL).


half([X], [X]).
half([X,_], [X]).
half([Hin|Tin], [Hin|Y]) :- nolast(Tin, NL), half(NL, Y).

h2([], [], []).
h2([X], [X], []).
%h2([X,Y], [X], [Y]).
h2(IN, OL, OR) :- append([L|M], [R], IN),
	h2(M, LL, RR),
	append([L],LL, OL), append(RR, [R], OR).

desc([]).
desc([_]).
desc([A,B]) :- A > B.
desc([A,B|T]) :- A > B, desc([B|T]).

diff([A,B], D) :- D =:= B-A.

arit([_],_).
arit([_,_]).
arit([A,B,C|T]) :- C-B =:= B-A, arit([B,C|T]).

min([X], X).
min([H|T], H) :- min(T, MM), H < MM.
min([H|T], MM) :- min(T,MM), MM <H.

in2sorted(X, [], [X]).
in2sorted(X, [A,B|C], OUT) :- A < X, X < B, append([A,X,B],C,OUT).
%in2sorted(X, [A,B|C], [A|OUT]) :- X < A, in2sorted(X, [B|C], Acc).

i2s(X, [], [X]).
i2s(X, [Hin|Tin], [Hin|Tout]) :- X > Hin, i2s(X, Tin, Tout).
i2s(X, [Hin|Tin], [X, Hin|Tin]) :- X =< Hin.

is([X], OUT, ACC) :- i2s(X, ACC, OUT).
is([Hin|Tin], OUT, ACC) :- i2s(Hin, ACC, A2), is(Tin, OUT, A2).

mrg([], [], [], _).
mrg(X, [], LOUT, ACC) :- append(ACC, X, LOUT).
mrg([], X, LOUT, ACC) :- append(ACC, X, LOUT).
mrg([Ah|At], [Bh|Bt], LOUT, ACC) :- Ah < Bh, append(ACC, [Ah], A2),
	mrg(At, [Bh|Bt], LOUT, A2).
mrg([Ah|At], [Bh|Bt], LOUT, ACC) :- Bh =< Ah, append(ACC, [Bh], A2),
	mrg([Ah|At], Bt, LOUT, A2).


ms([], []).
ms([X], [X]).
ms(IN, LOUT) :- h2(IN, L, R),
	ms(L, SL), ms(R, SR),
	mrg(SL,SR, LOUT,[]),!.
