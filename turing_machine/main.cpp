#include <iostream>
#include "tm.h"

using namespace std;

int main(int argc, char* argv[]) {
  TM tm;

  if (argc != 3) {
    cout << "usage: " << argv[0]
        << " transitions_file input_file1\n";
    return -1;
  }

  tm.readTransitionTable(argv[1]);

  tm.readInput(argv[2]);
  tm.checkInput();
  
  return 0;
}
