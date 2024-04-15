#include<stdio.h>
#define PI 3.14159
#define RAIO_AP 200
#define RAIO_ZA 2000 /* zona de alerta */
#define DELTA_ALARME 60
#define EPS_COS 0.000001 /* precisao para calculo do cosseno e da Raiz */
#define EPS 0.01 /* precisao para valores envolvendo metros */

int iguais(float x, float y){

    if(x-y < EPS && y-x < EPS){
        return 1;
    }
    else{
    return 0;
    }
}

float modulo(float a){
    if (a < 0){
        a = a*(-1);
    }
    return a;
}


void troca(float *x,float *y){

    float aux;
    aux = *x;
    *x = *y;
    *y = aux;
}
float cosseno(float theta, float epsilon){

    float pot, fat, numerador;
    float cosTheta;
    theta = (theta * PI)/180;
    pot = 2;
    fat = pot;
    cosTheta = 1;
    numerador = (-1)*(theta*theta);

    while(modulo(numerador/fat) > epsilon){
        
        cosTheta = cosTheta + numerador/fat;
        fat = ((pot+2)*fat)*(pot+1);
        pot = pot + 2;
        numerador = (-1)*(numerador)*(theta*theta);
    }

    return cosTheta;
}

float distancia(float H, float theta){
    float d, epsilon;
    epsilon = EPS_COS;
    d = H*cosseno(theta,epsilon);
    
    return d;
}


int localiza ( float xi, float yi, float div,float xj, float yj, float djv,
float xk, float yk, float dkv, float *xv, float *yv){

    float qij, qik, pij, pik;
   

    if(iguais(xi,xj) || iguais(yi,yj)){
        troca(&xi,&xk);
        troca(&yi,&yk);
        troca(&div,&dkv);
    }
    if(iguais(xi,xk) || iguais(yi,yk)){
        troca(&xi,&xj);
        troca(&yi,&yj);
        troca(&div,&djv);

    }

    if(iguais(yi,yj) && iguais(xj,xk)){
        troca(&yj,&yk);
        troca(&djv,&dkv);
    }
    if(iguais(xi,xk)){
        troca(&xi,&xj);
        troca(&yi,&yj);
        troca(&div,&djv);
    }
    if((iguais(xi,xj) && iguais(xi,xk)) ||(iguais(yi,yj) && iguais(yi,yk))){
        return 0;
    }

    pij = ((xi*xi) - (xj*xj) + (yi*yi) - (yj*yj) - (div*div) + (djv*djv))/(2*(xi-xj));
    qij = (yj-yi)/(xi-xj);
    pik = ((xi*xi) - (xk*xk) + (yi*yi) - (yk*yk) - (div*div) + (dkv*dkv))/(2*(xi-xk));
    qik = (yk-yi)/(xi-xk);
    *xv = ((-qik*pij) - (-qij*pik))/((-qik)-(-qij));
    *yv = (*xv-pij)/qij;
    
    return 1;
}

float raiz(float x, float epsilon){
    float r_atu,r_ant;
    if (x == 0.0){
        return 0.0;
    }
    r_ant = x;
    r_atu = 0.5*(r_ant + (x/r_ant));
    while(r_ant-r_atu > epsilon){
        r_ant = r_atu;
        r_atu = 0.5*(r_ant + (x/r_ant));

    }
    return r_atu;
}

int bhaskara(float a, float b, float c, float *raiz1, float *raiz2){

    float delta;
    delta = (b*b) - (4*a*c);
    
    if (delta >= 0 && a != 0){
        *raiz1 = (-b + raiz(delta,EPS_COS))/(2*a);
        *raiz2 = (-b - raiz(delta,EPS_COS))/(2*a);
        return 1;
    }
    return 0;
}

int intercepta(float x0, float y0, float x1, float y1, float *x, float
*y){

float m,b,c, raiz1,raiz2,Y1,Y2;
int delta;

if (x1==x0){
    m = 0;
}
else{
m=(y1-y0)/(x1-x0);
}

b = (m*x0 - m*x1)/(y0-y1);
c = y0*b - m*x0;

delta = bhaskara(m*m+1,2*m*c,c*c-40000,&raiz1,&raiz2);

Y1 = -(-m*raiz1-c);
Y2 = -(-m*raiz2-c);

    if(raiz((x1-raiz1)*(x1-raiz1)+(y1-Y1)*(y1-Y1),EPS_COS) < raiz((x1-raiz2)*(x1-raiz2)+(y1-Y2)*(y1-Y2),EPS_COS)){
        *x = raiz1;
        *y = Y1;
    }
    else{
        *x = raiz2;
        *y = Y2;
    }

if(delta && raiz((x0)*(x0)+(y0)*(y0),EPS_COS) > raiz((x1)*(x1)+(y1)*(y1),EPS_COS) && !(iguais(x1,x0)&&iguais(y0,y1)) && (((*x-x0 > 0) && (*x-x1> 0)) || ((*x-x0 < 0) && (*x-x1)< 0))){
    return 1;
}
else{
    return 0;
}


}

int main(){

FILE *arq;
char filename[256];
int n_casos, id_veiculo,id_antena1,id_antena2,id_antena3,interceptaAP,localizacaoA,localizacaoP,i;
float x_p1,y_p1,x_p2,y_p2,x_p3,y_p3,H_p1,H_p2,H_p3,theta_p1,theta_p2,theta_p3,xv1,yv1,xv2,yv2,div,djv,dkv,tempo,distancia_percorrida,velocidade,distancia_origem,x_inter,y_inter,distancia_AP;

printf("Programa-demo para o Sistema de Monitoramento\n");
printf("\n\nDigite o nome do arquivo com os dados a serem processados: ");
scanf("%s", filename);

arq = fopen(filename, "r");

if (arq == NULL) {
printf("Nao consegui abrir o arquivo %s.\n", filename);
return 0;
}

fscanf(arq, "%d", &n_casos);
printf("\nNumero de casos a serem analisados: %d",n_casos);

for(i = 0; i<n_casos;i++){
    fscanf(arq, "%d", &id_veiculo);
    printf("\n\nIDENTIFICACAO: veiculo %d\n",id_veiculo);
    printf("\nAntenas na posicao previa\n");
    printf("       | id |       posicao       |   H(m)   | angulo | distancia |");
    
    fscanf(arq, "%d", &id_antena1);
    fscanf(arq, "%f", &x_p1);
    fscanf(arq, "%f", &y_p1);
    fscanf(arq, "%f", &H_p1);
    fscanf(arq, "%f", &theta_p1);
    fscanf(arq, "%d", &id_antena2);
    fscanf(arq, "%f", &x_p2);
    fscanf(arq, "%f", &y_p2);
    fscanf(arq, "%f", &H_p2);
    fscanf(arq, "%f", &theta_p2);
    fscanf(arq, "%d", &id_antena3);
    fscanf(arq, "%f", &x_p3);
    fscanf(arq, "%f", &y_p3);
    fscanf(arq, "%f", &H_p3);
    fscanf(arq, "%f", &theta_p3);

    div = distancia(H_p1,theta_p1);
    djv = distancia(H_p2,theta_p2);
    dkv = distancia(H_p3,theta_p3);

    printf("\n         %d   (%8.2f,%8.2f)  %8.2f  %8.2f  %8.2f  \n         %d   (%8.2f,%8.2f)  %8.2f  %8.2f  %8.2f  \n         %d   (%8.2f,%8.2f)  %8.2f  %8.2f  %8.2f   ",id_antena1,x_p1,y_p1,H_p1,theta_p1,div,id_antena2,x_p2,y_p2,H_p2,theta_p2,djv,id_antena3,x_p3,y_p3,H_p3,theta_p3,dkv);


    localizacaoP = localiza(x_p1,y_p1,div,x_p2,y_p2,djv,x_p3,y_p3,dkv,&xv1,&yv1);

    fscanf(arq, "%f", &tempo);
    fscanf(arq, "%d", &id_antena1);
    fscanf(arq, "%f", &x_p1);
    fscanf(arq, "%f", &y_p1);
    fscanf(arq, "%f", &H_p1);
    fscanf(arq, "%f", &theta_p1);
    fscanf(arq, "%d", &id_antena2);
    fscanf(arq, "%f", &x_p2);
    fscanf(arq, "%f", &y_p2);
    fscanf(arq, "%f", &H_p2);
    fscanf(arq, "%f", &theta_p2);
    fscanf(arq, "%d", &id_antena3);
    fscanf(arq, "%f", &x_p3);
    fscanf(arq, "%f", &y_p3);
    fscanf(arq, "%f", &H_p3);
    fscanf(arq, "%f", &theta_p3);

    if(localizacaoP == 1){

        printf("\n\nLocalizacao previa: (%.2f,%8.2f)\n",xv1,yv1);
        printf("\nIntervalo de Tempo: %.2f\n",tempo);

        printf("\nAntenas na posicao atual\n");
        printf("       | id |       posicao       |   H(m)   | angulo | distancia |");
        
        div = distancia(H_p1,theta_p1);
        djv = distancia(H_p2,theta_p2);
        dkv = distancia(H_p3,theta_p3);

   printf("\n         %d   (%8.2f,%8.2f)  %8.2f  %8.2f  %8.2f  \n         %d   (%8.2f,%8.2f)  %8.2f  %8.2f  %8.2f  \n         %d   (%8.2f,%8.2f)  %8.2f  %8.2f  %8.2f   ",id_antena1,x_p1,y_p1,H_p1,theta_p1,div,id_antena2,x_p2,y_p2,H_p2,theta_p2,djv,id_antena3,x_p3,y_p3,H_p3,theta_p3,dkv);

        localizacaoA = localiza(x_p1,y_p1,div,x_p2,y_p2,djv,x_p3,y_p3,dkv,&xv2,&yv2);
        if(localizacaoA==1){
            
            printf("\n\nLocalizacao atual: (%.2f,%.2f)\n",xv2,yv2);
            if (tempo == 0.0 || (iguais(xv1,xv2)&&iguais(yv1,yv2))){
                velocidade = 0;
            }else{
            velocidade = (raiz((xv2-xv1)*(xv2-xv1)+(yv2-yv1)*(yv2-yv1),EPS_COS))/tempo;
            }
            interceptaAP = intercepta(xv1,yv1,xv2,yv2,&x_inter,&y_inter);
            distancia_percorrida = velocidade*tempo;
            distancia_origem = raiz(xv2*xv2 + yv2*yv2,EPS_COS);
            distancia_AP = raiz((xv2-x_inter)*(xv2-x_inter)+ (yv2-y_inter)*(yv2-y_inter),EPS_COS);

            printf("\nDistancia percorrida: %.2f",distancia_percorrida);
            printf("\nVelocidade: %.2f\n",velocidade);
            printf("\nDistancia da origem: %8.2f",distancia_origem);
            
            if (distancia_origem <= RAIO_ZA && distancia_origem > RAIO_AP ){
                if(velocidade>0){
                    printf("\n\nO veiculo esta em movimento NA zona de alerta\n");
                }
                else{
                    printf("\nO veiculo esta estacionado NA zona de alerta\n");
                }
                if(interceptaAP){
                    printf("\nTrajetoria INTERCEPTARA AP\n");
                    printf("\nDistancia atual a AP e de %.2f metros\n",distancia_AP);
                    printf("\nInterseccao ocorrera em %.2f segundos na coordenada (%.2f,%.2f)",distancia_AP/velocidade,x_inter,y_inter);

                    if(distancia_AP/velocidade < 60){
                        printf("\n\n     ****************************************************************\n     ALARME, ALARME, ALARME, ALARME !! Invasao iminente !\n     ****************************************************************\n");            
                    }
                }
                else{
                    printf("\nTrajetoria NAO INTERCEPTARA AP\n");
                }
            }

            else if(velocidade > 0 && distancia_origem > RAIO_ZA){
                printf("\nO veiculo esta em movimento FORA zona de alerta\n");
            }
            else if(velocidade == 0 && distancia_origem > RAIO_ZA){
                printf("\nO veiculo esta estacionado FORA zona de alerta\n");
            }
            else if(distancia_origem <= RAIO_AP){
                if(velocidade > 0){
                printf("\nO veiculo esta em movimento NA AP\n");
                }
                else{
                    printf("\nO veiculo esta estacionado NA AP\n");
                }
                printf("\n******************************************************\n ALARME, ALARME, ALARME, ALARME !! Veiculo esta na AP !\n*****************************************************\n");
            }
        }
        else{
            printf("\n\nNao foi possivel calcular a localizacao atual do veiculo %d. \n\n",id_veiculo);
            printf("Nao foi possivel determinar a situacao do veiculo %d",id_veiculo);
        }

    }
    else{
    printf("\n\nNao foi possivel calcular a localizacao inicial do veiculo %d. \n\n",id_veiculo);
    printf("Nao foi possivel determinar a situacao do veiculo %d",id_veiculo);
    }
}
fclose(arq);
return 0;
}