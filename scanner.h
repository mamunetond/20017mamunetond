#pragma once

#include <iostream>
#include "token.h"

class Scanner {
public:
  Scanner(istream* in);
  ~Scanner();

  Token* getToken();
  void putBackToken();

private:
  Scanner();

  istream* inStream;
  int lineCount;
  int colCount;
  bool needToken;
  Token* lastToken;
};





