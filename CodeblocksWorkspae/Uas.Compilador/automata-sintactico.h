#ifndef AUTOMATA_SINTACTICO_H_INCLUDED
#define AUTOMATA_SINTACTICO_H_INCLUDED

#include "modulos.h"

struct Nodo *gnext;

struct Nodo *empty;

int verificarExpression(struct Nodo *nodo, int estado);

int funcParametros(struct Nodo *nodo, int estado);

void verificarFuncion(struct Nodo *nodo, int estado);

void imprimir(struct Nodo *nodo, int estado);

void evalueToken(struct Nodo *nodo);

void declareVariable(struct Nodo *nodo, int estadoDeclararVariable);

void indentificadores(struct Nodo *nodo, int estado);

void autoIf(struct Nodo *nodo);

#endif
