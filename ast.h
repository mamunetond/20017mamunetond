#pragma once

#include <string>
#include <cstdlib>

using namespace std;

class AST {
 public:
   AST();
   virtual ~AST() = 0;
   virtual int evaluate() = 0;
   virtual string compile() = 0;

};

class BinaryNode : public AST {
 public:
   BinaryNode(AST* left, AST* right);
   ~BinaryNode();

   AST* getLeftSubTree() const;
   AST* getRightSubTree() const;

 private:
   AST* leftTree;
   AST* rightTree;
};

class UnaryNode : public AST {
 public:
   UnaryNode(AST* sub);
   ~UnaryNode();

   AST* getSubTree() const;
 private:
   AST* subTree;
};

class AddNode : public BinaryNode {
 public:
   AddNode(AST* left, AST* right);

   int evaluate();
  string compile();
};

class SubNode : public BinaryNode {
 public:
   SubNode(AST* left, AST* right);

   int evaluate();
   string compile();
   };

class TimesNode : public BinaryNode {
 public:
   TimesNode(AST* left, AST* right);

   int evaluate();
   string compile();
};

class DivideNode : public BinaryNode {
 public:
   DivideNode(AST* left, AST* right);

   int evaluate();
   string compile();
};
class ModuleNode : public BinaryNode {
 public:
   ModuleNode(AST* left, AST* right);

   int evaluate();
   string compile();

};

class NumNode : public AST {

public:     //metodos
   NumNode(int n);

   int evaluate();
   string compile();

private:
  int val;

};

class IdNode : public AST {

public:
  IdNode(std::string var);

   int evaluate();
   string compile();

private:
  std::string var;

};

class RecallNode : public AST {

public:     //metodos
   RecallNode();

   int evaluate();
   string compile();

};

class InitVarNode : public UnaryNode {
public:
  InitVarNode(std::string var, AST* sub);
  ~InitVarNode();

  int evaluate();
  string compile();
   int evaluate();
  string compile();

private:
  std::string var;
};

class StoreNode : public UnaryNode {
public:
  StoreNode(AST* sub);
  ~StoreNode();

  int evaluate();
  string compile();
};

class ClearNode : public AST {

public:
   ClearNode();
  ~ClearNode();
   int evaluate();
  string compile();

};

class PlusNode : public UnaryNode {

public:
   PlusNode(AST* sub);
  ~PlusNode();

   int evaluate();
  string compile();

};

class MinusNode : public UnaryNode {
public:
   MinusNode(AST* sub);
  ~MinusNode();

   int evaluate();
  string compile();

};








