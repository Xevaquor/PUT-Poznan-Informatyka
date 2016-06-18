min([X], X).
min([H|T], H) :- min(T, MM), H < MM,!.
min([_|T], M) :- min(T, M).

is_convex(List) :- append([H|Mid], [Last], List), min(Mid, M),
	M >= H, M >=Last.

all_convex([], ACC, [ACC]) :- is_convex(ACC).
all_convex([], _, []).
all_convex([H|T], ACC, [Seq|OUT]) :- append(ACC, [H], Seq),
	is_convex(Seq), all_convex(T, Seq, OUT),!.
all_convex([H|T], ACC, OUT) :- append(ACC, [H], Seq),
	all_convex(T, Seq, OUT).


generate([], []).
generate([H|T],OUT) :-all_convex([H|T], [], Buf), generate(T, Inner),
	append(Buf, Inner, OUT).

count([], 0).
count([_|T], C) :- count(T, CC), C is CC + 1.

maximize([], ACCX, ACCX, N) :-  count(ACCX, N),!.
maximize([H|T], OUT, _, ACCN) :- count(H,N), N > ACCN,
	maximize(T, OUT, H, N),!.

maximize([_|T], OUT, ACCX, ACCN) :- maximize(T, OUT, ACCX, ACCN).
maximize([H|T], MAX) :- count(H, N), maximize(T, MAX, H, N).

add_len([],[]).
add_len([H1|T1], [[H1,N]|T]) :- count(H1, N), add_len(T1, T).

find_longest(IN, OUT) :- generate(IN, Seqs),
	maximize(Seqs, OUT).
