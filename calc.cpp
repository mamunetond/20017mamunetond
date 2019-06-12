#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "calcex.h"
#include "calculator.h"


using namespace std;

Calculator* calc;

void detectarComando(int, char**);
bool noInteractivo(int, char**);
string getText(string,string);
bool c(int, char**);
void compiler();
void noCompiler(ifstream&);




int main(int argc, char* argv[]) {

   string line;
   string cadena;
   ifstream file;

   calc = new Calculator();


   detectarComando(argc, argv);


   if(noInteractivo(argc, argv))
   {
       bool fail = false;

       for(int i = 1; i < argc; i++)
        {
           fail = false;
           cadena = argv[i];

           if(cadena.size() > 4 and cadena.substr(cadena.size()-5, cadena.size()) == ".calc")
             {
                file.open(argv[i], ios::in);


              if(file.fail())
                {
                  cout << "Error en el momento de leer el archivo " << argv[i] << endl;
                  fail = true;
                 }


              if(c(argc,argv) and !fail)
                {
                  compiler();
                }else
                {
                  if(!fail){
                   
                  cout << "Error en el momento de leer el archivo " << argv[i] << endl;
                  fail = true;
                 }


              if(c(argc,argv) and !fail)
                {
                  compiler();
                }else
                {
                  if(!fail){

                      noCompiler(file);
                  }
                }
                  file.close();
                }

           }

   }else {
     if(c(argc,argv))
       {
         compiler();
       }


  while(true){
   try {

      cout << "> ";

      getline(cin, line);
 if(!cin) break;

        int result = calc->eval(line);

        cout << "= "  << result << endl;

   }
   catch(Exception e) {

   }
  }
  delete calc;

       }
}


void detectarComando(int argc, char* argv[]) {

  int valor;
  string val;
   string var;
  bool b = false;

  for(int i = 1; i<argc; i++)
    {
      if(strncmp(argv[i], "-v", 2) == 0)
        {
          b = true;
          string cadena = argv[i+1];
          int indice = cadena.find_first_of('=');
          var = cadena.substr(0, indice);
          val = cadena.substr(indice+1);
          calc->setVar(var, stoi(val));

        }
    }

}


void noCompiler(ifstream &archivo) {
  string line;
 while(!archivo.eof()){
    try {
      getline(archivo, line);
      int result = calc->eval(line);

      cout << "= " << result << endl;

    }catch(Exception e) {

    }
  }
}


bool noInteractivo(int argc, char** argv)
{
  string cadena;
  for(int i=1; i<argc; i++){
    cadena = argv[i];
    if(cadena.size()>4 and cadena.substr(cadena.size()-5, cadena.size())==".calc"){
      return true;
    }
  }

  return false;
}

bool c(int argc, char** argv)
{
  for(int i = 1; i < argc; i++)
    {
      if(strncmp(argv[i], "-c",2) == 0)
        {
          return true;
        }
    }

    return false;
}

void compiler()
{

  string ContadorLinea;
ofstream filePrint;
  string temp;
  string line;
  string line2;

  while(true)
    {
      try
        {
          cout << ">";
          getline(cin, line);
          if(!cin) break;
          line2 = line;

          string printer = temp +
            "\n# Imprime resultado \n" +
            "OP1 := M[SP + 0] \n"
            "SP  := SP - UNO \n"+
            "writeInt(OP1)";

          ContadorLinea = ContadorLinea + calc->comp(line) + printer;
        }
catch(Exception e)
        {
          cout << "Se produjo un error";
        }

}

  filePrint.open("a.ewe", ios::out);
  if(filePrint.fail())
    {
      cout << "Se produjo un error";
    }
  filePrint << getText(ContadorLinea, line);
  filePrint.close();
}


string getText(string lineOut, string line)
{
  string temp = "";
  string encabezado = temp + "\n# Expresion"
 + line +
"\nstart:"
 + "\n# Instrucciones antes del recorrido del arbol abstracto sintactico \n"+
    "SP     := 1000 \n"+
    "UNO    := 1 \n"+
    "CERO   := 0 \n"+
    "MEMORY := CERO";

  string encabezado2 = temp + "\n# Comienza el recorrido del arbol\n";

  string endArchivo = temp +

    "\nend: halt"
    "\nequ MEMORY M[0] \n"+
    "equ UNO    M[1] \n"+
    "equ CERO   M[2] \n"+
    "equ OP1    M[3] \n"+
    "equ OP2    M[4] \n"+
    "equ SP     M[5] \n"+
    "equ STACK  M[1000] \n"+
    calc->palabrasClaves();

  return encabezado +  encabezado2  + lineOut + endArchivo;
}


