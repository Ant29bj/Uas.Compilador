#include "automata-sintactico.h"
#include "modulos.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

extern struct Nodo *gnext;
void evalueToken(struct Nodo *nodo) {

  if (!strcmp(nodo->info.lexema, "Comodin")) {
    printf("Compilacion Terminada\n");
    gnext = empty;
    gnext = nodo->der;
  } else if (nodo->info.tipo == 0) {
    if (!strcasecmp(nodo->info.lexema, "ent") ||
        !strcasecmp(nodo->info.lexema, "real") ||
        !strcasecmp(nodo->info.lexema, "car") ||
        !strcasecmp(nodo->info.lexema, "discreto")) {
      declareVariable(nodo->der, 0);
    } else if (!strcasecmp(nodo->info.lexema, "tirarcodigo")) {
      verificarFuncion(nodo->der, 0);
    } else if (!strcasecmp(nodo->info.lexema, "imprimir")) {
      imprimir(nodo->der, 0);
    } else {
      printf("entro con %s\n", nodo->info.lexema);
      exit(1);
    }
  } else if (nodo->info.tipo == 1) {
    indentificadores(nodo->der, 0);
  } else {
    printf("Error en fila %d", nodo->info.fila);
    printf(" columna %d\n", nodo->info.columna);
    gnext = empty;
    gnext = nodo->der;
  }
}

void verificarFuncion(struct Nodo *nodo, int estado) {
  if (nodo != NULL) {
    switch (estado) {
    case 0:
      if (nodo->info.lexema[0] == '(') {
        verificarFuncion(nodo->der, 1);
      } else {
        printf("error on fila %d", nodo->info.fila);
        printf(" columna %d\n", nodo->info.columna);
      }
      break;
    case 1:
      if (nodo->info.lexema[0] == ')') {
        verificarFuncion(nodo->der, 2);
      } else {
        printf("error on fila %d", nodo->info.fila);
        printf(" columna %d\n", nodo->info.columna);
      }
      break;
    case 2:
      if (nodo->info.lexema[0] == '{') {
        evalueToken(nodo->der);
        verificarFuncion(gnext, 3);
      } else {
        printf("error on fila %d", nodo->info.fila);
        printf(" columna %d\n", nodo->info.columna);
      }
      break;
    case 3:
      if (nodo->info.lexema[0] == '}') {
        gnext = empty;
        gnext = nodo->der;
      } else {
        printf("error on fila %d", nodo->info.fila);
        printf(" columna %d\n", nodo->info.columna);
      }
      break;
    default:

      break;
    }
  }
}
int funcParametros(struct Nodo *nodo, int estado) {
  printf("entro con %s\n", nodo->info.lexema);
  if (nodo != NULL) {
    switch (estado) {
    case 0:
      if (nodo->info.tipo == 1) {
        funcParametros(nodo->der, 1);
      } else {
        printf("error on fila %d", nodo->info.fila);
        printf(" columna %d\n", nodo->info.columna);
      }
      break;
    case 1:
      if (nodo->info.lexema[0] == ')') {
        gnext = empty;
        gnext = nodo->der;
      } else if (nodo->info.lexema[0] == ',') {
        funcParametros(nodo->der, 0);
      } else {
        printf("error on fila %d", nodo->info.fila);
        printf(" columna %d\n", nodo->info.columna);
      }
      break;
    default:
      break;
    }
  }
  return 0;
}

// Declaracion de Variables del tipo [tipo variable] <Nombre variable> ||
// <Coma><Nombre Variable> || Terminal
void declareVariable(struct Nodo *nodo, int estadoDeclararVariable) {
  struct Nodo *auxiliar;
  if (nodo != NULL) {
    switch (estadoDeclararVariable) {
    case 0:
      if (nodo->info.tipo == 1) {
        declareVariable(nodo->der, 1);
      } else {
        printf("error on fila %d", nodo->info.fila);
        printf(" columna %d\n", nodo->info.columna);
      }
      break;
    case 1:
      if (nodo->info.lexema[0] == ';') {
        gnext = empty;
        gnext = nodo->der;
      } else if (nodo->info.lexema[0] == ',') {
        declareVariable(nodo->der, 0);
      } else {
        printf("error on fila %d", nodo->info.fila);
        printf(" columna %d\n", nodo->info.columna);
      }
      break;
    default:
      break;
    }
  }
}
void autoIf(struct Nodo *nodo) {}

/*
 * [Identificador] || = <Expresion> Terminal || ( <Expresion> ) || () ||
 * Terminal
 */
void indentificadores(struct Nodo *nodo, int estado) {
  if (nodo != NULL) {
    switch (estado) {
    case 0:
      if (nodo->info.lexema[0] == '=') {
        indentificadores(nodo->der, 1);
      } else {
        printf("Error en fila %d", nodo->info.fila);
        printf(" columna en %d \n", nodo->info.columna);
        gnext = empty;
        gnext = nodo->der;
      }
      break;
    case 1:
      if (verificarExpression(nodo, 0)) {
        indentificadores(gnext, 2);
      } else {
        printf("Error en fila %d", nodo->info.fila);
        printf(" columna en %d", nodo->info.columna);
        gnext = empty;
        gnext = nodo->der;
      }
      break;
    case 2:
      if (nodo->info.lexema[0] == ';') {
        gnext = empty;
        gnext = nodo->der;
      } else {
        printf("Error en fila %d", nodo->info.fila);
        printf(" columna en %d \n", nodo->info.columna);
        gnext = empty;
        gnext = nodo->der;
      }
      break;
    default:

      break;
    }
  }
}

int verificarExpression(struct Nodo *nodo, int estado) {
  int resultado;
  switch (estado) {
  case 0:
    if (nodo->info.tipo == 1 || nodo->info.tipo == 2) {
      verificarExpression(nodo->der, 1);
    } else {
      resultado = 0;
      printf("Error en fila %d", nodo->info.fila);
      printf(" columna %d\n", nodo->info.columna);
    }
    break;
  case 1:
    if (nodo->info.tipo == 5) {
      verificarExpression(nodo->der, 2);
    } else {
      resultado = 0;
      printf("Error en fila %d", nodo->info.fila);
      printf(" columna %d\n", nodo->info.columna);
      gnext = empty;
      gnext = nodo->der;
    }
    break;
  case 2:
    if (nodo->info.tipo == 1 || nodo->info.tipo == 2) {
      gnext = empty;
      gnext = nodo->der;
      resultado = 1;
    } else {
      printf("Error en fila %d", nodo->info.fila);
      printf(" columna %d\n", nodo->info.columna);
      gnext = empty;
      gnext = nodo->der;
    }
    break;
  default:

    break;
  }
  return resultado;
}

void imprimir(struct Nodo *nodo, int estado) {
  if (nodo != NULL) {
    switch (estado) {
    case 0:
      if (nodo->info.lexema[0] == '(') {
        imprimir(nodo->der, 1);
      } else {
        printf("Error en fila %d", nodo->info.fila);
        printf(" columna %d\n", nodo->info.columna);
        gnext = empty;
        gnext = nodo->der;
      }
      break;
    case 1:
      if (nodo->info.tipo == 3) {
        imprimir(nodo->der, 2);
      } else {
        printf("Error en fila %d", nodo->info.fila);
        printf(" columna %d\n", nodo->info.columna);
        gnext = empty;
        gnext = nodo->der;
      }
      break;
    case 2:
      if (nodo->info.lexema[0] == ')') {
        imprimir(nodo->der, 3);
      } else {
        printf("Error en fila %d", nodo->info.fila);
        printf(" columna %d\n", nodo->info.columna);
        gnext = empty;
        gnext = nodo->der;
      }
      break;
    case 3:
      if (nodo->info.lexema[0] == ';') {
        gnext = empty;
        gnext = nodo->der;
      } else {
        printf("Error en fila %d", nodo->info.fila);
        printf(" columna %d\n", nodo->info.columna);
        gnext = empty;
        gnext = nodo->der;
      }
      break;
    default:

      break;
    }
  }
}
