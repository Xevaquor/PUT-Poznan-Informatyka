%(+lista do sumowania, +maska, -wynik)
summask([], [], 0) :- !.
summask([H|Tlist], [1|Tmask], S) :- summask(Tlist, Tmask, SI),
	S is H + SI, !.
summask([_|Tlist], [0|Tmask], S) :- summask(Tlist, Tmask, SI),
	S is SI.

% (lista, lista masek, dot. najlepszy wynik, dot. najlepsza maska (nr),
% aktualny numer maski, ostateczny wynik
maxmask(_,[], _, ACC_BEST,_, ACC_BEST).
maxmask(List, [HMask|Tmask], ACC_VAL, _, ACC_MASK_ID, OUT) :-
	summask(List, HMask, LocalSum),
	LocalSum > ACC_VAL,
	NEXT_MASK is ACC_MASK_ID + 1,
	maxmask(List, Tmask, LocalSum, ACC_MASK_ID, NEXT_MASK, OUT), !.

maxmask(List, [_|Tmask], ACC_VAL, ACC_BEST, ACC_MASK_ID, OUT) :-
	NEXT_MASK is ACC_MASK_ID + 1,
	maxmask(List, Tmask, ACC_VAL, ACC_BEST, NEXT_MASK, OUT), !.


maxmask(List, [Hmask|Tmask], NR) :-
	summask(List, Hmask, Initial),
	maxmask(List, Tmask, Initial, 1, 2, NR).

