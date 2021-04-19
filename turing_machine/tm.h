#ifndef TM_H
#define TM_H

#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <map>
#include <set>
#include "next.h"

class TM {
private:
  std::map<uint, std::map<char, NextStep> > transitions;
  std::list<char> input;
  std::set<uint> acceptanceStates;
  bool loadedTransitions, loadedInput;
  uint currentState;
  std::list<char>::iterator currentSymbol;

  void init();
  void displayInfo();

public:
  TM();
  void readTransitionTable(const char* filename);
  void readInput(const char* filename);
  void checkInput();
};

TM::TM()
  : loadedTransitions(false), loadedInput(false) {}

void TM::init() {
  currentState = 0;
  currentSymbol = input.begin();
  currentSymbol++;
}

void TM::displayInfo()  {
  std::list<char>::iterator it1;
  std::cout << "current state = " << currentState << "\n";
  std::cout << "input = ";
  for (it1 = input.begin(); it1 != input.end(); it1++) {
    std::cout << *it1 << " ";
  }
  std::cout << "\n";
  std::cout << "        ";
  int limit = std::distance(input.begin(), currentSymbol);
  for (int i = 0; i < limit; i++) {
    std::cout << "  ";
  }
  std::cout << "^\n";
}

void TM::readTransitionTable(const char* filename) {
  std::ifstream inputFile;
  uint totalStates, currentState, totalTransitions;
  uint nextState, totalAcceptance, acceptanceState;
  char currentSymbol, nextSymbol, nextMove;
  direction dir;

  inputFile.open(filename);
  if (!inputFile.is_open()) {
    std::cout << "File not found\n";
    loadedTransitions = false;
    return;
  }

  inputFile >> totalStates;
  for (int i = 0; i < totalStates; i++) {
    std::map<char, NextStep> stX;

    inputFile >> currentState >> totalTransitions;
    for (int j = 0; j < totalTransitions; j++) {
      inputFile >> currentSymbol >> nextState >> nextSymbol >> nextMove;
      switch(nextMove) {
        case 'R'  : dir = R; break;
        case 'L'  : dir = L; break;
        default   : dir = S; break;
      }
      stX.insert(std::pair<char, NextStep>(currentSymbol,
                            NextStep(nextState, nextSymbol, dir)));
    }
    transitions.insert(std::pair<uint, std::map<char, NextStep> >
      (currentState, stX));
  }
  inputFile >> totalAcceptance;
  for (int i = 0; i < totalAcceptance; i++) {
    inputFile >> acceptanceState;
    acceptanceStates.insert(acceptanceState);
  }

  inputFile.close();

  loadedTransitions = true;
}

void TM::readInput(const char* filename) {
  std::ifstream inputFile;
  char symbol;

  inputFile.open(filename);
  if (!inputFile.is_open()) {
    std::cout << "File not found\n";
    loadedTransitions = false;
    return;
  }

  while (inputFile >> symbol) {
    input.push_back(symbol);
  }
  input.push_front('B');
  input.push_back('B');

  loadedInput = true;
}

void TM::checkInput() {
  bool acceptedTM, errorTM;

  if (!loadedTransitions) {
    std::cout << "The transition table has not been loaded.\n";
    return;
  }

  if (!loadedInput) {
    std::cout << "The entry has not been loaded.\n";
    return;
  }

  init();

  acceptedTM = false;
  errorTM = false;
  while (!acceptedTM && !errorTM) {
    // map<uint, map<char, NextStep> > transitions;
    std::map<char, NextStep> stateTransition;
    std::map<char, NextStep>::iterator itr;
    std::set<uint>::iterator itrSet;
    NextStep next;

    displayInfo();

    itrSet = acceptanceStates.find(currentState);
    if (itrSet != acceptanceStates.end()) {
      acceptedTM = true;
      continue;
    }

    stateTransition = transitions.at(currentState);

    itr = stateTransition.find(*currentSymbol);
    if (itr == stateTransition.end()) {
      errorTM = true;
      continue;
    }

    next = stateTransition.at(*currentSymbol);
    currentState = next.getState();
    *currentSymbol = next.getSymbol();
    switch(next.getMoveTo()) {
      case L  : currentSymbol--; break;
      case R  : currentSymbol++; break;
    }
  }

  if (acceptedTM) {
    std::cout << "The entry has been accepted.\n";
  } else {
    std::cout << "The entry has been rejected.\n";
  }
}

#endif
