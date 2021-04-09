#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <sstream>

enum tag {EOL=1000, NUMBER, ID, FAULT};

/*********** Token ***********/

class Token {
private:
    const int tag;

public:
  Token(int);
  const int& getTag() const;
  virtual const std::string toString() const;
};

Token::Token(int t) : tag(t) {}

const int& Token::getTag() const {
  return this->tag;
}

const std::string Token::toString() const {
  std::stringstream aux;
  aux << "Basic token, symbol = ";
  switch (tag) {
    case EOL  : aux << "EOL"; break;
    default   : aux << (char) this->tag; break;
  }
  return aux.str();
}

/*********** Number ***********/

class  Number : public Token {
private:
  const int value;

public:
  Number(int);
  const int& getValue() const;
  const std::string toString() const;
};

Number::Number(int v) : Token(NUMBER), value(v) {}

const int& Number::getValue() const {
  return this->value;
}

const std::string Number::toString() const {
  std::stringstream aux;

  aux << "NUMBER, value = " << this->value;
  return aux.str();
}

/*********** Identifier ***********/

class Identifier : public Token {
private:
  const std::string lexeme;

public:
  Identifier(int, std::string);
  const std::string& getLexeme() const;
  const std::string toString() const;
};

Identifier::Identifier(int t, std::string l) : Token(t), lexeme(l) {}

const std::string& Identifier::getLexeme() const {
  return this->lexeme;
}

const std::string Identifier::toString() const {
  std::stringstream aux;

  aux << "IDENTIFIER, lexeme = " << this->lexeme;
  return aux.str();
}

#endif
