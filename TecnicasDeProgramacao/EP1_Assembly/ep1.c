#include <stdio.h>

int primo(int n) {

    int eh_primo;
    int div ;  

    if (n == 1)
        eh_primo = 0;
    else
        eh_primo = 1;
    div = 2;

    /* verifica se existe um divisor próprio de n. Note que basta procurar até a sqrt(n) */
    while ((div*div<=n) && (eh_primo)) { 
        if (n%div==0)
            eh_primo = 0;
        div = div+1;
    }

    return eh_primo;
}

int proximo_primo(int n){
    int proximo = n+1;  /* incrimentamos 1 ao numero n para driblar o caso de n ser primo e não entrar no laço*/
    while (!primo(proximo)){ /* Assim, por força bruta, verificamos o proximo numero ate que ele seja primo */
        proximo++;
    }
    return proximo;  
}

int eh_multiplo_d_dois_primos(int n, int *mult1, int *mult2){
         
    int fator = 2; 
    int cont = 0;  
    
    while (n > 1){   /* Decompor o número por fatores menores que irão fornecer, os primos multiplicadores do produto 'n'*/
      
        if (n % fator == 0 && cont == 0){  
            cont ++;
            n = n / fator; 
            *mult1 = fator;
        }

        if (cont != 0 && n % fator == 0){
            cont++;
            n = n / fator; 
            *mult2 = fator;
        }
    fator++; 
    }

    /* O numero n é multiplo de dois primos se o cont e igual a dois, isto é, quando o numero é fatorado apenas duas vezes */
    if (cont == 2){
        return 1;
    }else{
        return 0;
    }
}

void leitura(int *numero_convertido, int *instrucao){

    int digito;
    char comando[1];
    char numero[10];
    int i, pot;
    int cont = 0; /* Conta o tamanho */
    int junta_potencia = 0;
    scanf("%s", comando);
    scanf("%s",numero); 
    for (i=0; numero[i]!='\0'; i++){
        cont++;
    }
    for (i=cont,pot=1; i!=0; i--){ /*Descasca os digitos*/
        digito = numero[i-1] - 48; /*Faz a conversão para inteiro*/
        digito = digito*pot;
        pot = 10*pot;
        junta_potencia = junta_potencia + digito;
    }
    *numero_convertido = junta_potencia;
    *instrucao = comando[0]-48;
    }

void imprime_se_0(int *numero){
    int aux;
    int cont = 0;
    char impressao[15];
    int i,j, digito;
    int numero_decomposto = *numero;
    for (aux = *numero; aux != 0 ; aux = aux/10){
        cont++; /*Conta o tamanho do numero*/
    }
    for (i=cont; i!=0 ; i--){
        digito = numero_decomposto%10;
        numero_decomposto = numero_decomposto/10;
        impressao[i-1]= digito+48; /*Faz a conversão para inteiro*/
    }
    for (j=0; j!=cont ; j++){
        printf("%c",impressao[j]);
    }
}

void imprime_se_1(int *mult1, int *mult2){
    int aux;
    int cont = 0;
    char impressao[15];
    int i,j, digito;
    int numero_decomposto; 
    for (aux = *mult1; aux != 0 ; aux = aux/10){
        cont++; /*Conta o tamanho de mult1*/
    }
    numero_decomposto = *mult1;
    for (i=cont; i!=0 ; i--){
        digito = numero_decomposto%10;
        numero_decomposto = numero_decomposto/10;
        impressao[i-1]= digito+48; /*Converte para ascii*/
    }
    
    impressao[cont] = 32;
    cont++; /*Adiciona 1 ao tamanho apos adicionar o caracter espaço*/
    for (aux = *mult2; aux != 0 ; aux = aux/10){
        cont++; /*Conta o tamanho de mult2 somando com o tamanho de mult1 mais 1 unidade do caracter espaço*/
    }
    numero_decomposto = *mult2;
    for (i=cont; numero_decomposto!=0 ; i--){
        digito = numero_decomposto%10;
        numero_decomposto = numero_decomposto/10;
        impressao[i-1]= digito+48; /*Convert para ascii*/
    }
   
    for (j=0; j!=cont ; j++){
        printf("%c",impressao[j]);
    }
}
    
int main(){

    int numero;
    int instrucao;
    int mult1, mult2;
    leitura(&numero, &instrucao);
   if (instrucao == 0){
    numero = proximo_primo(numero);
    imprime_se_0(&numero);
   } else if( instrucao == 1 &&  eh_multiplo_d_dois_primos(numero, &mult1,&mult2) == 1 ){
    imprime_se_1(&mult1,&mult2);
   }
   return 0;
}
