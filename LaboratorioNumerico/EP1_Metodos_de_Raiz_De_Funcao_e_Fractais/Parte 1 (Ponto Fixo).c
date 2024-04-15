#include <stdio.h>
#include <math.h>


float procura_raizes_g1(float x_ini, float epsilon1, float epsilon2){

    float x, g1, aux;

    x = x_ini;
    aux = x;
    g1 = pow(exp(x)/2, 0.5); 

    while ((fabs(g1 - aux) > epsilon1) || (fabs(exp(g1)-2*(g1*g1)) > epsilon2) ) {
        aux = x;
        g1 = pow(exp(x)/2, 0.5); 
        x = g1;

    }
    return g1;
}


float procura_raizes_g2(float x_ini, float epsilon1, float epsilon2){

    float x, g2, aux;

    x = x_ini;
    aux = x;
    g2 = -1 * pow(exp(x)/2, 0.5);

    while ((fabs(g2 - aux) > epsilon1) || (fabs(exp(g2)-2*(g2*g2)) > epsilon2) ) {
        aux = x;
        g2 = -1 * pow(exp(x)/2, 0.5);
        x = g2;
    }
    return g2;
}

float procura_raizes_g3(float x_ini, float epsilon1, float epsilon2){

    float x, g3, aux;

    x = x_ini;
    aux = x;
    g3 = log(2 * pow(x,2)); 

    while ((fabs(g3 - aux) > epsilon1) || (fabs(exp(g3)-2*(g3*g3)) > epsilon2) ) {
        aux = x;
        g3 = log(2 * pow(x,2)); ;
        x = g3;
    }
    return g3;



}



int main(){
    
    float raiz1, raiz2, raiz3, epsilon1, epsilon2;
    epsilon1 = 0.00001;
    epsilon2 = epsilon1;

    raiz1 = procura_raizes_g1(1, epsilon1, epsilon2);
    raiz2 = procura_raizes_g2(0, epsilon1, epsilon2);
    raiz3 = procura_raizes_g3(1, epsilon1, epsilon2);

    printf("\n\nAs três raízes encontradas foram: %f, %f, %f\n", raiz1, raiz2, raiz3);
    
    return 0;
}