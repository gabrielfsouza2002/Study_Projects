#include<stdio.h>
#include <stdlib.h>

int main() {

    printf("Bem-vindo ao JOGO da FORCA !!\n===============================\n");

    int num; 
    int digito; 
    int aux_num1,aux_num2;  
    int cont1 = 1;
    int cont2; 
    int tentativas;
    int depuracao = 0;
    int opcao = 0;
    int jogadas = 0;
    int venceu = 0;
    int a1,a2,a3;
    int adivinhou1,adivinhou2,adivinhou3;
    int sub_a1,sub_a2,sub_a3;

    while(opcao != 3){ /*O programa será executado enquanto o usuário não escolher a opção 3.*/

        printf("\nDepuracao = %d / Jogos jogados = %d\n",depuracao, jogadas);
        printf(" \n 1. Continuar a jogar\n 2. Alterar modo de depuracao e continuar a jogar\n 3. Parar\n");
        printf("\nEscola uma opcao: ");
        scanf("%d",&opcao);

        if (opcao == 2 && depuracao == 0){ /*Essa condição permite alterar o modo de depuração durante a execução do programa quando o usuário digita a opção 2.*/
            depuracao = 1;
        }
        else if (opcao == 2) { 
            depuracao = 0;
        }
        
        if (opcao == 1){ /* Quando o usuário digita a opção 1, essa condição permite que o jogo inicie, portanto, a programação do jogo esta dentro dessa condição. */

            num = rand() % 1000; /* Gera número aleatório > 0 e < 1000 */

            /* Foram necessárias duas variáveis auxiliares para não comprometer o valor da variável num*/
            aux_num1 = num;  
            aux_num2 = num;

            /*Foi necessário guardar algarimos (a3 = primeiro digito, a2 = segundo digito, a1 = terceiro digito) do numero aleatório gerado (num) para futuramente verificar se o usuário acertou o digito. Ex: num = "xxx" Saída: _ _ _ == Saída: a3 a2 a1 */

            if (num/100 == 0){ /*Se o numero gerado aleatoriamente (num) ter apenas dois digitos, isto é num/100 == 0, entao o primeiro digito da forca deve ser 0. num = 41 resposta: (0) 4 1 */
                a3 = 0;
            }

            cont1 = 1; /* Esse contador 1 permite direcionar corretamente os valores de cada algarismo. Por exemplo: a1 é atribuido no primero loop (cont1 = 1), e assim por diantea té cont1 = 3, pois são 3 digitos do jogo. */
            while (aux_num2 > 0){ 

                /* Descascando o numero*/ 
                aux_num1 = aux_num2%10; 
                aux_num2 = aux_num2/10; 
                /* Guardando os digitos*/ 
                if (cont1 == 1){   
                    a1 = aux_num1; 
                }
                else if (cont1 == 2){
                    a2 = aux_num1;      
                }
                else if (cont1 == 3){
                    a3 = aux_num1;
                }
                cont1 = cont1 + 1;
            }
            /* Para evitar futuramente repetições e o comprometimento do valor correto das variáveis a1,a2,a3 foi necessário criar 3 variáveis substitutas*/ 
            sub_a1 = a1;
            sub_a2 = a2;
            sub_a3 = a3;
            /* As variaveis "adivinhou" são os digitos que o usuário ja adivinhou, sendo que, "-1" representa que o digito ainda não foi adivinhado. Ex: digito = 4 num = 454 Saída = 4, -1, 4. O número negativo foi escolhido porque ele se diferencia dos outros digitos que são sempre positivos*/ 
            adivinhou1 = -1;
            adivinhou2 = -1;
            adivinhou3 = -1;

            cont2 = 3; /*Esse contador 2 representa o número de digitos que não foram adivinhados*/ 
            tentativas = 6; /* Limite de tentativas*/ 

            while (tentativas > 0 && cont2 > 0){ /* Esse laço ocorre enquanto o numero de tentativas não expira && o usuário ainda nao adivinhou todos os digitos*/ 

                if (depuracao == 1){
                    printf( "\nNumero a ser adivinhado: %d", num);
                }

                printf("\nrestam %d tentativas\n",tentativas);
                printf("Sua proxima tentativa (digito de 0 a 9): ");
                scanf("%d",&digito); 
                
                /* As 3 condições abaixo visam direcionar corretamente os valores adivinhados e evitar por meio das variáveis "sub_" a repetição de digitos adivinhados. Por isso as variáveis "sub_" ficaram negativas para diferenciar os digitos.*/   

                if (digito == sub_a1){         
                    cont2 = cont2 - 1;
                    adivinhou1 = a1;
                    sub_a1 = -1;
                }

                if (digito == sub_a2){
                    cont2 = cont2 -1;
                    adivinhou2 = a2;
                    sub_a2 = -1;
                }

                if (digito == sub_a3){
                    cont2 = cont2 - 1;
                    adivinhou3 = a3;
                    sub_a3 = -1;
                }

                printf("Voce ja acertou os seguintes digitos: %d, %d, %d \n", adivinhou3, adivinhou2, adivinhou1); 
                tentativas = tentativas - 1;

                /* Se as tentativas expirarem e o número de digitos não adivinhados for diferente de 0 então o usuário perdeu. O complemento dessa lógica serve caso o usuário vença*/ 

                if (tentativas == 0 && cont2 != 0){ 
                    printf("\nVoce PERDEU !\n");
                }

                else if (cont2 == 0){
                    printf("\nVoce VENCEU !\n");
                    venceu = venceu + 1;
                }
            }

            jogadas = jogadas + 1;
        }
    }

    printf("\nVoce jogou %d jogos e venceu %d!\n",jogadas, venceu);

    return 0;
}