#include "parser.h"
#include "calcex.h"
#include <string>
#include <sstream>

Parser::Parser(istream* in) {
   scan = new Scanner(in);
}

Parser::~Parser() {
   try {
      delete scan;
   } catch (...) {}
}

AST* Parser::parse() {
   return prog();
}

AST* Parser::prog() {

   AST* result = expr();
   Token* t = scan->getToken();

   if (t->getType() != eof) {
     cout << "* parser error" << endl;
     throw ParseError;
   }

   return result;

}

AST* Parser::expr() {
   return restExpr(term());
}

AST* Parser::restExpr(AST* e) {
  Token* t = scan->getToken();

  if (t->getType() == add) {
      return restExpr(new AddNode(e,term()));
   }
    if (t->getType() == sub)
      return restExpr(new SubNode(e,term()));

   scan->putBackToken();

   return e;
}

AST* Parser::term() {
  return restTerm(storable());
}

AST* Parser::restTerm(AST* e) {
    Token* t = scan->getToken();

   AST* result = nullptr;

   switch(t->getType()) {
   case times:
     result = restTerm(new TimesNode(e, storable()));
     break;
     
       case divide:
     result = restTerm(new DivideNode(e, storable()));
     break;

   case module:
     result = restTerm(new ModuleNode(e, storable()));
     break;

   default:
     scan->putBackToken();
     result = e;
     break;
   }

   return result;
}

AST* Parser::storable() {
  return memOperation(factor());
}

AST* Parser::memOperation(AST* e) {

  AST* result = e;

    Token *t = scan->getToken();

  if (t->getType() == keyword){
    if(t->getLex() == "S") {
      return new StoreNode(result);
    }
    else if(t->getLex() == "P") {
      return new PlusNode(result);
    }
    else if(t->getLex() == "M") {
      return new MinusNode(result);
    }
    else {
      cout << "* parse error" << endl;
      throw ParseError;
    }
  }
   else {
    scan->putBackToken();
  }

  return result;

}

AST* Parser::factor() {

  AST* result;
  Token* t = scan->getToken();

   if (t->getType() == number) {
      istringstream in(t->getLex());
      int val;
      in >> val;
      return new NumNode(val);
   }

   if (t->getType() == identifier) {
      istringstream in(t->getLex());
       string val;
      in >> val;
      return new IdNode(val);
   }

   if (t->getType() == keyword){
    if(t->getLex() == "-v") {
      return InitVar();
     }
    else if(t->getLex() == "R") {
      return new RecallNode();
    }
    else if(t->getLex() == "C") {
      return new ClearNode();
    }
    else {
      cout << "* Parse error" << endl;
      throw ParseError;
    }
  }

   if (t->getType() == lparen) {
    AST *result = expr();
     t = scan->getToken();
     if (t->getType() != rparen) {
       cout << "* Parse error" << endl;
       throw ParseError;
     }
     return result;
   }

   cerr << "* Parse error" << endl;
   throw ParseError;
}

AST* Parser::InitVar() {
  Token* t = scan->getToken();

  if(t->getType() == identifier) {
    Token* to = scan->getToken();

    if(to->getType() == equals)
      return new InitVarNode(t->getLex(), expr());
  }
  cout << "* parser error" << endl;
  throw ParseError;
}











