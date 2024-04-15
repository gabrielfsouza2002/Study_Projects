#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>

#define WIDTH 800
#define HEIGHT 800
#define NMAX 50

double complex evalf1(double complex z) {
        return cpow(z, 3) - 1.0;
}
double complex evalf2(double complex z) {
        return cpow(z, 4) - 1.0;
}
double complex evalf3(double complex z) {
    return cpow(z, 2) - 1.0;
}
double complex evalf4(double complex z) {
        return cpow(z, 3) -z;
}
double complex evalf5(double complex z) {
        return cpow(z, 4) - 2.0;
}


double complex evalDf1(double complex z) {
        return 3.0 * cpow(z, 2);
}
double complex evalDf2(double complex z) {
        return 4.0 * cpow(z, 3);
}
double complex evalDf3(double complex z) {
    return 2.0 * cpow(z, 1);
}
double complex evalDf4(double complex z) {
    return 3.0 * cpow(z, 2) -1;
}
double complex evalDf5(double complex z) {
    return 4.0 * cpow(z, 3);
}


/* Função que calcula a raiz pelo método de Newton*/
int newton(double complex z, double complex *raiz, double complex (*evalf)(double complex), double complex (*evalDf)(double complex), int n_raizes) {

    int n = 0;
    double complex fz = z;

    while (n < NMAX) {
        double complex fz2 = evalf(fz)/evalDf(fz);
        fz -= fz2;
        n++;

        /* Testa se a convergência foi alcançada*/
        for (int i = 0; i < n_raizes; i++) {
            if (cabs(fz - raiz[i]) < 1e-6) {
                return i;
            }
        }
    }
    return -1;
}

int main() {

    double complex raiz1[3] = {1.0, -0.5 + 0.866025*I, -0.5 - 0.866025*I};
    double complex raiz2[4] = {1.0, -1.0, I, -I};   
    double complex raiz3[2] = {1.0 + 0.0*I, -1.0 + 0.0*I};
    double complex raiz4[3] = {0.0 + 0.0*I, 0.5 + 0.8660254 *I, 0.5 - 0.8660254 *I};
    double complex raiz5[4] = {1.189207, 1.189207*I,-1.189207, -1.189207*I};

    double x, y;
    int cor, n;

    printf("\nDigite 1 para plotar a função: x**3 - 1\nDigite 2 para plotar a bacia da função: x**4 - 1\nDigite 3 para plotar a bacia função: x**2 - 1\nDigite 4 para plotar a bacia da função x**3 - x\nDigite 5 para plotar a bacia da função x**4 - 2\n---->");
    scanf("%d", &n);

    /* Abre o arquivo para escrita*/
    FILE *fp_txt = fopen("output.txt", "w");
    

    /* Escreve os valores para cada ponto na imagem*/
    for (int j = 0; j < HEIGHT; j++) {
        y = 4.0*(j - HEIGHT/2.0)/HEIGHT;
        for (int i = 0; i < WIDTH; i++) {
            x = 4.0*(i - WIDTH/2.0)/WIDTH;
            double complex z = x + I*y;

            /* Calcula a cor para este ponto*/
            if (n == 1)
                cor = newton(z, raiz1, evalf1, evalDf1, 3);
            if (n == 2)
                cor = newton(z, raiz2, evalf2, evalDf2, 4);
            if (n == 3)
                cor = newton(z, raiz3, evalf3, evalDf3, 2);
            if (n == 4)
                cor = newton(z, raiz4, evalf4, evalDf4, 3);
            if (n == 5)
                cor = newton(z, raiz5, evalf5, evalDf5, 4);

            /* Escreve o ponto e a cor no arquivo*/
            fprintf(fp_txt, "%.3lf %.3lf %d\n", x, y, cor);
        }
    }

    /* Fecha o arquivo*/
    fclose(fp_txt);
    
    FILE *gnuplot = popen("\"C:\\Program Files\\gnuplot\\bin\\gnuplot\" -persist", "w"); /*importante colocar o local do executavel do gnuplot*/    
    fprintf(gnuplot, "set term png\n");  /* Escolher o formato da saída*/
    fprintf(gnuplot, "set output 'bacia.png'\n");  /* Definir o nome do arquivo de saída*/
    fprintf(gnuplot, "set size square\n");  /* Definir a proporção do gráfico*/
    fprintf(gnuplot, "set xrange [-2:2]\n");  /* Definir os limites do eixo x*/
    fprintf(gnuplot, "set yrange [-2:2]\n");  /* Definir os limites do eixo y*/
    fprintf(gnuplot, "plot 'output.txt' using 1:2:3 with points pt 7 palette notitle\n");  /* Plotar os pontos*/
    pclose(gnuplot);
    return 0;
}