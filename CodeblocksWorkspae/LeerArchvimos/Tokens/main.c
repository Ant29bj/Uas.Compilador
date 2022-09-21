#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

enum TipoToken{
  PalRes,
  id,
  num,
  sum
};

struct Token{
  enum TipoToken tipo;
  char lexema[80];
};

struct nodo{
  struct Token info;
  struct nodo *izq;
  struct nodo *der;
};

struct nodo *raiz;
struct nodo *acutal;

void insertar(struct Token token){
  struct nodo *nuevo;
  nuevo  = malloc(sizeof(struct nodo));

  nuevo->info = token;
  nuevo->izq = NULL;
  nuevo->der = NULL;

  if(raiz == NULL){
    raiz = nuevo;
    acutal = nuevo;
  }else {
    nuevo->izq=acutal;
    acutal->der=nuevo;
    acutal=nuevo;
  } 
}

void imprimirLista(struct nodo *reco){
  struct nodo *aux;
  aux = raiz;
    while (aux != NULL) {
      printf("\n",aux->info.tipo);
      printf("\n",aux->info.lexema);
      aux = aux->der;
    }
}

int main()
{
    raiz = NULL;
    acutal = NULL;

    struct Token token;
    token.tipo = PalRes;
    strcpy(token.lexema,"(");
    insertar(token);

    token.tipo = id;
    strcpy(token.lexema, "a");
    insertar(token);

    token.tipo=PalRes;
    strcpy(token.lexema, ")");
    insertar(token);

    imprimirLista(raiz);

    return 0;
}
