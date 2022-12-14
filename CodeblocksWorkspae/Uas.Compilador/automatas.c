#include "automatas.h"
#include "modulos.h"

#include <ctype.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void saltarGuardar(char *string, char cad) {
  strncat(string, &cad, 1);
  cad = fgetc(sourcef);
}

void identificadores(char c) {

  int estado = 1;
  char cadena[50];
  memset(cadena, 0, sizeof(cadena) - 1);
  while (estado == 1 || estado == 2) {
    switch (estado) {
    case 1:
      if (isalnum(c)) {
        strncat(cadena, &c, 1);
        c = fgetc(sourcef);
        estado = 2;
      }
      break;
    case 2:
      if (isalnum(c) || c == '_') {
        strncat(cadena, &c, 1);
        c = fgetc(sourcef);
      } else {
        estado = 3;
      }
      break;
    }
  }
  if (estado == 3) {
    BuscarPalRes(cadena);
    memset(cadena, 0, sizeof(cadena));
  }

  if (c == ';' || c == '(' || c == ')' || c == '{' || c == '}' || c == '[' ||
      c == ']' || c == ',') {

    caracterEspecial(c);

  } else if (isascii(c) && !isspace(c)) {

    printf("Error: invalid %c", c);
    exit(1);
  }
}

void numeros(char c) {

  int estado = 1;
  char numero[999];
  memset(numero, 0, sizeof(numero) - 1);

  while (estado < 6) {
    switch (estado) {
    case 1:
      if (c == '-' || c == '.') {
        strncat(numero, &c, 1);
        c = fgetc(sourcef);
        estado = 2;
      } else if (isdigit(c)) {

        strncat(numero, &c, 1);
        c = fgetc(sourcef);
        estado = 3;
      }
      break;
    case 2:
      if (c == '.') {
        strncat(numero, &c, 1);
        c = fgetc(sourcef);
        estado = 4;
      } else if (isspace(c)) {
        estado = 8;
      } else if (isdigit(c)) {
        strncat(numero, &c, 1);
        c = fgetc(sourcef);
        estado = 3;
      }
      break;
    case 3:
      if (isdigit(c)) {
        strncat(numero, &c, 1);
        c = fgetc(sourcef);
      } else if (c == '.') {
        strncat(numero, &c, 1);
        c = fgetc(sourcef);
      } else {
        estado = 6;
      }
      break;
    case 4:
      if (isdigit(c)) {
        strncat(numero, &c, 1);
        c = fgetc(sourcef);
        estado = 5;
      }
      if (!isdigit(c)) {
        printf("Entre \n");
        estado = 5;
      }
      break;
    case 5:
      if (isdigit(c)) {
        strncat(numero, &c, 1);
        c = fgetc(sourcef);
      } else {
        estado = 6;
      }
      break;
    }
  }

  if (estado == 6) {
    insertarNumero(numero);
    memset(numero, 0, sizeof(numero) - 1);
  }

  if (estado == 8) {
    insertarCaracter(numero);
    memset(numero, 0, sizeof(numero) - 1);
  }

  if (isascii(c) && !isspace(c)) {
    caracterEspecial(c);
  }
}

void caracterEspecial(char c) {
  int estado = 1;
  char operadores[1000];
  memset(operadores, 0, sizeof(operadores) - 1);
  while (estado < 7) {
    switch (estado) {
    case 1:
      if (c == '+' || c == '-' || c == '*' || c == '/' || c == ';' ||
          c == ':') {
        saltarGuardar(operadores, c);
        estado = 7;
      } else if (c == '!' || c == '<' || c == '>' || c == '=') {
        strncat(operadores, &c, 1);
        c = fgetc(sourcef);
        estado = 4;
      } else if (c == '&' || c == '|') {
        saltarGuardar(operadores, c);
        estado = 5;
      } else if (c == '(' || c == ')' || c == '{' || c == '}' || c == '[' ||
                 c == ']') {
        strncat(operadores, &c, 1);
        estado = 7;
      } else if (c == '"') {
        strncat(operadores, &c, 1);
        c = fgetc(sourcef);
        estado = 6;
      } else if (isascii(c)) {
        saltarGuardar(operadores, c);
        estado = 7;
      } else {
        estado = 7;
      }
      break;
    case 4:
      if (c == '!' || c == '<' || c == '>' || c == '=') {
        saltarGuardar(operadores, c);
        estado = 7;
      } else {
        estado = 7;
      }
      break;
    case 5:
      if (c == '&' && c == '|') {
        strncat(operadores, &c, 1);
        estado = 7;
      }
      break;
    case 6:
      if (c != '"' && c != '\n') {
        strncat(operadores, &c, 1);
        c = fgetc(sourcef);
      } else if (c == '"') {
        strncat(operadores, &c, 1);
        estado = 7;
      } else if (c == '\n') {
        printf("Error: missing element ");
        exit(1);
      }
      break;
    }
  }

  if (estado == 7) {
    insertarCaracter(operadores);
    memset(operadores, 0, sizeof(operadores) - 1);
  }
}
