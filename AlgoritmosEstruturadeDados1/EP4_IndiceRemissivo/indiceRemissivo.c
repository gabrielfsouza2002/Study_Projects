#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tabelaSimbolos.c"
#define qtdLetras 2
#define MAX 256

/*

Informações Relevantes:

- Os arquivos enviados são modificações dos algorítimos publicados no moodle da diciplina.
- O algorítimo remove com strtok alguns caractéres indesejáveis, mas não todos, logo, se aparecer um caractére fora da lista do strtok ou fora do formato UTF8, a palavra vai ser odenada e iniciar com um "?".
- Palavras com acento "´", serão incluídas para ordenação, e palavras com "^ ou ~" não serão incluídas.
- A exibição do índice remissivo é realizada no "arv.c", e vale destacar que o terminal não impreme todo o conteúdo que deveria (mas no programa todos os dados estão presentes) por conta da alta quantidade de espaçamento que a impressão do programa ocupa. Para imprimir mais dados no terminal, é necessário editar o arquivo "arv.c" removendo os "\n" dos "printf".
- Para construção do índice remissivo, foi feita uma alteração no arquivo "arv.h" onde os raiz->valor (quantas vezes a palavra se repetiu em uma determinada linha) e raiz->linhha (linha em que foi encontrada a palavra) são vetores que são percorridos por um índice raiz-i.
- Para compilar e executar o código, bastas digitar os seguindos comandos no terminal: "gcc -Wall -ansi -pedantic -O2 indiceRemissivo.c -o indiceRemissivo" e "./indiceRemissivo". Depois, insira o diretório do arquivo .txt que deseja abrir.

*/

int main(int argc, char **argv) {

    char * palavra;
    int valor;
    int linha = 1;
    int i = 0;
    no * p = NULL;
    no * aux = NULL;
    char url[10];
    char info[MAX];
    
    FILE *arq;
    printf("\nDigite o diretorio do arquivo: ");
    if(scanf("%s", url)){
        arq = fopen(url, "r");
        printf("\n");
    }
    
    if(arq == NULL)
        printf("Erro, nao foi possivel abrir o arquivo\n");

    else
        while( (fgets(info, sizeof(info), arq)) != NULL ){
        
            palavra = strtok(info, " ~,.-!?;[]'*_—#:@$%%^&(){}<>/|+=1234567890\"\r\n");

                while(palavra != NULL){
                    if (strlen(palavra) >= qtdLetras){

                        valor = 1;
                        aux = busca(p, palavra);
                        if (aux != NULL){

                            if(aux->linha[aux->i] < linha){
                                aux->i ++;
                                aux->valor[aux->i] = 1;
                                i = aux->i;
                            }
                    
                            else{
                                valor = ++aux->valor[aux->i];
                                i=0;
                            }
                        }
                        else
                            i=0;

                        p = insercao(p, palavra, valor,linha,i);  
                    }  

                    palavra = strtok(NULL, " ~,.-!?;[]'*_—#:@$%%^&(){}\\<>/|+=1234567890\"\r\n");
                }
            
            linha++;

        }
 
    inordem(p);
    fclose(arq);
    return 0;
}