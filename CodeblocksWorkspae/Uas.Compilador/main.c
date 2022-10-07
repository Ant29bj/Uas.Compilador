#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "automatas.h"
#include "modulos.h"
extern struct Nodo *raiz;

char ArregloPalRes[][19] = {"ent",         "real",    "car",     "discreto",
                            "tirarcodigo", "cuando",  "sino",    "paranga",
                            "imprimir",    "nada",    "regresa", "importa",
                            "nuevo",       "publico", "privado", "mientras",
                            "bloque",      "clase",   "mientras"};

FILE *sourcef;
char caracter;
int fila = 1;
int columna = 0;
int main() {

  sourcef =
      fopen("//home//sekai//Escritorio//programafuente//holamundo.txt", "r");
  if (sourcef == NULL) {
    printf("Archivo no encontrado\n");

  } else {
    printf("==========Contenido============\n");
    caracter = fgetc(sourcef);
    while (caracter != EOF) {

      if (caracter == '\n') {
        printf("salto de linea \n");
      } else if (isalpha(caracter)) {

        identificadores(caracter);

      } else if (isdigit(caracter) || caracter == '-' || caracter == '.') {

        numeros(caracter);

      } else if (isascii(caracter) && !isspace(caracter)) {

        caracterEspecial(caracter);
      }
      caracter = fgetc(sourcef);
    }
  }
  printf("Tipo \t Nombre\t Lexema\t Columna\t Fila\n");
  recorerNodo(raiz);
  return 0;
}
