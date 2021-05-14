#include <iostream>
#include <string>
#include <stack>

//const int MAX = 4097;

class APD {
private:
  int state;
  std::stack<char> apdStack;

public:
  void state0(char);
  void state1(char);
  void processEntry(std::string);
};

void APD::state0(char c) {
  char top = apdStack.top();
  if (c == 'a') {
    switch(top) {
      case 'Z'  :
      case 'X'  :
      case 'Y'  : apdStack.push('X'); state = 0; break;
      default   : state = -1; break;
    }
  } else if (c == 'b') {
    switch(top) {
      case 'Z'  :
      case 'X'  :
      case 'Y'  : apdStack.push('Y'); state = 0; break;
      default   : state = -1; break;
    }
  } else if (c == 'c') {
    switch(top) {
      case 'Z'  :
      case 'X'  :
      case 'Y'  : state = 1; break;
      default   : state = -1; break;
    }
  } else {
    state = -1;
  }
}

void APD::state1(char c) {
  char top = apdStack.top();
  if (c == 'a') {
    if (top == 'X') {
      apdStack.pop();
      state = 1;
    } else {
      state = -1;
    }
  } else if (c == 'b') {
    if (top == 'Y') {
      apdStack.pop();
      state = 1;
    } else {
      state = -1;
    }
  } else if (c == ' ') {
    state = (top == 'Z')? 2 : -1;
  }
}

void APD::processEntry(std::string s) {
  char c;
  int i;

  i = 0;
  state = 0;
  apdStack = std::stack<char>();
  apdStack.push('Z');
  while (i <= s.size() && state != -1) {
    c = (i != s.size())? s[i] : ' ';
    std::cout << "state = " << state << " c = ." << c << ".\n";
    switch(state) {
      case 0  : state0(c); break;
      case 1  : state1(c); break;
    }
    i++;
  }

  switch(state) {
    case -1 : std::cout << "NO ACCEPTED\n"; break;
    case 2  : std::cout << "ACCEPTED\n"; break;
  }
}

int main(int argc, char* argv[]) {
  APD apd;
  std::string input;

  std::cout << "Input: ";
  std::getline(std::cin, input);
  apd.processEntry(input);
}
