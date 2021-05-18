%factorial
factorial(1, 1) :- !.

factorial(X, Res) :-
    X1 is X - 1,
    factorial(X1, Aux),
    Res is Aux * X.

sumatoria(End, End, End).
sumatoria(Start, End, Res) :-
    Start < End,
    X1 is Start + 1,
    sumatoria(X1, End, Aux),
    Res is Aux + Start.

% x ^ n = res <=> power(X, N, Res).
power(_, 0, 1).
power(X, N, Res) :-
    N =\= 0,
    N1 is N - 1,
    power(X, N1, Aux),
    Res is Aux * X.

%fibo(N, X) => x se the n-th fibonnaci number
fibo(1, 1).
fibo(2, 1).
fibo(N, X) :-
    N > 2,
    N1 is N - 1,
    fibo(N1, X1),
    N2 is N - 2,
    fibo(N2, X2),
    X is X1 + X2.

% gcd (A, B, Res)
gcd(A, 0, A).
gcd(A, B, Res) :-
    B =\= 0,
    A1 is B,
    B1 is (A mod B),
    gcd(A1, B1, Res).

%first(L, Res) =>
first([H | _ ], H).

rest([_ | T], T).

sum_list([], 0).
sum_list([H | T], Res) :-
    sum_list(T, Aux),
    Res is Aux + H.

find_list([X], X) :- !.
find_list([X | _], X) :- !.
find_list([H | T], X) :-
    H =\= X,
    find_list(T, X).

% remove_from_list(L, X, NewList)
remove_from_list([], _, []).
remove_from_list([X | T], X, Res) :-
    remove_from_list(T, X, Res).
remove_from_list([H | T], X, [H | Aux]) :-
    H =\= X,
    remove_from_list(T, X, Aux).

%my_append(L1, L2, newL3).
my_append([], L2, L2).
my_append([H | T], L2, [H | Aux]) :-
    my_append(T, L2, Aux).

%my_merge(L1, L2, Res).
my_merge([], L2, L2).
my_merge(L1, [], L1).
my_merge([H1 | T1], [H2 | T2], [H1 | Aux]) :-
    H1 < H2,
    my_merge(T1, [H2 | T2], Aux).
my_merge([H1 | T1], [H2 | T2], [H2 | Aux]) :-
    H1 >= H2,
    my_merge([H1 | T1], T2, Aux).

%split(L1, R1, R2)
split([], [], []) :- !.
split([X], [X], []) :- !.
split([H | T], [H | R1], R2) :-
    split(T, R2, R1).

%mergesort(X, Res).
mergesort([], []) :- !.
mergesort([X], [X]) :- !.
mergesort(L, Res) :-
    split(L, M1, M2),
    mergesort(M1, R1),
    mergesort(M2, R2),
    merge(R1, R2, Res).

%filter(L, X, MenoresAX, MayoresAY).
filter([], _, [], []).
filter([H | T], X, [H | Min], Max) :-
    H < X,
    filter(T, X, Min, Max).
filter([H | T], X, Min, [H | Max]) :-
    H >= X,
    filter(T, X, Min, Max).

quicksort([], []) :- !.
quicksort([X], [X]) :- !.
quicksort([H | T], Res) :-
    filter(T, H, Min, Max),
    quicksort(Min, Min1),
    quicksort(Max, Max1),
    my_append(Min1, [H | Max1], Res).

