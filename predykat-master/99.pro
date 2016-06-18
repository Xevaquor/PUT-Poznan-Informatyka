my_last([X], X).
my_last([_|T], X) :- my_last(T, X).

m2([X,_], X).
m2([_,B|T], X) :- m2([B|T], X).

kth([Hin|_], 1, Hin).
kth([_|Tin], K, OUT) :- KK is K - 1, kth(Tin, KK, OUT).

cl([], 0).
cl([_|Tin], COUNT) :- cl(Tin, INNER), COUNT is INNER + 1.

nolast([_], []).
nolast([Hin|Tin], [Hout|Tout]) :- Hin = Hout, nolast(Tin, Tout).

rev([X],[X]).
rev(IN, [Hout|Tout]) :- my_last(IN, Hout), nolast(IN, REVERSED),
	rev(REVERSED, Tout).

pal([]).
pal([_]).
pal([H|T]) :- my_last(T,H),!, nolast(T, CUT), pal(CUT).

pal2(X) :- rev(X,X).
%needs expanding
%flat(X, Y) :- is_list(X), flat(X, Y).
%flat(X, Y)
%
%expand(X, Y


flatt([], OUT, ACC) :- OUT = ACC,!.
flatt([Hin|Tin], OUT, ACC) :- is_list(Hin), flatt(Hin, FHEAD, []),
       append(ACC, FHEAD, A2), flatt(Tin, OUT, A2),!.
flatt([Hin|Tin], OUT, ACC) :- append(ACC, [Hin], A2), flatt(Tin, OUT, A2).

f2(X, [X]) :- \+ is_list(X).
f2([], []).
f2([H|T], OUT) :- f2(H, X), f2(T, Y), append(X, Y, OUT).

uniq([X], [X]).
uniq([A,B|T], OUT) :- A = B, uniq([B|T], OUT).
uniq([A,B|T], [Hout|Tout]) :- A\=B, Hout=A, uniq([B|T], Tout).

pack([], []).
pack([X|Xs], [Y|Ys]) :- transfer(X, Xs, Zs, Y), pack(Zs, Ys).

transfer(_, [],[],[]).
transfer(X, [H|T], T, [X]) :- X \= H.
transfer(X, [X|T], LEFT, [X|Tout]) :- transfer(X, T, LEFT, Tout).

recount([], []).
recount([Hin|Tin], [Hout|Tout]) :- cl(Hin, COUNT), my_last(Hin, ELEM),
	Hout = [COUNT,ELEM], recount(Tin,Tout).


recount2([], []).
recount2([Hin|Tin], [Hout|Tout]) :- cl(Hin, 1), my_last(Hin, ELEM),
	Hout = ELEM, recount2(Tin,Tout),!.

recount2([Hin|Tin], [Hout|Tout]) :- cl(Hin, COUNT), my_last(Hin, ELEM),
	Hout = [COUNT,ELEM], recount2(Tin,Tout).

gen_list(_, 0, []).
gen_list(X, COUNT, [X|Ys]) :- COUNT @> 0, CC is COUNT - 1, gen_list(X, CC, Ys),!.

expand_item([A,B], Y) :- gen_list(B, A, Y), !.
expand_item(X, [X]).

uncompress([], []).
uncompress([Hin|Tin], Y) :- expand_item(Hin, HU), uncompress(Tin, ACC),
	append(HU, ACC, Y).

%dupli([], []).
dupli([X], [X,X]).
dupli([Hin|Tin], [Hin,Hin|Tout]) :- dupli(Tin, Tout).


dupli([X], [X], 1).
dupli([X], [X|T], N) :- N > 1, NN is N - 1, dupli([X], T, NN).

dupli([Hin|Tin], OUT, N) :- dupli([Hin], HDUP, N), dupli(Tin, TDUP, N),
	append(HDUP, TDUP, OUT).


todel(N, ACC) :- ACC mod N =:= 0.

dropb([_|Tin], OUT, N, ACC) :- ACC2 = ACC + 1, ACC2 mod N =:= 0,
	dropb(Tin, OUT, N, ACC2).
dropb([Hin|Tin], [Hin|Tout], N, ACC) :- ACC2 = ACC + 1, ACC2 mod N =\= 0,
	dropb(Tin, Tout, N, ACC2).
dropb([], [], _, _).

dropc([_|Tin], OUT, N, ACC) :- ACC2 = ACC + 1, ACC2 mod N =:= 0,
	dropc(Tin, OUT, N, ACC2),!.
dropc([Hin|Tin], [Hin|Tout], N, ACC) :- ACC2 = ACC + 1,
	dropc(Tin, Tout, N, ACC2).
dropc([], [], _, _).

split([], _,  [], []).
split([Hin|Tin], N, [Hin|TLOUT], ROUT) :- N > 0,
	split(Tin, N - 1, TLOUT, ROUT),!.
split([Hin|Tin], N, LOUT, [Hin|TROUT]) :- split(Tin, N, LOUT, TROUT).

slice([], _, _, []).
slice([Hin|Tin], I, K, [Hin|Tout]) :- I =< 1, K >= 1,
	slice(Tin, I - 1, K - 1, Tout), !.
slice([_|Tin], I, K, OUT) :- slice(Tin, I -  1, K-1, OUT).

lshift(IN, N, OUT) :- N >= 0, split(IN, N, DYN, STAT), append(STAT, DYN, OUT).
lshift(IN, N, OUT) :- N < 0, length(IN, LEN), split(IN, LEN +  N, STAT, DYN),
	append(DYN, STAT, OUT).

rem_at([], _, []).
rem_at([_|Tin], INDEX, Tin) :- INDEX =:= 1,!.
rem_at([H|Tin], INDEX, [H|Tout]) :- rem_at(Tin, INDEX - 1, Tout).

ins_at(X, IN, 1, [X|IN]).
ins_at(X, [H|Tin], INDEX, [H|Tout]) :- II is INDEX -  1,
	ins_at(X, Tin, II, Tout).

range(LO, LO, [LO]) :- !.
range(LO, HI, [LO|TAIL]) :- LO < HI, LL is LO + 1, range(LL,HI,  TAIL).

crand(LO, HI, X) :- random(SEED),  S2 is SEED * (HI- LO) + LO, round(S2, X).

rnd_sel(_, 0, []).

rnd_sel(IN, C, [H|T]) :- C > 0,
	length(IN, HI),
	crand(1, HI, INDEX),
	rem_at(IN, INDEX, ACC), CC is HI - C - 1, rnd_sel(ACC, CC, OUT).

lotto(C, BOUND, OUT) :- C >0, range(1, BOUND, ALL),
	rnd_sel(ALL, C, OUT).

is_prime(_, 1) :- !.
is_prime(N, DIVIDOR) :- N mod DIVIDOR =/= 0, DD is DIVIDOR - 1,
	is_prime(N, DD).

is_prime(N) :- NN is N - 1, is_prime(N, NN).
