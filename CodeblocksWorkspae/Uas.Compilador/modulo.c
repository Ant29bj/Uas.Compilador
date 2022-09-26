#include "modulos.h"
#include <stdlib.h>
#include <stdio.h>

enum TipoToken{
  ID,
  PALRES,
  NUM,
  CAD
};


struct Token{
  enum TipoToken tipo; 
  char lexema[80];
};

struct Nodo{
  struct Token info;
  struct Nodo *izq;
  struct Nodo *der;
};


struct Nodo *raiz;
struct Nodo *actual;

void insertarNodo(struct Token token){
  struct Nodo *nuevo;
  nuevo  = malloc(sizeof(struct Nodo));

  nuevo->info = token;
  nuevo->izq = NULL;
  nuevo->der = NULL;

  if(raiz == NULL){
    raiz = nuevo;
    actual = nuevo;
  }else {
    nuevo->izq=actual;
  }
}

void recorerNodo(struct Nodo *nodo){
  while (nodo != NULL) {
    printf("Nombre: %d\n", nodo->info.tipo);
    printf("Tipo: %s\n",nodo->info.lexema); 
    recorerNodo(nodo->der); 
  }   

}


