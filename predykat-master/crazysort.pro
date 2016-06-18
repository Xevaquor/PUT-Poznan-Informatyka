bget_occurs([], _, ACC, ACC).
bget_occurs([X|Ys], POS, OUT, ACC) :- NP is POS + 1,
	bget_occurs(Ys, NP, OUT, [[X,POS]|ACC]).
get_occurs(IN, OUT) :- bget_occurs(IN, 1, OUT, []).

into([ELEM, INDEX], [], [[ELEM, INDEX]]).
into([ELEM, INDEX], [[ELEM2, INDEX2]|Ys], [[ELEM2, INDEX2]|ACC]) :-
	ELEM \= ELEM2,
	into([ELEM, INDEX], Ys, ACC).
into([ELEM, INDEX], [[ELEM, OLD_INDEX]|Ys], [[ELEM, DIFF]|Ys]) :-
	DIFF is  OLD_INDEX - INDEX.


normalize([], ACC, ACC).
normalize([[ELEM,INDEX]|T], OUT, ACC) :- into([ELEM,INDEX], ACC, A2),
	normalize(T, OUT, A2).

merge(A, [], A).
merge([], A, A).
merge([[E,CL]|TL], [[E2,CR]|TR], [[E,CL]|Ys]) :- CL =< CR,
	merge(TL, [[E2,CR]|TR], Ys).
merge([[E,CL]|TL], [[E2,CR]|TR], [[E2,CR]|Ys]) :- CL > CR,
	merge(TR, [[E,CL]|TL], Ys).



half([X], [X], []).
half([], [], []).
half(IN, LEFT, RIGHT) :- append([L|M],[R],IN),
	half(M, LL, RR),
	append([L], LL, LEFT),
	append([R], RR, RIGHT).

mergesort([X], [X]).
mergesort(IN, OUT) :- half(IN, L, R),
	mergesort(L, LL),
	mergesort(R, RR),
	merge(LL, RR, OUT).

select_names([], []).
select_names([[ENTRY, _]|T], [ENTRY|Ys]) :- select_names(T, Ys).

crazy_sort(IN, OUT) :- get_occurs(IN, MID),
	normalize(MID, MID2, []), mergesort(MID2, MID3),!,
	select_names(MID3, OUT).
