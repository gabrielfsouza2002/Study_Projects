#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.14159265358979323846
#define qtd_N 9
#define resultado_analitico_integral_1 0.45969769
#define resultado_analitico_integral_2 580.
#define resultado_analitico_integral_3 1.

double f1(double x) {
    return sin(x);
}

double f2(double x) {
    return x*x*x;
}

double f3(double x) {
    return exp(-x);
}

double calculandoPI(int N) {
    int i = 0;
    double integral, x_u, y_u;
    for(i = 0; i < N; i++) {
        y_u = (double)rand()/RAND_MAX;
        x_u = (double)rand()/RAND_MAX;
        if(x_u*x_u + y_u*y_u < 1) {
            integral += 1;
        }
    }
    integral = 4*integral/N;
    return integral;
}

double integracaoMonteCarlo(double p, double q, int n, double (*f)(double)) {
    double integral, u;
    for(int i = 0; i < n; i++) {
        u = (double)rand()/RAND_MAX;
        integral += (*f)(p+u*(q-p));
    }
    integral = integral*(q-p)/n;
    return integral;
};

int main() {
    int n;
    double integral;
    double erroRelativo;
    double erroAbsoluto;
    printf("\nI1:\n");
    printf("ErroAbsoluto   \t ErroRelativo\t  N\t  I\n");;
    int i;
    for(i = 1; i < qtd_N; i++) {
        n = pow(10, i);
        integral = integracaoMonteCarlo(0, 1, n, f1);
        erroAbsoluto = integral - resultado_analitico_integral_1;
        erroRelativo = erroAbsoluto/resultado_analitico_integral_1;
        printf("%f\t  %f\t  10^%d\t  %f\n", erroAbsoluto, 100*erroRelativo, i, integral);
    }

    printf("\nI2:\n");
    printf("ErroAbsoluto   \t ErroRelativo\t  N\t  I\n");;
    for(i = 1; i < qtd_N; i++) {
        n = pow(10, i);
        integral = integracaoMonteCarlo(3, 7, n, f2);
        erroAbsoluto = integral - resultado_analitico_integral_2;
        erroRelativo = erroAbsoluto/resultado_analitico_integral_2;
        printf("%f\t  %f\t  10^%d\t  %f\n", erroAbsoluto, 100*erroRelativo, i, integral);
    }
    
    printf("\nI3:\n");
    printf("ErroAbsoluto   \t ErroRelativo\t  N\t  I\n");;
    for(i = 1; i < qtd_N; i++) {
        n = pow(10, i);
        integral = integracaoMonteCarlo(0, 20, n, f3);
        erroAbsoluto = integral - resultado_analitico_integral_3;
        erroRelativo = erroAbsoluto/resultado_analitico_integral_3;
        printf("%f\t  %f\t  10^%d\t  %f\n", erroAbsoluto, 100*erroRelativo, i, integral);
    }
    
    printf("\nI4:\n");
    printf("ErroAbsoluto   \t ErroRelativo\t  N\t  I\n");;
    for(i = 1; i < qtd_N; i++) {
        n = pow(10, i);
        integral = calculandoPI(n);
        erroAbsoluto = integral - PI;
        erroRelativo = erroAbsoluto/PI;
        printf("%f\t  %f\t  10^%d\t  %f\n", erroAbsoluto, 100*erroRelativo, i, integral);
    }

    return 0;
}


