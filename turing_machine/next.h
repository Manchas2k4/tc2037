#ifndef NEXT_H
#define NEXT_H

typedef unsigned int uint;

typedef enum {L, R, S} direction;

class NextStep {
private:
  uint state;
  char symbol;
  direction moveTo;

public:
  NextStep();
  NextStep(uint, char, direction);
  uint getState() const;
  char getSymbol() const;
  direction getMoveTo() const;
};

NextStep::NextStep()
  : state(0), symbol('B'), moveTo(R) {}

NextStep::NextStep(uint s, char ss, direction m)
  : state(s), symbol(ss), moveTo(m) {}

uint NextStep::getState() const {
  return state;
}

char NextStep::getSymbol() const {
  return symbol;
}

direction NextStep::getMoveTo() const {
  return moveTo;
}

#endif
