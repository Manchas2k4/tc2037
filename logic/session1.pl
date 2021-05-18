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

neg(1, 0).
neg(0, 1).

nand(X, Y, Z) :- and(X, Y, R), neg(R, Z).

nor(X, Y, Z) :- or(X, Y, R), neg(R, Z).

altXOR(X, Y, Z) :-
    nand(X, Y, R1),
    nand(X, R1, R2),
    nand(R1, Y, R3),
    nand(R2, R3, Z).
