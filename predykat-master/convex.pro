count([], 0).
count([_|T], C) :- count(T, IC), C is 1 + IC.
separate_asc([H|T], [H|OUT], Rest) :- separate_asc(T, H, OUT, Rest), !.
separate_asc([H|T], P, [H|OUT], Rest) :- H >= P,
	separate_asc(T, H, OUT, Rest),!.
separate_asc(Rest, _, [], Rest).


separate_desc([A,B|T], [A|DESC]) :- A >= B, separate_desc([B|T], DESC), !.
separate_desc([H|_], [H]) :- !.
separate_desc(_, []) :- !.

separate_convex(IN, OUT) :- separate_asc(IN, Asc, Rest),
	separate_desc(Rest, Desc),  Asc = [_|_], Desc = [_|_],
	append(Asc, Desc, OUT), !.
separate_convex(_, []).

longest([], 0, []).
longest([H|T], C, H) :- count(H,C), longest(T, TC, _), TC < C,!.
longest([_|T], TC, TX) :- longest(T, TC, TX).

all_convex([], []).
all_convex([H|T], [Conv|Tout]) :- separate_convex([H|T], Conv),
	all_convex(T, Tout).


longest_convex(IN, OUT) :- all_convex(IN, Seqs), longest(Seqs, _, OUT).





