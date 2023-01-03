#include "automata-sintactico.h"
#include "modulos.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

extern struct Nodo *gnext;

void buscarLlave(struct Nodo *nodo) {
  if (strcmp(nodo->info.lexema, "}") != 0 && strcmp(nodo->info.lexema, "Comodin") != 0) {
    buscarLlave(nodo->der);
  } else if (!strcmp(nodo->info.lexema, "}")) {
    strcat(nodo->info.lexema, "|");
  } else if (!strcmp(nodo->info.lexema, "Comodin")) {
    printf("Error en fila %d ", nodo->info.fila);
    printf("columna %d ", nodo->info.columna);
  }
}

void evalueToken(struct Nodo *nodo) {
  printf("entro con %s\n",nodo->info.lexema);
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
    } else if (!strcmp(nodo->info.lexema, "si")) {
      printf("entro\n");
      autoIf(nodo->der, 0);
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
    printf("Error en fila %d ", nodo->info.fila);
    printf("columna %d ", nodo->info.columna);
    printf("en %s\n", nodo->info.lexema);
    gnext = empty;
    gnext = nodo->der;
  }
}

void verificarFuncion(struct Nodo *nodo, int estado) {
  if (nodo != NULL) {
    switch (estado) {
    case 0:
      if (!strcmp(nodo->info.lexema, "(")) {
        verificarFuncion(nodo->der, 1);
      } else {
        printf("Error en fila %d ", nodo->info.fila);
        printf("columna %d ", nodo->info.columna);
        printf("en %s\n", nodo->info.lexema);
        gnext = empty;
        gnext = nodo->der;
      }
      break;
    case 1:
      if (!strcmp(nodo->info.lexema, ")")) {
        verificarFuncion(nodo->der, 2);
      } else {
        printf("Error en fila %d ", nodo->info.fila);
        printf("columna %d ", nodo->info.columna);
        printf("en %s\n", nodo->info.lexema);
        gnext = empty;
        gnext = nodo->der;
      }
      break;
    case 2:
      if (!strcmp(nodo->info.lexema, "{")) {
        buscarLlave(nodo);
        verificarFuncion(nodo->der, 3);
      } else {
        printf("Error en fila %d ", nodo->info.fila);
        printf("columna %d ", nodo->info.columna);
        printf("en %s\n", nodo->info.lexema);
        gnext = empty;
        gnext = nodo->der;
      }
      break;
    case 3:
      if (strcmp(gnext->info.lexema, "}|")) {
        evalueToken(nodo);
        verificarFuncion(gnext, 3);
      } else if (!strcmp(nodo->info.lexema, "}|")) {
        gnext = empty;
        gnext = nodo->der;
      }
      break;
    default:
      break;
    }
  }
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
        printf("Error en fila %d ", nodo->info.fila);
        printf("columna %d ", nodo->info.columna);
        printf("en %s\n", nodo->info.lexema);
        gnext = empty;
        gnext = nodo->der;
      }
      break;
    case 1:
      if (nodo->info.lexema[0] == ';') {
        gnext = empty;
        gnext = nodo->der;
      } else if (nodo->info.lexema[0] == ',') {
        declareVariable(nodo->der, 0);
      } else {
        printf("Error en fila %d ", nodo->info.fila);
        printf("columna %d ", nodo->info.columna);
        printf("en %s\n", nodo->info.lexema);
        gnext = empty;
        gnext = nodo->der;
      }
      break;
    default:
      break;
    }
  }
}

/*
 *
 * [si](<Expresion>){}
 * */
void autoIf(struct Nodo *nodo, int estado) {
  if (nodo != NULL) {
    switch (estado) {
    case 0:
      if (nodo->info.lexema[0] == '(') {
        autoIf(nodo->der, 1);
      } else {
        printf("Error en fila %d ", nodo->info.fila);
        printf("columna %d ", nodo->info.columna);
        printf("en %s\n", nodo->info.lexema);
        gnext = empty;
        gnext = nodo->der;
      }
      break;
    case 1:
      if (verificarExpression(nodo, 0)) {
        autoIf(gnext, 2);
      } else {
        printf("Error en fila %d ", nodo->info.fila);
        printf("columna %d ", nodo->info.columna);
        printf("en %s\n", nodo->info.lexema);
        gnext = empty;
        gnext = nodo->der;
      }
      break;
    case 2:
      if (nodo->info.lexema[0] == ')') {
        autoIf(nodo->der, 3);
      } else {
        printf("Error en fila %d ", nodo->info.fila);
        printf("columna %d ", nodo->info.columna);
        printf("en %s\n", nodo->info.lexema);
        gnext = empty;
        gnext = nodo->der;
      }
      break;
    case 3:
      if (nodo->info.lexema[0] == '{') {
        buscarLlave(nodo);
        autoIf(nodo->der, 4);
      } else {
        printf("Error en fila %d ", nodo->info.fila);
        printf("columna %d ", nodo->info.columna);
        printf("en %s\n", nodo->info.lexema);
        gnext = empty;
        gnext = nodo->der;
      }
    case 4:
      if (strcmp(nodo->info.lexema, "}|") != 0) {
        evalueToken(nodo);
        autoIf(gnext, 4);
      } else if (strcmp(nodo->info.lexema, "}|") == 0) {
        gnext = empty;
        gnext = nodo->der;
      }
      break;
    default:
      break;
    }
  }
}

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
      } else if (nodo->info.tipo == 1 || nodo->info.tipo == 2 ||
                 nodo->info.tipo == 3) {
        indentificadores(nodo->der, 2);
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
        printf("Error en fila %d ", nodo->info.fila);
        printf("columna %d ", nodo->info.columna);
        printf("en %s\n", nodo->info.lexema);
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
      gnext = empty;
      gnext = nodo->der;
    }
    break;
  case 1:
    if (nodo->info.tipo == 5 && nodo->info.lexema[0] != ';') {
      verificarExpression(nodo->der, 2);
    } else if (nodo->info.lexema[0] == ';') {
      gnext = empty;
      gnext = nodo;
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
      printf("Error en fila %d ", nodo->info.fila);
      printf("columna %d ", nodo->info.columna);
      printf("en %s\n", nodo->info.lexema);
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
        printf("Error en fila %d ", nodo->info.fila);
        printf("columna %d ", nodo->info.columna);
        printf("en %s\n", nodo->info.lexema);
        gnext = empty;
        gnext = nodo->der;
      }
      break;
    case 1:
      if (nodo->info.tipo == 3) {
        imprimir(nodo->der, 2);
      } else {
        printf("Error en fila %d ", nodo->info.fila);
        printf("columna %d ", nodo->info.columna);
        printf("en %s\n", nodo->info.lexema);
        gnext = empty;
        gnext = nodo->der;
      }
      break;
    case 2:
      if (nodo->info.lexema[0] == ')') {
        imprimir(nodo->der, 3);
      } else {
        printf("Error en fila %d ", nodo->info.fila);
        printf("columna %d ", nodo->info.columna);
        printf("en %s\n", nodo->info.lexema);
        gnext = empty;
        gnext = nodo->der;
      }
      break;
    case 3:
      if (nodo->info.lexema[0] == ';') {
        gnext = empty;
        gnext = nodo->der;
      } else {
        printf("Error en fila %d ", nodo->info.fila);
        printf("columna %d ", nodo->info.columna);
        printf("en %s\n", nodo->info.lexema);
        gnext = empty;
        gnext = nodo->der;
      }
      break;
    default:

      break;
    }
  }
}
