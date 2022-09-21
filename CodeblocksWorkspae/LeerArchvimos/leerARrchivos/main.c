#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <ctype.h>

FILE *archivo;
int main()
{
  char caracter;
  archivo = fopen("main.c", "r");

  if(archivo == NULL){
    printf("Archivo no disponilbe");
  }else {
    
    printf("contenido");
    caracter = fgetc(archivo);
    while (caracter != EOF) {

      if(isalpha(caracter)){
	printf("automata de identificadores");
      }else if (isalnum(caracter)) {
	printf("llama automata de numeors");
      }else if (isascii(caracter)) {
	printf("simbolos especiales");
      }

      printf("%c\n",caracter);
      caracter = fgetc(archivo);
    }

  }
  fclose(archivo);
  return 0;
}
