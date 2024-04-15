#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Palavra
{
  char *p;
}PALAVRA;

void merge(char** v, char** c, int i, int m, int f) {
  int z,
  iv = i, ic = m + 1;
  for (z = i; z <= f; z++) 
    c[z] = v[z];
  z = i;
  while (iv <= m && ic <= f) {

  if (strcmp(c[iv],c[ic]) <= 0 )
    v[z++] = c[iv++];
  else 
    v[z++] = c[ic++];
  }
  while (iv <= m) 
    v[z++] = c[iv++];
  while (ic <= f) 
    v[z++] = c[ic++];
}

void sort(char** v, char** c, int i, int f) {
  if (i >= f) 
    return;
  int m = (i + f) / 2;
  sort(v, c, i, m);
  sort(v, c, m + 1, f);

  if (strcmp(v[m],v[m + 1]) <=0) 
    return;

  merge(v, c, i, m, f);
}

void mergesort(char** v, int n) {
  char** c = (char**)malloc(100000000*sizeof(char*));
  sort(v, c, 0, n - 1);
}

int main (void) {

  char** matrix = (char**)malloc(10000000*sizeof(char));
  char *aux = malloc(100000000*sizeof(const char));
  char aux2[100];
  
 
  int i = 0;
  int cont = 0;

  char url[]="arquivo.txt";
  FILE *arq;
  arq = fopen(url, "r");
  
  if(arq == NULL)
    printf("Erro, nao foi possivel abrir o arquivo\n");
  else{
    for(cont=0; fscanf(arq,"%c", matrix[cont])!= EOF ;cont++,i++){ //fscanf

  
    printf("%c ", matrix[cont-1]);
    printf("%s ", matrix[0]);
    
    }
} fclose(arq);
  mergesort(matrix, cont);
  for (i = 0; i < cont; i++) 
    printf("%s ", matrix[i]);

  putchar('\n');

    return 0;
}