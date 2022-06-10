%X times Y = Z
%RECURSIVE VERSION
times(1, Y, Y).

times(X, Y, Z) :-
  X > 1,
  X1 is X - 1,
  times(X1, Y, Z1),
  Z is Z1 + Y.

%TAIL VERSION
timesT(0, _, Acc, Acc).

timesT(X, Y, Acc, Z) :-
  X > 0,
  X1 is X - 1,
  NewAcc is Acc + Y,
  timesT(X1, Y, NewAcc, Z).

%factorial
%RECURSIVE VERSION
factorial(1, 1).

factorial(X, Result) :-
  X > 1,
  X1 is X - 1,
  factorial(X1, R1),
  Result is X * R1.

%TAIL VERSION
factorialT(0, Acc, Acc).

factorialT(X, Acc, Result) :-
  X > 0,
  X1 is X - 1,
  NewAcc is Acc * X,
  factorialT(X1, NewAcc, Result).

%fibo
%RECURSIVE VERSION
fibo(1, 1).

fibo(2, 1).

fibo(N, Result) :-
  N > 2,
  N1 is N - 1,
  fibo(N1, R1),
  N2 is N - 2,
  fibo(N2, R2),
  Result is R1 + R2.

%TAIL VERSION
fiboT(1, _, Acc, Acc).

fiboT(N, T1, T2, Result) :-
  N > 1,
  N1 is N - 1,
  NewT is T2 + T1,
  fiboT(N1, T2, NewT, Result).

%sum
%RECURSIVE VERSION
sum(End, End, End).

sum(Start, End, Result) :-
  Start < End,
  S1 is Start + 1,
  sum(S1, End, R1),
  Result is Start + R1.

%TAIL VERSION
sumT(End, End, Acc, Result) :-
  Result is Acc + End.

sumT(Start, End, Acc, Result) :-
  Start < End,
  S1 is Start + 1,
  NewAcc is Acc + Start,
  sumT(S1, End, NewAcc, Result).

% X is the first element of List
first(X, [X | _]).

% X is the rest of List
rest(X, [_ | X]).

%sumList
% X is the sum of elements of List
%RECURSIVE VERSION
sumList([], 0).

sumList([Head | Tail], Result) :-
  sumList(Tail, R1),
  Result is Head + R1.

%TAIL VERSION
sumListT([], Acc, Acc).

sumListT([Head | Tail], Acc, Result) :-
  NewAcc is Acc + Head,
  sumListT(Tail, NewAcc, Result).

%findList(X, List)
findList(_, []) :- fail.

findList(X, [X | _]) :- !.

findList(X, [Head | Tail]) :-
  X \= Head,
  findList(X, Tail).

%removeFromList(X, List1, List2).
removeFromList(_, [], []).

removeFromList(X, [X | Tail], Result) :-
  removeFromList(X, Tail, Result).

removeFromList(X, [Head | Tail], [Head | R1]) :-
  X \= Head,
  removeFromList(X, Tail, R1).
