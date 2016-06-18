size([], 0).
size([_|T], S) :- size(T, SS), S is SS + 1.

sum_no_first([], 0, _) :- !.
sum_no_first([H|T], SUM, 0) :-	sum_no_first(T, IS, 0), SUM is IS + H, !.
sum_no_first([_|T], SUM, SKIP) :- NSKIP is SKIP - 1,
	sum_no_first(T, SUM, NSKIP).

sumtriangle(MATRIX,
