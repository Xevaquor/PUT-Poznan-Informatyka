in2sorted(X, [], [X]).
in2sorted(X, [In2|Tin], Lout) :-
	 X < In2, append([X,In2],Tin,Lout).
in2sorted(X, [In1|Tin], [Hout|Tout]) :- Hout = In1,
	in2sorted(X, Tin, Tout).

i_sort([], X, X).
i_sort([H|T], Acc, Sorted) :- in2sorted(H, Acc, NAcc),
	i_sort(T, NAcc, Sorted).
isort(List, Sorted) :-  i_sort(List, [], Sorted),!.


rev([], []).
rev(In, [Hout|Tout]) :- append(Nolast,[Hout],In),
	 rev(Nolast, Tout),!.
