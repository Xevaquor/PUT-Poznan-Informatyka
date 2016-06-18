%DISCLAIMER
%
%Zak³adam, ¿e coenty znaczy 1 potem 1+n, potem 1+2n...
%
%oraz
%
%Ma byæ lista list a nie tylko lista.

bevery_n([], _, [], _).
bevery_n([H|T], N, [H|OUT], COUNTER) :- COUNTER mod N =:= 0,
	CC is COUNTER + 1,
	bevery_n(T, N, OUT, CC).
bevery_n([_|T], N, OUT, COUNTER) :- COUNTER mod N =\= 0,
	CC is COUNTER + 1,
	bevery_n(T, N, OUT, CC).

every_n(IN, N, OUT) :- bevery_n(IN, N, OUT,0).

everynth([], [], _).
everynth([H|T], [HH|OUT], N) :- every_n(H, N, HH), NN is N + 1,
	everynth(T, OUT, NN).

everynth(IN, OUT) :- everynth(IN, OUT, 2).
