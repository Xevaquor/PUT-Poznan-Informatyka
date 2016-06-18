count([], 0).
count([_|T], C) :- count(T, IC), C is 1 + IC.

how_much(1, 1).
how_much(Size, H) :- SS is Size - 1, how_much(SS, IH), H is IH + Size, !.

hw(Size, ToUse, Iterator) :- how_much(Iterator, IR), IR =< Size,
	I2 is Iterator + 1, hw(Size, ToUse, I2), !.
hw(_, ToUse, Iterator) :- ToUse is Iterator -  1.

rev([], []).
rev([H|T], Lout) :- rev(T, RT), append(RT, [H], Lout).

sum_list([], 0).
sum_list([H|T], S) :- sum_list(T, IS), S is H + IS.

sum_n(_, 0, 0).
sum_n([H|T], N, S) :- NN is N - 1, sum_n(T, NN, IS), S is IS + H.


func(Lin, Sum) :- count(Lin, Size), hw(Size, Normal, 1),
	how_much(Normal, NormalToSum),
	sum_n(Lin, NormalToSum, MidSum),
	rev(Lin, Reversed),
	ToSumLeft is Normal + 1,
	sum_n(Reversed, ToSumLeft, SSum),
	Sum is MidSum + SSum.



