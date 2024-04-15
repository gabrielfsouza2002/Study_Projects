#include <stdlib.h>
#include <stdio.h>
#include "propriedadesnumericas.h"

int ehPar(long long numero){
    return !(numero%2);
}

int ehPrimo(long long numero){

    int eh_primo;
    int div ;  

    if (numero == 1)
        eh_primo = 0;
    else
        eh_primo = 1;
    div = 2;

    while ((div*div<=numero) && (eh_primo)) { 
        if (numero%div==0)
            eh_primo = 0;
        div = div+1;
    }
    return eh_primo;
}

int ehQuadradoPerfeito(long long numero){

    int operador;
    int eh_QP;
    if (numero == 1)
        eh_QP = 1;
    else
        eh_QP = 0;
    operador = 2;

    while ((operador*operador<=numero) && !(eh_QP)) { 
        if (operador*operador==numero)
            eh_QP = 1 ;
        operador = operador+1;
    }
    return eh_QP;
}

int ehCuboPerfeito(long long numero){

    int operador;
    int eh_CP;
    if (numero == 1)
        eh_CP = 1;
    else
        eh_CP = 0;
    operador = 2;

    while ((operador*operador*operador<=numero) && !(eh_CP)) { 
        if (operador*operador*operador==numero)
            eh_CP = 1 ;
        operador = operador+1;
    }
    return eh_CP;
}

int ehFibonacci(long long numero){
    
    int aux1, aux2, aux3;
    aux1=1;
    aux2=0;
    while (aux1<numero){
        aux3=aux1;
        aux1=aux1+aux2;
        aux2=aux3;
    }
    if (aux1==numero){
        return 1;
    }
    return 0;
}

int ehFatorial(long long numero){

    long long operador,aux;
    
    for (operador=1,aux=1;operador!=numero;operador++){
        aux = aux*operador;
        if (numero%operador!=0 || aux == numero){
            if(aux==numero)
                return 1;
            return 0;
        }
    }
    return 0;
}

