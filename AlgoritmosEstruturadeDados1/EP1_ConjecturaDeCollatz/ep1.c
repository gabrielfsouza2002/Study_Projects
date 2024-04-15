#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* #include <time.h> */

/*NOME: GABRIEL FERREIRA DE SOUZA ARAUJO. NUSP: 12718100 */

void Collatz_pot_d_2(int inicio, int fim){

    int n,n_passos,aux;

    for(; inicio<=fim; inicio++){
        n = inicio;
        for(n_passos = 0; n != 1; n_passos++){
            aux = n;
            /* Verifica se o numero é potencia de 2. Se sim, converge para 1*/
            while(aux != 1 && aux%2 == 0){
                aux = aux/2;
            }
            if (n==1||aux == 1 ){
                n = 1;
            }
            else if (n%2 == 0){
                n = n/2;
            }
            else if (n%2 != 0){
                n = 3*n+1;
            }
        }
        printf("\n");
        printf("Para n = %d foram necessarios %d passos",inicio,n_passos);
    }

}

void Collatz(int inicio, int fim){

    int n,n_passos;

    for(; inicio<=fim; inicio++){
        n = inicio;
        for(n_passos = 0; n != 1; n_passos++){

            if (n==1){
                n = 1;
            }
            else if (n%2 == 0){
                n = n/2;
            }
            else if (n%2 != 0){
                n = 3*n+1;
            }
        }
        printf("\n");
        printf("Para n = %d foram necessarios %d passos",inicio,n_passos);
    }
}

int main(){
    int c,inicio,fim;
    printf("1: Collatz por potencia de 2.\n2: Collatz sem potencia de 2\n\n --->");
    scanf("%d",&c);
    printf("\nDigite o número do inicio do intervalo: ");
    scanf("%d",&inicio);
    printf("\nDigite o número do fim do intervalo: ");
    scanf("%d",&fim); 

    /*clock_t start = clock();*/       /*Para testar o tempo de execução, remova os sinais de comentario*/
    if (c == 1){
    Collatz_pot_d_2(inicio,fim);
    } else if (c == 2) {
    Collatz(inicio,fim);
    }
    /*clock_t stop = clock();
    double elapsed = (double)(stop - start)/1000.0;
    printf("\n\nTempo de execução em segundos: %f\n",elapsed);*/
    return 0;
}




