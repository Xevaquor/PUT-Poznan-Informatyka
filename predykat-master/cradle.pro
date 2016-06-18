%DISCLAIMER
%
%Nie czajê polecenia wiêc pewnie
%nie to co mia³o byæ :v

%http://www.youtube.com/watch?v=Tbm4TqXH2ZA

lshift([], []).
lshift([H|T], OUT) :- append(T, [H], OUT).

rshift([],[]).
rshift(IN, OUT) :- append(STATIC, [DYNAMIC], IN),
	append([DYNAMIC], STATIC, OUT).

sepleft([],_, []).
sepleft([S|T], S, [S|T]).
sepleft([H|T], S, OUT) :- H \= S, lshift([H|T], ACC), sepleft(ACC, S, OUT).

sepright([], _, []).
sepright(IN, S, IN) :- append(_,[S],IN).
sepright(IN, S, OUT) :- append(_,[L],IN), L\=S, rshift(IN, ACC),
	sepright(ACC, S, OUT).


cradle([],_,[]).
cradle([H|T], S, [Hout|Tout]) :- sepleft(H, S, Hout),
	cradle_r(T,S,Tout).
cradle_r([], _ , []).
cradle_r([H|T], S, [Hout|Tout]) :- sepright(H, S, Hout), cradle(T, S, Tout).
