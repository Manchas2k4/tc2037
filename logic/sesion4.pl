% insert(X, List1, List2)
insert(X, [], [X]).

insert(X, [Head | Tail], [X, Head | Tail]) :-
  X =< Head.

insert(X, [Head | Tail], [Head | Aux]) :-
  X > Head,
  insert(X, Tail, Aux).

% iSort(List, TempList, OrderedList).
iSort([], TempList, TempList).

iSort([Head | Tail], TempList, OrderedList) :-
  insert(Head, TempList, NewTempList),
  iSort(Tail, NewTempList, OrderedList).

insertionSort(List, OrderedList) :-
  iSort(List, [], OrderedList).

% getMax(X, List1, List1, Max)
getMax(X, [], [], X).

getMax(X, [Head | Tail], [Head | NewTail], Max) :-
  X > Head,
  getMax(X, Tail, NewTail, Max).

getMax(X, [Head | Tail], [X | NewTail], Max) :-
  X =< Head,
  getMax(Head, Tail, NewTail, Max).

% bSort(List, TempList, OrderedList)
bSort([], TempList, TempList).

bSort([Head | Tail], TempList, OrderedList) :-
  getMax(Head, Tail, NewTail, Max),
  bSort(NewTail, [Max | TempList], OrderedList).

bubbleSort(List, OrderedList) :-
  bSort(List, [], OrderedList).

% ------------------- CUT 1 --------------------------%
a(1).

b(1).
b(2).

c(1).
c(2).

d(2).

e(2).

f(3).

p(X) :- b(X), c(X), !, d(X), e(X).
% ------------------- CUT 1 --------------------------%
% ------------------- CUT 2 --------------------------%
i(1).
i(2).

j(1).
j(2).
j(3).

q(X, Y) :- i(X), !, j(Y).

s(0, 0).
s(X, Y) :- q(X, Y).

% ----------------- BFS && DFS ------------------------%
arc(1, 2).
arc(1, 3).
arc(1, 4).
arc(2, 5).
arc(2, 6).
arc(2, 7).
arc(3, 8).
arc(3, 9).
arc(3,10).
arc(4, 5).
arc(4, 7).
arc(4, 11).
arc(4, 9).
arc(7, 8).
arc(7, 10).
arc(8, 9).

connect(A, B) :- arc(A, B).
connect(A, B) :- arc(B, A).

% next(Current, Next, VisitedList)
next(Current, Next, VisitedList) :-
  connect(Current, Next),
  not(member(Next, VisitedList)).

% dfsAux(Current, Goal, VisitedList, Path).
dfsAux(Goal, Goal, _, [Goal]).

dfsAux(Current, Goal, VisitedList, [Current | Path]) :-
  next(Current, Next, VisitedList),
  dfsAux(Next, Goal, [Next | VisitedList], Path).

dfs(Start, End, Path) :-
  dfsAux(Start, End, [], Path).

%pushBack(X, List, Result)
pushBack(X, [], [X]).

pushBack(X, [Head | Tail], [Head | R1]) :-
  pushBack(X, Tail, R1).

% bfsAux(Goal, Pending, Visited, Path)
bfsAux(Goal, [Goal | _], Visited, Visited).

bfsAux(Goal, [Current | Tail], Visited, Path) :-
  Goal =\= Current,
  next(Current, Next, Visited),
  pushBack(Tail, Next, NewPending),
  pushBack(Current, Visited, NewVisited),
  bfsAux(Goal, NewPending, NewVisited, Path).

bfs(Start, End, Path) :-
  bfsAux(End, [Start], [], TempPath),
  pushBack(End, TempPath, Path).
