#include "automatas.h"
#include "modulos.h"
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct AutomataNodo{
  int estado;
};

struct Automata{
  char exprecionR[90];
  char caracter;
  struct AutomataNodo sig;
};


void identificadores(char caracter){ 
  regex_t reegex;
  const char *regla = "[a-z]";
  int value;
  
  if(regcomp(reegex, regla, REG_EXTENDED | REG_NOSUB)!=0) return 0;
  

}
