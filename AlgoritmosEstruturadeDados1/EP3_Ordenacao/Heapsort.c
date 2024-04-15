#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

int chao(double n) {
  return (int) n;
}

void sobe(int i, char** heap) {
  int j; /* índice do pai de i */
  char *temp;
  temp = malloc (10* sizeof(char)); /* variável usada na troca (swap) */

  j = chao((i-1)/2);

 /* se i tem pai e que seja maior que i */

  if(j >= 0 && (strcmp(heap[i], heap[j]) > 0)) {
   /* troca ambos */
    temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
    /* e continua subindo este elemento */
    sobe(j, heap);
  }
}

/* desce o elemento i no heap de tamanho n */
void desce(int i, char** heap, int n) {
  int j; /* índice do filho de i */
  char *temp;
  temp = malloc (10* sizeof(char)); /* variável usada na troca (swap) */

  j = 2*i + 1;

 if(j < n){ /* se i tem filhos */
    if(j < n-1) /* se i tem filho direito */
    {
     /* pega o maior filho... */
      if(strcmp(heap[j],heap[j+1])<0)
        j++;
    }
   /* ..e compara com o pai */
   
    
    if(strcmp(heap[j], heap[i]) > 0) {
      /* troca ambos (swap) */
      temp = heap[i];
      heap[i] = heap[j];
      heap[j] = temp;
      /* e continua descendo o mesmo elemento */
      desce(j, heap, n);
    }
  }
}

void constroiHeap(char** vetor, int n) {
  int i;
  for(i = chao(n/2); i >= 0; i--) {
    desce(i, vetor, n);
  }
}

/* função de ordenação */
void heapsort(char** vetor, int n) {

  int i; /* contador */
  char *temp;
  temp = malloc (10* sizeof(char)); /* usado na troca (swap) */
  int tamanhoDoHeap;

  tamanhoDoHeap = n;
  sobe(n/2, vetor);
  constroiHeap(vetor, n);
  constroiHeap(vetor, n);
 for(i = n-1; i > 0; i--) {
    /* coloca o primeiro (que é o maior, pela definição de heap)
    no final do vetor e decrementa o tamanho do heap */
    temp = vetor[i];
    vetor[i] = vetor[0];
    vetor[0] = temp;
  
    tamanhoDoHeap--;
  
    desce(0, vetor, tamanhoDoHeap);
  }
  free(temp);
}

void imprime(int n, char** vetor) {
  int i;
  printf("\n  ");
  for(i = 0; i < n; i++)
    printf("[%d] ", i);
  printf("\n  ");
  for(i = 0; i < n; i++)
    printf(" %s  ", vetor[i]);
  printf("\n");
}

int main() {
  char** heap = (char**)malloc(10*sizeof(char*));
  int n;

  n = 9;

  /* construindo um vetor desordenado */
  heap[0] = "cc";
  heap[1] = "dd";
  heap[2] = "vb";
  heap[3] = "fa";
  heap[4] = "ba";
  heap[5] = "ma";
  heap[6] = "fa";
  heap[7] = "na";
  heap[8] = "ex";



  heapsort(heap, n);
  printf("\n\n  Vetor ordenado pelo Heapsort: \n");
  imprime(n,heap);

  printf("\n\n  ");
  system("pause");
  free(heap);
  return 0; 
}

