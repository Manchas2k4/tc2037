#include <iostream>
#include "parser.h"

using namespace std;

int main(int argc, char* argv[]) {
  //Lexer lexer;

  if (argc != 2) {
    cout << "usage: " << argv[0] << " pathname\n";
    return -1;
  }

  /*
  lexer.setInputFile(argv[1]);

  Token *next = NULL;
  do {
    if (next != NULL) {
      delete next;
    }
    next = lexer.nextToken();
    cout << next->toString() << "\n\n";
  } while (next != NULL && next->getTag() != EOL);
  */

  Parser parser;

  parser.analyze(argv[1]);

  return 0;
}
