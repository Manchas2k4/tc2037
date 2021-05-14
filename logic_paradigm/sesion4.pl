any_positive([H | _]) :-
    H > 0, !.
any_positive([_ | T]) :-
    any_positive(T).

substitute(_, _, [], []).
substitute(A, B, [A | T1], [B | R1]) :-
    substitute(A, B, T1, R1).
substitute(A, B, [H1 | T1], [H1 | R1]) :-
    A =\= H1,
    substitute(A, B, T1, R1).

remove_element(_, [], []).
remove_element(A, [A | T1], R1):-
    remove_element(A, T1, R1).
remove_element(A, [H1 | T1], [H1 | R1]) :-
    A =\= H1,
    remove_element(A, T1, R1).

remove_duplicates([], []).
remove_duplicates([H | T], [H | R2]) :-
    remove_element(H, T, R1),
    remove_duplicates(R1, R2).

push_back(X, [], [X]).
push_back(X, [H | T], [H | R1]) :-
    push_back(X, T, R1).

invert([], []).
invert([H | T], R2):-
    invert(T, R1),
    push_back(H, R1, R2).

len([], 0).
len([_ | T], R2) :-
    len(T, R1),
    R2 is R1 + 1.

rotate(L, 0, L).
rotate([H | T], Num, R2) :-
    Num > 0,
    push_back(H, T, R1),
    Num1 is Num - 1,
    rotate(R1, Num1, R2).
rotate(L, Num, R1) :-
    Num < 0,
    len(L, Aux),
    Num1 is Aux + Num,
    rotate(L, Num1, R1).

insert(X, [], [X]).
insert(X, [H | T], [H | R1]) :-
    X > H,
    insert(X, T, R1).
insert(X, [H | T], [X, H | T]) :-
    X =< H.

i_sort([], Acc, Acc).
i_sort([H | T], Acc, Sorted) :-
    insert(H, Acc, Aux),
    i_sort(T, Aux, Sorted).

insertion_sort(List, Sorted) :-
    i_sort(List, [], Sorted).

bubble(X, [], [], X).
bubble(X, [H | T], [H | NewT], Max) :-
    X > H,
    bubble(X, T, NewT, Max).
bubble(X, [H | T], [X | NewT], Max) :-
    X =< H,
    bubble(H, T, NewT, Max).

b_sort([], Acc, Acc).
b_sort([H | T], Acc, Sorted) :-
    bubble(H, T, NewT, Max),
    b_sort(NewT, [Max | Acc], Sorted).

bubble_sort(List, Sorted) :-
    b_sort(List, [], Sorted).

% arc(X, Y): X to Y
arc(1, 2).
arc(1, 3).
arc(1, 4).
arc(2, 5).
arc(2, 6).
arc(2, 7).
arc(3, 8).
arc(3, 9).
arc(3, 10).
arc(3, 6).
arc(4, 5).
arc(4, 7).
arc(4, 11).
arc(4, 9).
arc(7, 8).
arc(7, 10).
arc(8, 9).

connected(A, B) :- arc(A, B).
connected(A, B) :- arc(B, A).

next(Current, Next, Visited) :-
    connected(Current, Next),
    not(member(Next, Visited)).

dfs_a(Goal, Goal, _, [Goal]).
dfs_a(Current, Goal, Visited, [Current | Path]) :-
    next(Current, Next, Visited),
    dfs_a(Next, Goal, [Next | Visited], Path), !.

dfs(Start, Goal, Path) :-
    dfs_a(Start, Goal, [Start], Path).

bfs_a(Goal, [Goal | _], Visited, Visited).

bfs_a(Goal, [Current | Rest], Visited, Path):-
    Current =\= Goal,
    %findall(X, next(Current, X, Visited), Nodes),
    %append(Rest, Nodes, NewPending),
    next(Current, X, Visited),
    push_back(X, Rest, NewPending),
    push_back(Current, Visited, NewVisited),
    bfs_a(Goal, NewPending, NewVisited, Path), !.

bfs(Start, Goal, Path) :-
    bfs_a(Goal, [Start], [], TempPath),
    push_back(Goal, TempPath, Path).
