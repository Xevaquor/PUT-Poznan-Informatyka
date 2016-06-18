in2sorted([A,B], [], [[A,B]]).
in2sorted([A,B], [[AH,BH]|T], [[A,B],[AH,BH]|T]) :- A < AH.
in2sorted([A,B], [[AH,BH]|T], [[AH,BH]|ACC]) :- A >= AH,
	in2sorted([A,B], T, ACC).

binsert_sort([], Y, Y).
binsert_sort([Hin|Tin], ACC, OUT) :- in2sorted(Hin, ACC, MID),
	binsert_sort(Tin, MID, OUT).

insert_sort(IN, OUT) :- binsert_sort(IN, [], OUT).

normalize([X], [X]).
%zawiera sie
normalize([[A1,B1],[A2,B2]|T], LOUT) :- B1 >= A2, B1 > B2,
	normalize([[A1,B1]|T], LOUT).
%scal
normalize([[A1,B1],[A2,B2]|T], LOUT) :- B1 >= A2,
%	normalize(T, LOUT).
normalize([[A1,B2]|T], LOUT).
normalize([[A1,B1],[A2,B2]|T], [[A1,B1]|LOUT]) :- B1 < A2,
	normalize([[A2,B2]|T], LOUT).

do_magic(IN, OUT) :- insert_sort(IN, MID), normalize(MID, OUT).
