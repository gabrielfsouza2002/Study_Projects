#include <stdio.h>
#include <stdlib.h>
#include "arv.h"

void inordem (no *raiz) {

  if (raiz != NULL){

    int i;
    inordem (raiz->esq);
    printf("%s: \n", raiz->chave);

    for (i=0; i <= raiz->i; i++)
      printf("%d(%d) ", raiz->linha[i], raiz->valor[i]);

    printf("\n\n");

    inordem (raiz->dir);
  }

}