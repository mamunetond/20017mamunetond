#pragma once

#include <map>
#include <string>

using namespace std;


class Calculator {
 public:
   Calculator();


   string comp(string expr);
   int eval(string expr);
   void store(int val);
   int recall();
   int clear();
   void plus(int val);
   void minus(int val);
   void setVar(string var, int val);
   int getVar(string var);
   bool containVar(string var);
   string palabrasClaves();



 private:
   int memory;
   map <string, int> variables;
};

extern Calculator* calc;

