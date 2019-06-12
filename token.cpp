#include "token.h"

Token::Token() :
  type(eof),
  line(0),
  col(0)
{}

Token::~Token() {}

Token::Token(TokenType type, int line, int colNum) :
  type(type),
  line(line),
  col(colNum)
{
}

TokenType Token::getType() const {
  return type;
}

int Token::getLine() const {
  return line;
}

int Token::getCol() const {
  return col;
}

string Token::getLex() const { return ""; }

LexicalToken::LexicalToken(TokenType typ, string* lex, int lineNu\
m, int colNum) :
   Token(typ,lineNum,colNum),
   lexeme(lex)
   {}

LexicalToken::~LexicalToken() {
   try {
      delete lexeme;
   } catch (...) {}
}

string LexicalToken::getLex() const {
  return *lexeme;
}

