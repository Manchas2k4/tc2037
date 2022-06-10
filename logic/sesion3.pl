%substitute(X, Y, List, Result)
substitute(_, _, [], []).

substitute(X, Y, [X | Tail], [Y | R1]) :-
  substitute(X, Y, Tail, R1).

substitute(X, Y, [Head | Tail], [Head | R1]) :-
  X \= Head,
  substitute(X, Y, Tail, R1).

  %removeFromList(Element, List, NewList).
  removeFromList(_, [], []).

  removeFromList(Element, [Element | Tail], Result) :-
    removeFromList(Element, Tail, Result).

  removeFromList(Element, [Head | Tail], [Head | NewList]) :-
    Element \= Head,
    removeFromList(Element, Tail, NewList).

%removeAllDuplicates(List, Result)
removeAllDuplicates([], []).

removeAllDuplicates([Head | Tail], [Head | R2]) :-
  removeFromList(Head, Tail, R1),
  removeAllDuplicates(R1, R2).

%anyPositive(List)
anyPositive([]) :- fail.

anyPositive([X | _]) :- X > 0, !.

anyPositive([_ | Tail]) :-
  anyPositive(Tail).

%pushBack(X, List, Result)
pushBack(X, [], [X]).

pushBack(X, [Head | Tail], [Head | R1]) :-
  pushBack(X, Tail, R1).

%len(List, Size)
len([], 0).

len([_ | Tail], Result) :-
  len(Tail, R1),
  Result is R1 + 1.

%invert(List, Result)
invert([], []) :- !.

invert([Head | Tail], Result) :-
  invert(Tail, R1),
  pushBack(Head, R1, Result).

%rotate(List, Amount, Result)
%=> Amount is positive, rotate right
rotate(List, 0, List) :- !.

rotate([Head | Tail], Amount, Result) :-
  Amount > 0,
  pushBack(Head, Tail, R1),
  NewAmount is Amount - 1,
  rotate(R1, NewAmount, Result).

%myAppend(List1, List2, NewList)
myAppend([], List2, List2).

myAppend([Head | Tail], List2, [Head | R1]):-
  myAppend(Tail, List2, R1).

%myMerge(List1, List2, Result)
myMerge([], List2, List2).

myMerge(List1, [], List1).

myMerge([H1 | T1], [H2 | T2], [H1 | Temp]) :-
  H1 < H2,
  myMerge(T1, [H2 | T2], Temp).

myMerge([H1 | T1], [H2 | T2], [H2 | Temp]) :-
  H1 >= H2,
  myMerge([H1 | T1], T2, Temp).

%mySplit(List, SubList1, SubList2)
mySplit([], [], []) :- !.

mySplit([X], [X], []) :- !.

mySplit([Head | Tail], [Head | SubList2], SubList1) :-
  mySplit(Tail, SubList1, SubList2).

%mergeSort(List, OrderedList).
mergeSort([], []) :- !.

mergeSort([X], [X]) :- !.

mergeSort(List, OrderedList) :-
  mySplit(List, SubList1, SubList2),
  mergeSort(SubList1, OrderedSubList1),
  mergeSort(SubList2, OrderedSubList2),
  myMerge(OrderedSubList1, OrderedSubList2, OrderedList).

%partition(List, Pivot, Lesser, Greater).
partition([], _, [], []) :- !.

partition([Head | Tail], Pivot, [Head | Lesser], Greater) :-
  Head < Pivot,
  partition(Tail, Pivot, Lesser, Greater).

partition([Head | Tail], Pivot, Lesser, [Head | Greater]) :-
  Head >= Pivot,
  partition(Tail, Pivot, Lesser, Greater).

%quickSort(List, OrderedList)
quickSort([], []) :- !.

quickSort([X], [X]) :- !.

quickSort([Head | Tail], OrderedList) :-
  partition(Tail, Head, Lesser, Greater),
  quickSort(Lesser, OrderedLesser),
  quickSort(Greater, OrderedGreater),
  append(OrderedLesser, [Head | OrderedGreater], OrderedList).
