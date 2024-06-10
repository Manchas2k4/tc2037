%% factorial(N, Result)
factorial(0, 1).
factorial(N, Result) :-
    N > 0,
    N1 is N - 1,
    factorial(N1, R1),
    Result is R1 * N.

count_digits(N, 1) :- N < 10.
count_digits(N, Result) :-
    N >= 10,
    N1 is N / 10,
    count_digits(N1, R1),
    Result is R1 + 1.
