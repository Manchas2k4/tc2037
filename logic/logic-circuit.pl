% and(input1, input2, output)
and(1, 1, 1).
and(1, 0, 0).
and(0, 1, 0).
and(0, 0, 0).

% or(input1, input2, output)
or(1, 1, 1).
or(1, 0, 1).
or(0, 1, 1).
or(0, 0, 0).

%xor(input1, input2, output)
xor(1, 1, 0).
xor(1, 0, 1).
xor(0, 1, 1).
xor(0, 0, 0).

%neg(input, output)
neg(1, 0).
neg(0, 1).

%nand(input1, input2, output)
nand(X, Y, Result) :- and(X, Y, Z), neg(Z, Result).

nor(X, Y, Result) :- or(X, Y, Z), neg(Z, Result).

circuit(W, X, Y, Z, Result) :-
  and(W, X, R1),
  neg(Y, R2), or(X, R2, R3),
  and(R1, R3, R4),
  nor(Y, Z, R5),
  or(R4, R5, Result).
