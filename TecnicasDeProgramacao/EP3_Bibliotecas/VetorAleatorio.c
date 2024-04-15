#include <stdlib.h>
#include <stdio.h>
#include "VetorAleatorio.h"

long long * criaVetorAleatorio(int semente, int tamanho){

    long long *vetor = (long long*)malloc(sizeof(long)*tamanho);
    int i;

    srand(semente);
    for(i=0 ; i <= tamanho ; i++)
        vetor[i] = rand();
    return vetor;
}

