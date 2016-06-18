get_step([A, B|_], STEP) :- STEP is B - A.

extract_all_with_step([], _, [], []) :- !.
extract_all_with_step([H|T], STEP, [H|RESULT], OTHER) :-
	get_step(H, STEP), extract_all_with_step(T, STEP, RESULT, OTHER), !.
extract_all_with_step([H|T], STEP, RESULT, [H|OTHER]) :-
	extract_all_with_step(T, STEP, RESULT, OTHER), !.


group([], []).
group([Hin|Tin], [Hout|Tout]) :- get_step(Hin, STEP),
	extract_all_with_step([Hin|Tin], STEP, Hout, Rest),
	group(Rest, Tout).

maxlist([], ACC, ACC) :- !.
maxlist([H|T], ACC, LOUT) :- H > ACC, maxlist(T, H, LOUT), !.
maxlist([_|T], ACC, LOUT) :- maxlist(T, ACC, LOUT).
maxlist([H|T], OUT) :- maxlist(T, H, OUT).

maxx([], ACC, ACC) :- !.
maxx([H|T], ACC, LOUT) :- maxlist(H, IMAX), IMAX > ACC, maxx(T, IMAX, LOUT), !.
maxx([_|T], ACC, LOUT) :- maxx(T, ACC, LOUT).
maxx([H|T], OUT) :- maxlist(H, Initial), maxx(T, Initial, OUT).

minlist([X], X) :- !.
minlist([H|T], H) :- minlist(T, IMIN), H < IMIN, !.
minlist([_|T], MIN) :- minlist(T, MIN).

minn([X], MIN) :- minlist(X, MIN), !.
minn([H|T], CMIN) :- minn(T, IMIN), min_list(H, CMIN), CMIN < IMIN, !.
minn([_|T], MIN) :- minn(T, MIN).

generate_step(MIN, STEP, [H|T], [H|T]) :- H - STEP < MIN, !.
generate_step(MIN, STEP, [H|T], LOUT) :- NEW is H - STEP,
	generate_step(MIN, STEP, [NEW,H|T], LOUT).

change_list([H|T], OUT) :- get_step(H, STEP),
	minn([H|T], MIN), maxx([H|T], MAX), generate_step(MIN, STEP, [MAX], OUT).

combine([], []).
combine([H|T], [Hout|Tout]) :- change_list(H, Hout), combine(T, Tout).

recombine(IN, OUT):- group(IN, MID),combine(MID, OUT).
