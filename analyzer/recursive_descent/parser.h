#ifndef PARSER_H
#define PARSER_H

#include "exception.h"
#include "token.h"
#include "lexer.h"

class Parser {
private:
    Lexer lexer;
    Token *token;

    void check(int);
    void E();
    void T();
    void F();
    void H();
    void EPrime();
    void TPrime();
    void FPrime();

public:
  ~Parser();
  void analyze(const std::string);
};

Parser::~Parser() {
  if (token != NULL) {
    delete token;
  }
}

void Parser::check(int tag) {
  if (token->getTag() == tag) {
    delete token;
    token = lexer.nextToken();
  } else {
    throw SyntaxException();
  }
}

void Parser::analyze(const std::string pathname) {
  lexer.setInputFile(pathname);
  token = lexer.nextToken();
  E();
  std::cout << "ACCEPTED\n";
}

void Parser::E() {
  T();
  EPrime();
}

void Parser::T() {
  F();
  TPrime();
}

void Parser::F() {
  H();
  FPrime();
}

void Parser::H() {
  if (token->getTag() == NUMBER) {
    check(NUMBER);
  } else if (token->getTag() == ID) {
    check(ID);
  } else if (token->getTag() == ((int) '(')) {
    check((int) '(');
    E();
    check((int) ')');
  } else {
    throw SyntaxException();
  }
}

void Parser::EPrime() {
  if (token->getTag() == ((int) '+')) {
    check((int) '+');
    T();
    EPrime();
  } else if (token->getTag() == ((int) '-')) {
    check((int) '-');
    T();
    EPrime();
  } else {
    // do nothing
  }
}

void Parser::TPrime() {
  if (token->getTag() == ((int) '*')) {
    check((int) '*');
    F();
    TPrime();
  } else if (token->getTag() == ((int) '/')) {
    check((int) '/');
    F();
    TPrime();
  } else {
    // do nothing
  }
}

void Parser::FPrime() {
  if (token->getTag() == ((int) '^')) {
    check((int) '^');
    H();
    FPrime();
  } else {
    // do nothing
  }
}

#endif
