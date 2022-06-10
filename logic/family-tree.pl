male(caos).
male(erbo).
male(urano).
male(eter).
male(crios).
male(cronos).
male(ceo).
male(oceano).
male(japeto).
male(hiperion).
male(poseidon).
male(hades).
male(zeus).
male(helios).
male(eros).

female(nix).
female(gea).
female(hemera).
female(temis).
female(rea).
female(febe).
female(tetis).
female(tia).
female(mnemosine).
female(leto).
female(hestia).
female(hera).
female(demeter).
female(pleyone).
female(metis).
female(climene).
female(selene).
female(eos).
female(afrodita).

parent(caos, erbo).
parent(caos, urano).
parent(caos, eter).
parent(caos, nix).
parent(caos, gea).
parent(caos, hemera).
parent(urano, temis).
parent(urano, crios).
parent(urano, cronos).
parent(urano, rea).
parent(urano, febe).
parent(urano, ceo).
parent(urano, oceano).
parent(urano, tetis).
parent(urano, japeto).
parent(urano, tia).
parent(urano, hiperion).
parent(urano, mnemosine).
parent(urano, afrodita).
parent(ceo, leto).
parent(cronos, hestia).
parent(cronos, hades).
parent(cronos, poseidon).
parent(cronos, hera).
parent(cronos, zeus).
parent(cronos, demeter).
parent(oceano, pleyone).
parent(oceano, metis).
parent(oceano, climene).
parent(hiperion, helio).
parent(hiperion, selene).
parent(hiperion, eos).

parent(gea, temis).
parent(gea, crios).
parent(gea, cronos).
parent(gea, rea).
parent(gea, febe).
parent(gea, ceo).
parent(gea, oceano).
parent(gea, tetis).
parent(gea, japeto).
parent(gea, tia).
parent(gea, hiperion).
parent(gea, mnemosine).
parent(febe, leto).
parent(rea, hestia).
parent(rea, hades).
parent(rea, poseidon).
parent(rea, hera).
parent(rea, zeus).
parent(rea, demeter).
parent(tetis, pleyone).
parent(tetis, metis).
parent(tetis, climene).
parent(tia, helio).
parent(tia, selene).
parent(tia, eos).
parent(afrodita, eros).

% X is father of Y
father(X, Y) :- parent(X, Y), male(X).

% X is mother of Y
mother(X, Y) :- parent(X, Y), female(X).

% X is son of Y
son(X, Y) :- parent(Y, X), male(X).

% X is daughter of Y
daughter(X, Y) :- parent(Y, X), female(X).

sibling(X, Y) :-
  father(F, X), father(F, Y),
  mother(M, X), mother(M, Y),
  X \= Y.

brother(X, Y) :- sibling(X, Y), male(X).

sister(X, Y) :- sibling(X, Y), female(X).

grandparent(X, Y) :- parent(X, Z), parent(Z, Y).

ancestor(X, Y) :- parent(X, Y).
ancestor(X, Y) :- parent(X, Z), ancestor(Z, Y).

descendant(X, Y) :- ancestor(Y, X).
