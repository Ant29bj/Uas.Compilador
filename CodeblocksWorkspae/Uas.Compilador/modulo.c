#include "modulos.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum TipoToken { PALRES, ID, NUM, CAD, CAR, SIM };

struct Token {
  enum TipoToken tipo;
  char *Nombre;
  int fila;
  int columna;
  char lexema[80];
};


struct Nodo {
  struct Token info;
  struct Nodo *izq;
  struct Nodo *der;
};

struct Nodo *raiz;
struct Nodo *actual;

struct Token newToken;

void insertarNodo(struct Token token) {
  struct Nodo *nuevo;
  nuevo = malloc(sizeof(struct Nodo));

  nuevo->info = token;
  nuevo->izq = NULL;
  nuevo->der = NULL;

  if (raiz == NULL) {
    raiz = nuevo;
    actual = nuevo;
  } else {
    nuevo->izq = actual;
    actual->der = nuevo;
    actual = nuevo;
  }
}

void recorerNodo(struct Nodo *nodo) {
  if (nodo != NULL) {
    //printf("%d\t", nodo->info.tipo);
    //printf("%s\t\t", nodo->info.Nombre);
    printf("%s\t", nodo->info.lexema);
    printf("%d\t", nodo->info.columna);
    printf("%d\t", nodo->info.fila);
    printf("\n");
    recorerNodo(nodo->der);
  }
}

void BuscarPalRes(char *t) {
  columna++;
  int longitudArreglo;
  longitudArreglo = sizeof(*ArregloPalRes) / sizeof(*ArregloPalRes[0]);
  for (int i = 0; i < longitudArreglo; i++) {
    if (strcmp(t, ArregloPalRes[i]) == 0) { // si es una palabra reservada
      // creacion del  nuevo token
      newToken.tipo = PALRES;
      newToken.Nombre = "PALRES";
      strcpy(newToken.lexema, t);
      break;
    } else {
      // en caso de ser identificadr
      newToken.tipo = ID;
      newToken.Nombre = "IDENTIFICADORES";
      strcpy(newToken.lexema, t);
    }
  }

  newToken.columna = columna;
  newToken.fila = fila;
  insertarNodo(newToken);
  memset(t, 0, sizeof(t) - 1);
}

void insertarNumero(char *string) {
  columna++;
  newToken.tipo = NUM;
  newToken.Nombre = "NUMERO";
  strcpy(newToken.lexema, string);
  newToken.columna = columna;
  newToken.fila = fila;
  insertarNodo(newToken);
}

void insertarCaracter(char *string) {
  if (string[0] == '"') {
    newToken.tipo = CAD;
    newToken.Nombre = "CADENA";
  } else {

    newToken.Nombre = "SIMBOLO";
    newToken.tipo = SIM;
  }
  columna++;
  strcpy(newToken.lexema, string);
  newToken.columna = columna;
  newToken.fila = fila;
  insertarNodo(newToken);
}
