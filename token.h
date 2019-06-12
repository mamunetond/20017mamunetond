#pragma once

#include <string>
using namespace std;

enum TokenType {
                identifier,keyword,number,add,sub,times,divide,lp\
aren,rparen,module,eol,eof,unrecognized,equals
};

class Token {
public:

  Token();
  Token(TokenType typ, int line, int col);
  virtual ~Token();

  TokenType getType() const;
  int getLine() const;
  int getCol() const;
  virtual string getLex() const;

private:
  TokenType type;
  int line,col;
};

class LexicalToken : public Token {
 public:
   LexicalToken(TokenType typ, string* lex, int line, int col);
   ~LexicalToken();

   virtual string getLex() const;

 private:
TokenType type;
  int line,col;
};

class LexicalToken : public Token {
 public:
   LexicalToken(TokenType typ, string* lex, int line, int col);
   ~LexicalToken();

   virtual string getLex() const;

 private:
   string* lexeme;
};
