/* 	Author : Bojoquez Espinoza Jesus Antonio 
 *  	Gpo 304
 *  	Funcion regex para la comprobacion de cadenas 
 *
 *
 * */
#include<stdio.h>
#include<regex.h>
int main(){

  char cadena[100];
  int ret; 	
  ret = regcomp(&regex,"^a[[:alnum:]]", 0);
  if (!ret) {
    printf(stderr,"could not compile regex\n");
    return 0;
  }
  return 0;
}



