mmember(X, [X|_]).
mmember(X, [_ | Tail]) :-
    mmember(X, Tail).


count([], 0).
count([_ | Tail], Result) :-
    count(Tail, R1),
    Result is R1 + 1.

%% mappend(L1, L2, List_Result)
mappend([], L2, L2).
mappend([Head | Tail], L2, [Head | R1]) :-
    mappend(Tail, L2, R1).

%% mreverse(L1, List_Result)
mreverse([], []).
mreverse([Head | Tail], Result) :-
    mreverse(Tail, R1),
    mappend(R1, [Head], Result).