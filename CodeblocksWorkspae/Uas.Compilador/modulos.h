#ifndef MODULOS_H_INCLUDED
#define MODULOS_H_INCLUDED

#include <stdio.h>
extern FILE *sourcef;

extern char caracter;

extern char ArregloPalRes[][19];

extern int fila;

extern int columna;

struct Token;

struct Nodo;

void insertarNodo(struct Token token);

void recorerNodo(struct Nodo *nodo);

void BuscarPalRes(char *t);

void insertarNumero(char *string);

void insertarCaracter(char *strins);

#endif // MODULOS_H_INCLUDED
