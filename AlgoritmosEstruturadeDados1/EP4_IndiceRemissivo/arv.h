#define MAXV 1000000

typedef struct cel {
  char * chave;
  int valor[MAXV];
  int linha[MAXV];
  int i;
  struct cel * esq;
  struct cel * dir; 
} no;

void inordem (no *raiz);