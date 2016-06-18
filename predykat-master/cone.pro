blank(0, []) :- !.
blank(N, [#|T]) :-  NN is N - 1, blank(NN, T).
first(Size, OUT) :- BLANK_COUNT is Size // 2,
	blank(BLANK_COUNT, Blanks),
	append(Blanks,[0|Blanks], OUT).
second(Size, OUT) :- BLANK_COUNT is Size // 2 - 1,
	blank(BLANK_COUNT, Blanks),
	append(Blanks, [0,#,0|Blanks], OUT).

swapl([], []) :- !.
swapl([A,0|T], [0,A|T2]) :- swapr(T,T2),!.
swapl([H|T], [H|T2]) :-swapl(T, T2).

swapr([],[] ):- !.
swapr([0,A|T], [A,0|T]) :- !.
swapr([H|T], [H|T2]) :- swapr(T,T2), !.

cone(1, [OUT]) :- first(1, OUT).
cone(3, [A,B]) :- first(3, A), second(3, B).
cone(N, [A,B|T]) :- first(N, A), second(N, B), down(B, T).

down([0|_],[]).

down(UPPER, [[A|H]|T]) :- swapl(UPPER,[A|H]), down([A|H], T), !.
