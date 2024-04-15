#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arv.c"

no * busca (no * raiz, char * x){
  if (raiz == NULL || strcmp(raiz->chave, x) == 0)
    return raiz;
  if (strcmp(x, raiz->chave) < 0)
    return busca (raiz->esq, x);
  return busca (raiz->dir, x);
}

no * insercao (no * raiz, char * x, int valor, int linha, int i){

  if (raiz == NULL){
    raiz = malloc (sizeof(no));
    raiz->chave = malloc(strlen(x)+1);
    raiz->i = i;
    strcpy(raiz->chave,x);
    raiz->valor[i] = valor;
    raiz->linha[i] = linha;
    raiz->dir = raiz->esq = NULL;
    return raiz;
  }
  if (strcmp(x, raiz->chave) == 0){
    raiz->valor[i] = valor;
    raiz->linha[i] = linha;
  }  
  else if (strcmp(x, raiz->chave) < 0)
    raiz->esq = insercao (raiz->esq, x, valor, linha, i);
  else if (strcmp(x, raiz->chave) > 0)
    raiz->dir = insercao (raiz->dir, x, valor, linha, i);
  return raiz;
}