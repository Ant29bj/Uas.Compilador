#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>
#include "modulos.h"
#include "automatas.h"

FILE *sourcef;
int main()
{
    char caracter;
    sourcef = fopen("//home//sekai//Escritorio//programafuente//holamundo.txt","r");
    if(sourcef == NULL){
      printf("Archivo no encontrado\n");
    }else {
      printf("==========Contendio============\n");
      caracter = fgetc(sourcef);
      while (caracter != EOF) {

        if (isalpha(caracter)) {
	  identificadores(caracter); 
        }else if (isalnum(caracter)) {
	  printf("automate de numeros\n");
        }else if (isascii(caracter)) {
	  printf("automata de caracteres\n");
        }
	caracter = fgetc(sourcef); 
      }

    }

    return 0;
}
