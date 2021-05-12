%any_positive(L) -> true
any_positive([H | _]) :-
    H > 0, !.
any_positive([_ | T]) :-
    any_positive(T).


%substitute(A, B, L, Result)
substitute(_, _, [], []).
substitute(A, B, [A | T], [B | Result]) :-
    substitute(A, B, T, Result).
substitute(A, B, [H1 | T], [H1 | Result]) :-
    A =\= H1,
    substitute(A, B, T, Result).

remove_element(_, [], []).
remove_element(A, [A | T], Result) :-
    remove_element(A, T, Result).
remove_element(A, [H | T], [H | Result]) :-
    A =\= H,
    remove_element(A, T, Result).


remove_duplicates([], []).
remove_duplicates([H | T], [H | R2]) :-
    remove_element(H, T, R1),
    remove_duplicates(R1, R2).

push_back(X, [], [X]).
push_back(X, [H | T], [H | Result]) :-
    push_back(X, T, Result).

invert([], []).
invert([H | T], R2) :-
    invert(T, R1),
    push_back(H, R1, R2).

insert(X, [], [X]).
insert(X, [H | T], [H | Result]) :-
    X > H,
    insert(X, T, Result).
insert(X, [H | T], [X, H | T]) :-
    X =< H.

%i_sort(Unsorted, Aux, Sorted)
i_sort([], Aux, Aux).
i_sort([H | T], Temp, Sorted) :-
    insert(H, Temp, Aux),
    i_sort(T, Aux, Sorted).

insertion_sort(List, Sorted) :-
    i_sort(List, [], Sorted).

%bubble(Insert, List, ListModified, Max).
bubble(X, [], [], X).
bubble(X, [H | T], [H | NewT], Max) :-
    X > H,
    bubble(X, T, NewT, Max).
bubble(X, [H | T], [X | NewT], Max) :-
    X =< H,
    bubble(H, T, NewT, Max).

%b_sort(Unordered, Aux, Sort).
b_sort([], Aux, Aux).
b_sort([H | T], Aux, Sorted) :-
    bubble(H, T, NewT, Max),
    b_sort(NewT, [Max | Aux], Sorted).

bubble_sort(List, Sorted) :-
    b_sort(List, [], Sorted).

edge(1, 2).
edge(1, 3).
edge(1, 4).
edge(2, 5).
edge(2, 6).
edge(2, 7).
edge(3, 8).
edge(3, 9).
edge(3, 10).
edge(4, 5).
edge(4, 7).
edge(4, 9).
edge(4, 11).
edge(7, 8).
edge(7, 10).
edge(8, 9).


connected(A, B) :- edge(A, B).
connected(A, B) :- edge(B, A).

next(Current, Next, Visited) :-
    connected(Current, Next),
    not(member(Next,  Visited)).

%dfs_a(Start, Goal, Visited, Path).
dfs_aux(Goal, Goal, _, [Goal]).
dfs_aux(Current, Goal, Visited, [Current | Path]) :-
    next(Current, Next, Visited),
    dfs_aux(Next, Goal, [Next | Visited], Path), !.

dfs(Start, Goal, Path) :-
    dfs_aux(Start, Goal, [Start], Path).

%bfs_aux(Goal, Pending, Visited, Path).
bfs_aux(Goal, [Goal | _], _, [Goal]).
bfs_aux(Goal, [Current | Rest], Visited, [Current | Path]) :-
    Current =\= Goal,
    findall(X, next(Current, X, Visited), Nodes),
    merge(Rest, Nodes, NewPending),
    bfs_aux(Goal, NewPending, [Current | Visited], Path).

bfs(Start, Goal, Path) :-
    bfs_aux(Goal, [Start], [], Path).
