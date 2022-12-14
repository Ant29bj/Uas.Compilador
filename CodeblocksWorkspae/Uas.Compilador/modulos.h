#ifndef MODULOS_H_INCLUDED
#define MODULOS_H_INCLUDED

#include <stdio.h>
extern FILE *sourcef;

extern char caracter;

extern char ArregloPalRes[][21];

extern int fila;

extern int columna;

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

void insertarNodo(struct Token token);

void recorerNodo(struct Nodo *nodo);

void BuscarPalRes(char *t);

void insertarNumero(char *string);

void insertarCaracter(char *strins);

#endif // MODULOS_H_INCLUDED
