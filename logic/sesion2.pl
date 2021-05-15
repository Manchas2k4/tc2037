% relation(a, b) can be read as relation of a to b
dad(billy, bob).
dad(bob, sue).
dad(bob, alex).
dad(alex, john).
dad(john, pete).

mom(ana, erika).
mom(erika, sue).
mom(sue, sussy).
mom(ana, billy).

% rule
grandpa(X, Z) :-
    dad(X, Y), dad(Y, Z);
    dad(X, Y), mom(Y, Z).


grandma(X, Z) :-
    mom(X, Y), dad(Y, Z);
    mom(X, Y), mom(Y, Z).

grandparent(X, Z) :-
    grandpa(X, Z);
    grandma(X, Z).

ancestor(X, Z) :-
    dad(X, Z);
    mom(X, Z).

ancestor(X, Z) :-
    mom(X, Y),
    ancestor(Y, Z).

ancestor(X, Z) :-
    dad(X, Y),
    ancestor(Y, Z).

%ancestor(X, Y) :- (mon(X, Y); dad(X, Y)), ancestor(Y, Z).

%aux(X, Y) :- ((mom(X, Y), mom(X, Z)); (dad(X, Y), dad(X, Z))), Y \= Z.

sibling(Y, Z) :-
    mom(X, Y),
    mom(X, Z),
    Y \= Z.

sibling(Y, Z) :-
    dad(X, Y),
    dad(X, Z),
    Y \= Z.

relative(Y, Z) :-
    sibling(Y, Z);
    ancestor(Y, Z);
    ancestor(Z, Y).
