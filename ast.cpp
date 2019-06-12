#include "ast.h"
#include <iostream>
#include "calculator.h"
#include <sstream>
#include <ostream>
#include <fstream>
#include <cstdlib>

// for debug information uncomment
//#define debug

AST::AST() {}

AST::~AST() {}

BinaryNode::BinaryNode(AST* left, AST* right):
   AST(),
   leftTree(left),
   rightTree(right)
{}

BinaryNode::~BinaryNode() {
#ifdef debug
   cout << "In BinaryNode destructor" << endl;
#endif

   try {
 delete leftTree;
   } catch (...) {}

   try {
      delete rightTree;
   } catch(...) {}
}

AST* BinaryNode::getLeftSubTree() const {
   return leftTree;
}

AST* BinaryNode::getRightSubTree() const {
   return rightTree;

UnaryNode::UnaryNode(AST* sub):
   AST(),
   subTree(sub)
{}

UnaryNode::~UnaryNode() {
#ifdef debug
   cout << "In UnaryNode destructor" << endl;
#endif

   try {
      delete subTree;
        } catch (...) {}
}

AST* UnaryNode::getSubTree() const {
   return subTree;
}

AddNode::AddNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int AddNode::evaluate() {
   return getLeftSubTree()->evaluate() + getRightSubTree()->evaluate();
}
string AddNode::compile() {

  string line = getLeftSubTree()->compile() + getRightSubTree()->compile();
  return line + "\n# AddNode \n"+
         "OP2 := M[SP+0] \n"+
         "OP1 := M[SP+1] \n"+
         "OP1 := OP1 + OP2 \n"+
         "SP  := SP + UNO \n"+
         "M[SP+0] := OP1 \n";
}

SubNode::SubNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int SubNode::evaluate() {
   return getLeftSubTree()->evaluate() - getRightSubTree()->evaluate();
}

string SubNode::compile() {

  string line = getLeftSubTree()->compile() + getRightSubTree()->compile();
  return line + "\n# SubNode \n"+
         "OP2 := M[SP+0] \n"+
         "OP1 := M[SP+1] \n"+
         "OP1 := OP1 - OP2 \n"+
         "SP  := SP + UNO \n"+
         "M[SP+0] := OP1 \n";

}

TimesNode::TimesNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int TimesNode::evaluate() {
   return getLeftSubTree()->evaluate() * getRightSubTree()->evaluate();
}

string TimesNode::compile() {
 string line = getLeftSubTree()->compile() + getRightSubTree()->compile();
  return line + "\n# TimesNode \n"+
         "OP2 := M[SP+0] \n"+
         "OP1 := M[SP+1] \n"+
         "OP1 := OP1 * OP2 \n"+
         "SP  := SP + UNO \n"+
         "M[SP+0] := OP1 \n";

}

DivideNode::DivideNode(AST* left, AST* right):
   BinaryNode(left,right)
{}
DivideNode::DivideNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int DivideNode::evaluate() {
   return getLeftSubTree()->evaluate() / getRightSubTree()->evaluate();
}

 string DivideNode::compile() {

  string line = getLeftSubTree()->compile() + getRightSubTree()->compile();

 return line + "\n# DivideNode \n"+
         "OP2 := M[SP+0] \n"+
         "OP1 := M[SP+1] \n"+
         "OP1 := OP1 / OP2 \n"+
         "SP  := SP + UNO \n"+
         "M[SP+0] := OP1 \n";

}

ModuleNode::ModuleNode(AST* left, AST* right):
   BinaryNode(left,right)
{}

int ModuleNode::evaluate() {

 return getLeftSubTree()->evaluate() % getRightSubTree()->evaluate();
}

string ModuleNode::compile() {

  string line = getLeftSubTree()->compile() + getRightSubTree()->compile();
  return line + "\n# ModNode \n"+
         "OP2 := M[SP+0] \n"+
         "OP1 := M[SP+1] \n"+
         "OP1 := OP1 % OP2 \n"+
         "SP  := SP + UNO \n"+
         "M[SP+0] := OP1 \n";

}
NumNode::NumNode(int n) :
   AST(),
   val(n)
{}

int NumNode::evaluate() {
   return val;
}

 string NumNode::compile() {

         string line = "";
         return line + "\n# NumNode \n"+
 "OP1 := " + to_string(val) + "\n"+
         "M[SP+0] := OP1 \n"+
         "SP  := SP - UNO \n";


}

IdNode::IdNode(std::string var) :
   AST(),
   var(var)
{}

int IdNode::evaluate() {
  if(calc->containVar(var))
   return calc->getVar(var);
  else
    calc->setVar(var, 0);
    return 0;
}

string IdNode::compile() {

  string line = "";
  evaluate();
  return line + "\n# VarNode \n"+
         "M[SP+0] := " + var + "\n"+
         "SP := SP - UNO \n";
}
RecallNode::RecallNode() :
   AST()
{}

int RecallNode::evaluate() {
  return calc->recall();
}

 string RecallNode::compile() {

  string line = "";
  return line + "\n# RecallNode \n"+
         "SP      := SP + UNO \n"+
         "M[SP+1] := MEMORY \n";
}

InitVarNode::InitVarNode(std::string var, AST* sub) : UnaryNode(sub), var(var) {}

InitVarNode::~InitVarNode() {}

int InitVarNode::evaluate(){
 calc->setVar(var, getSubTree()->evaluate());
  return calc->getVar(var);
}

 string InitVarNode::compile() {

  evaluate();
  string line = getSubTree()->compile();
  return line + "\n# AssigNode \n"+
         var + " := M[SP+1] \n";
}

StoreNode::StoreNode(AST *sub) : UnaryNode(sub) { }

StoreNode::~StoreNode() {}

int StoreNode::evaluate() {
 int result = getSubTree()->evaluate();
  calc->store(result);

}

string StoreNode::compile() {

  int result = getSubTree()->evaluate();
  calc->store(result);
  string line = getSubTree()->compile();
  return line + "\n# StoreNode \n"+
         "MEMORY := " + to_string(result) + "\n"+
         "SP      := SP+UNO \n"+
         "M[SP+1] := MEMORY \n";
}

ClearNode::ClearNode() :
   AST()
{}

ClearNode::~ClearNode() {}

int ClearNode::evaluate() {
  return calc->clear();
}

 string ClearNode::compile() {

  string line="";
  return line + "\n# CleanNode \n"+
         "SP      := SP+UNO \n"+
         "MEMORY  := CERO \n"+
         "M[SP+1] := MEMORY \n";
}

PlusNode::PlusNode(AST *sub) : UnaryNode(sub) { }
PlusNode::~PlusNode() {}

int PlusNode::evaluate() {
  calc->plus(getSubTree()->evaluate());
  return calc->recall();
}

 string PlusNode::compile() {

   string line = getSubTree()->compile();
  int result = getSubTree()->evaluate();
  calc->plus(result);
  return line + "\n# PlusNode \n"+
         "VALUE  := " + to_string(result) + "\n"
         "MEMORY := MEMORY + VALUE \n"+
         "SP      := SP+UNO \n"+
         "M[SP+0] := MEMORY \n";
}

MinusNode::MinusNode(AST *sub) : UnaryNode(sub) { }

MinusNode::~MinusNode() {}

int MinusNode::evaluate() {
  calc->minus(getSubTree()->evaluate());
  return calc->recall();
}

string MinusNode::compile() {

  string line = getSubTree()->compile();
  int result = getSubTree()->evaluate();
  calc->minus(result);
  return line + "\n# MinusNode \n"+
         "VALUE   := " + to_string(result) + "\n"
 "MEMORY  := MEMORY - VALUE \n"+
         "SP      := SP+UNO \n"+
         "M[SP+0] := MEMORY \n";
}




  



         

