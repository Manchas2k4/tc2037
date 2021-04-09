#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <fstream>
#include <sstream>
#include <cctype>

class Lexer {
private:
  char current;
  std::ifstream input;
  int line;

public:
  void setInputFile(const std::string);
  Token* nextToken();
};

void Lexer::setInputFile(const std::string pathname) {
  input.open(pathname);

  if (!input.is_open()) {
    throw InputFileException();
  }

  current = ' ';
  line = 1;
}

Token* Lexer::nextToken() {
  if (!input.is_open()) {
    throw InputFileException();
  }

  do {
    input.get(current);
    if (current == ' ' || current == '\t') {
      continue;
    } else if (current == '\n') {
      line = line + 1;
    } else {
      break;
    }
  } while (!input.eof());

  if (isdigit(current)) {
    int value = 0;
    do {
      value = (10 * value) + (current - '0');
      input.get(current);
    } while (isdigit(current));
    input.putback(current);
    return new Number(value);
  }

  if (isalpha(current)) {
    std::stringstream aux;

    do {
      aux << current;
      input.get(current);
    } while (isalpha(current));
    input.putback(current);
    return new Identifier(ID, aux.str());
  }

  if (input.eof()) {
    return new Token(EOL);
  }

  return new Token(current);
}

#endif
