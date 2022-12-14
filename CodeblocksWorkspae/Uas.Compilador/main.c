#include "automatas.h"
#include "modulos.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
extern struct Nodo *raiz;

char ArregloPalRes[][21] = {
    "ent",      "real",    "car",      "discreto", "tirarcodigo", "cuando",
    "sino",     "paranga", "imprimir", "nada",     "regresa",     "importa",
    "nuevo",    "publico", "privado",  "mientras", "bloque",      "clase",
    "mientras", "si",      "sino"};
FILE *sourcef;
char caracter;
int fila = 1;
int columna = 0;

struct Token comodin;
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
        columna = 0;
        fila++;
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
  
  comodin.tipo = NUM;
  comodin.Nombre = "NUMERO";
  strcpy(comodin.lexema, "Comodin");
  comodin.columna = columna;
  comodin.fila = fila;
  insertarNodo(comodin);

  recorerNodo(raiz);
  printf("Exito");
  return 0;
}
