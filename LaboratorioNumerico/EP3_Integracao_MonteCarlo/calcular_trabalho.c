#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#define qtdDados 7
#define resultadoAnalitico 117.13


double metodoDoTrapezio(double h, double y[], int y_len) {
    double integral=0;
    for(int i=0; i<(y_len-1); i++)
        integral += h*(y[i]+y[i+1])/2;
    return integral;
}

double metodoDeSimpson(double h, double y[], int y_len) {
    double integral=0;
    for(int i=0; i<(y_len-2); i=i+2)
        integral += h*(y[i]+4*y[i+1]+y[i+2])/3;
    return integral;
}

double psi(int tamanhoX, double x, double dado_x[]) {
    int i = 0;
    double psi = 1;
    for(i=0; i < tamanhoX; i++){
        psi *= (x - dado_x[i]);
    }
    return psi;
}

double* interpolacaoPorLagrange(int tamanhoX, double h, double dado_x[], double dado_y[]) {
    int qtdPontosInterpolados = 1 + (int)((dado_x[tamanhoX-1]-dado_x[0])/h);
    double* vector_i = malloc(tamanhoX*sizeof(double));
    double* vector_j = malloc(tamanhoX*sizeof(double));
    int i, j, z;
    for(i=0; i<tamanhoX; i++) {
        vector_i[i] = 1;
        for(j=0; j < tamanhoX; j++) {
            if(j!=i){
                vector_i[i] *= (dado_x[i] - dado_x[j]);
            }
        }
        vector_j[i] = 1/vector_i[i];
    }

    double x;
    int flag = 0;
    double* interpolacao_x = malloc(qtdPontosInterpolados*sizeof(double));
    double* interpolacao_y = malloc(qtdPontosInterpolados*sizeof(double));

    for(i= 0; i < qtdPontosInterpolados; i++) {
        flag = 0;
        interpolacao_x[i] = dado_x[0] + h*i;
        x = interpolacao_x[i];
        for(z = 0; z < tamanhoX; z++){
            if(x == dado_x[z]){
                flag = 1;
                interpolacao_y[i] = dado_y[z];
            }
        }
        if(flag == 0){
            interpolacao_y[i] = 0;
            for(j = 0; j < tamanhoX; j++) {
                interpolacao_y[i] += vector_j[j]*dado_y[j]/(x-dado_x[j]);
            }
            interpolacao_y[i] *= psi(tamanhoX, x, dado_x);
        }
    }

    free(vector_i);
    free(vector_j);
    free(interpolacao_x);

    return interpolacao_y;
}


int main() {
    double* vector_interpolador;
    int qtdPontosInterpolados;
    int i;
    double integral;
    double ErroAbsoluto;
    double ErroRelativo;

    double F[qtdDados]  = {0, 9, 13, 14, 10.5, 12, 5};
    double h[qtdDados]  = {8, 3.5, 0.57, 0.16, 0.015, 0.005, 0.0009};
    double F_tempo[qtdDados] = {0, 1.5297, 9.5120, 8.7025, 2.8087, 1.0881, 0.3537};
    double dado_x[qtdDados]  = {0, 5, 10, 15, 20, 25, 30};
    double tempo[qtdDados]  = {0.5, 1.4, 0.75, 0.9, 1.3, 1.48, 1.5};
   

    printf("Integral pelo método do Trapézio: \n");
    printf("ErroAbsoluto   \t ErroRelativo\t I\t         h\n");

    for(i = 0; i < qtdDados; i++) {
        vector_interpolador = interpolacaoPorLagrange(qtdDados, h[i], dado_x, F_tempo);
        qtdPontosInterpolados = (int)(30/h[i]) + 1;
        integral = metodoDoTrapezio(h[i], vector_interpolador, qtdPontosInterpolados);
        ErroAbsoluto = integral - resultadoAnalitico;
        ErroRelativo = 100*ErroAbsoluto/resultadoAnalitico;

        printf("%.8f\t %.8f \t %.6f\t %.6f\n", ErroAbsoluto, ErroRelativo, integral, h[i]);
    }

    printf("\nIntegral pelo método de Simpson: \n");
    printf("ErroAbsoluto   \t ErroRelativo\t I\t         h\n");

    for(i = 0; i < qtdDados; i++) {
        vector_interpolador = interpolacaoPorLagrange(qtdDados, h[i], dado_x, F_tempo);
        qtdPontosInterpolados = (int)(30/h[i]) + 1;
        integral = metodoDeSimpson(h[i], vector_interpolador, qtdPontosInterpolados);
        ErroAbsoluto = integral - resultadoAnalitico;
        ErroRelativo = 100*ErroAbsoluto/resultadoAnalitico;

        printf("%.8f\t %.8f \t %.6f\t %.6f\n", ErroAbsoluto, ErroRelativo, integral, h[i]);
    }
    
    free(vector_interpolador);
    return 0;
}



