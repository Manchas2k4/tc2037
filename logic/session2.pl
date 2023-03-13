fact(1, 1).
fact(N, X) :-
	X > 1,
	X1 is X - 1,
	fact(N1, X1),
	N is X * N1.

