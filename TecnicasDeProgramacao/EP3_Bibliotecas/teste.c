#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <sys/time.h>
#include <time.h>
#include "VetorAleatorio.h"
#include "propriedadesnumericas.c"
#define tamanho 10
#define seed 2002

/*Para ter o tempo de execucao, remova o codigo comentado e use a funcao float time_diff*/

/*float time_diff(struct timeval *start, struct timeval *end)
{
    return (end->tv_sec - start->tv_sec) + 1e-6*(end->tv_usec - start->tv_usec);
}
*/
int main(){

    /*struct timeval start;
    struct timeval end;
    */
    long long *vetor = malloc(sizeof(long)*tamanho);
    int *gabarito_ehPar = malloc(sizeof(int)*tamanho);
    int *gabarito_ehPrimo = malloc(sizeof(int)*tamanho);
    int *gabarito_ehQuadradoPerfeito = malloc(sizeof(int)*tamanho);
    int *gabarito_ehCuboPerfeito = malloc(sizeof(int)*tamanho);
    int *gabarito_ehFibonacci = malloc(sizeof(int)*tamanho);
    int *gabarito_ehFatorial = malloc(sizeof(int)*tamanho);
    int i;

    gabarito_ehPar[0] = 1;
    gabarito_ehPar[1] = 0;
    gabarito_ehPar[2] = 0;
    gabarito_ehPar[3] = 1;
    gabarito_ehPar[4] = 0;
    gabarito_ehPar[5] = 1;
    gabarito_ehPar[6] = 1;
    gabarito_ehPar[7] = 1;
    gabarito_ehPar[8] = 1;
    gabarito_ehPar[9] = 0;

    gabarito_ehPrimo[0] = 0;
    gabarito_ehPrimo[1] = 0;
    gabarito_ehPrimo[2] = 1;
    gabarito_ehPrimo[3] = 0;
    gabarito_ehPrimo[4] = 0;
    gabarito_ehPrimo[5] = 0;
    gabarito_ehPrimo[6] = 0;
    gabarito_ehPrimo[7] = 0;
    gabarito_ehPrimo[8] = 0;
    gabarito_ehPrimo[9] = 0;

    gabarito_ehQuadradoPerfeito[0] = 0;
    gabarito_ehQuadradoPerfeito[1] = 0;
    gabarito_ehQuadradoPerfeito[2] = 0;
    gabarito_ehQuadradoPerfeito[3] = 0;
    gabarito_ehQuadradoPerfeito[4] = 0;
    gabarito_ehQuadradoPerfeito[5] = 0;
    gabarito_ehQuadradoPerfeito[6] = 0;
    gabarito_ehQuadradoPerfeito[7] = 0;
    gabarito_ehQuadradoPerfeito[8] = 0;
    gabarito_ehQuadradoPerfeito[9] = 0;

    gabarito_ehCuboPerfeito[0] = 0;
    gabarito_ehCuboPerfeito[1] = 0;
    gabarito_ehCuboPerfeito[2] = 0;
    gabarito_ehCuboPerfeito[3] = 0;
    gabarito_ehCuboPerfeito[4] = 0;
    gabarito_ehCuboPerfeito[5] = 0;
    gabarito_ehCuboPerfeito[6] = 0;
    gabarito_ehCuboPerfeito[7] = 0;
    gabarito_ehCuboPerfeito[8] = 0;
    gabarito_ehCuboPerfeito[9] = 0;

    gabarito_ehFibonacci[0] = 0;
    gabarito_ehFibonacci[1] = 0;
    gabarito_ehFibonacci[2] = 0;
    gabarito_ehFibonacci[3] = 0;
    gabarito_ehFibonacci[4] = 0;
    gabarito_ehFibonacci[5] = 0;
    gabarito_ehFibonacci[6] = 0;
    gabarito_ehFibonacci[7] = 0;
    gabarito_ehFibonacci[8] = 0;
    gabarito_ehFibonacci[9] = 0;

    gabarito_ehFatorial[0] = 0;
    gabarito_ehFatorial[1] = 0;
    gabarito_ehFatorial[2] = 0;
    gabarito_ehFatorial[3] = 0;
    gabarito_ehFatorial[4] = 0;
    gabarito_ehFatorial[5] = 0;
    gabarito_ehFatorial[6] = 0;
    gabarito_ehFatorial[7] = 0;
    gabarito_ehFatorial[8] = 0;
    gabarito_ehFatorial[9] = 0;

    for (i=0; i<10; i++){
        /*gettimeofday(&start, NULL);*/
            vetor = criaVetorAleatorio(seed,tamanho);
        /*gettimeofday(&end, NULL);*/
     }

    for (i=0; i<tamanho; i++){
        /*gettimeofday(&start, NULL);*/
            assert(gabarito_ehPar[i]==ehPar(vetor[i]));
        /*gettimeofday(&end, NULL);*/       

        /*gettimeofday(&start, NULL);*/        
            assert(gabarito_ehPrimo[i]==ehPrimo(vetor[i]));
        /*gettimeofday(&end, NULL);*/

        /*gettimeofday(&start, NULL);*/
            assert(gabarito_ehQuadradoPerfeito[i]==ehQuadradoPerfeito(vetor[i]));
        /*gettimeofday(&end, NULL);*/

        /*gettimeofday(&start, NULL);*/
            assert(gabarito_ehCuboPerfeito[i]==ehCuboPerfeito(vetor[i]));
        /*gettimeofday(&end, NULL);*/

        /*gettimeofday(&start, NULL);*/
            assert(gabarito_ehFibonacci[i]==ehFibonacci(vetor[i]));
        /*gettimeofday(&end, NULL);*/

        /*gettimeofday(&start, NULL);*/
            assert(gabarito_ehFatorial[i]==ehFatorial(vetor[i]));
        /*gettimeofday(&end, NULL);*/
    }
    
    free(gabarito_ehPar);
    free(gabarito_ehPrimo);
    free(gabarito_ehQuadradoPerfeito);
    free(gabarito_ehCuboPerfeito);
    free(gabarito_ehFibonacci);
    free(gabarito_ehFatorial);
    free(vetor);

    printf("\nTodas as funções foram testadas e estão funcionando corretamente! OBS: Vale apenas para assert habilitado\n\n");

    return 0;    
}
