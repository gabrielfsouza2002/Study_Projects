#include <stdio.h>
#include "pilha.c"

/* NOME: Gabriel Ferreira de Souza Araujo  NUSP:12719100 */

/*Essa funcao pega da lista de palavras, a palvra a ser colocada no tabuleiro de acordo com os requisitos dados*/
int pega(int n_palavras,char palavras[n_palavras][256], int verifica[], char palavra[], char requesito[],int tamanho_requisito, int cont_space, int *ordem, int *ordem_i){ 

    int i, j, k, flag1, flag2;
    printf("\n");
    printf("\n");
    flag2=1;
    for(i=*ordem_i; i<n_palavras && flag2==1 ; i++){
        flag1=1;
        if(verifica[i]==1){
            continue;
        }
        for(k=0;k<tamanho_requisito;k++){
            if(requesito[k]=='0'){     
                continue;
            }
            if (!(requesito[k]==palavras[i][k])){
                flag1=0;
                break;
            }
        }

        for(j=0; palavras[i][j]!='\0' && flag1==1 && j<cont_space; j++){
            if(j==cont_space-1 && palavras[i][j+1]=='\0' && flag1==1){
                verifica[i]=1;
                *ordem = i;
                for (k=0; palavras[i][k]!='\0' ;k++){
                palavra[k] = palavras[i][k];
               
                printf("%c",palavra[k]);
                }
                flag1=0;
                flag2=0;
            }
        }
    }
    if(palavra[0]=='\0'){ /*retorna sem tem uma palavra a ser colocada ou não*/
        return 0;
    }
    return 1;
}


/*Maior entre dois números*/
int maior(int a, int b){
    if(a>b) return a;
    else  return b;
}
/*Imprime o Tabuleiro*/
void imprime(int linhas, int colunas, char matriz[linhas][colunas]){
    int i,j;
    printf("\n");
    for (i=0; i<linhas; i++){
        printf("\n");
        for(j=0; j<colunas; j++){
            printf("%c ",matriz[i][j]);
        }
    }
}
/*Preenche o requesito com '0'*/
void zera_requesito(int tamanho, char vetor[]){
    int i;
    for(i=0; i<tamanho; i++)
        vetor[i]='0';    
}
/*Preenche a palavra com '\0'*/
void zera_palavra(int tamanho, char palavra[]){
    int i;
    for(i=0; i<tamanho; i++)  
        palavra[i] = '\0';
}
/*Essa funcao retorna qual a posicao de uma palavra em relacao a sua coluna. Assim, ela retorna o numero de '*' entre a palavra e conta o final da palavra caso o final nao seja '*'. Exemplo: *palavra** ->3  ***palavra ->4  **palavra*** ->5*/
int posicao_col(int linhas, int colunas, char tabuleiro[linhas][colunas], int linha, int coluna){
    int i, cont;
    cont=0;
        for (i=linha-1; i!=-1 ;i--){
            if(tabuleiro[i][coluna] =='*')
                cont++;
        }
        for (i=linha; i<linhas ;i++){
            if(tabuleiro[i][coluna] =='*'){
                cont++;
                break;
            }
            if(tabuleiro[i][coluna]!='\0'){
                cont++;
                break;
            }
        }
    return cont;

}
/*Essa funcao é analoga a anterior, porém em relação a linha.*/
int posicao_lin(int linhas, int colunas, char tabuleiro[linhas][colunas], int linha ,int coluna){
    int i, cont;
    cont=0;
        for (i=coluna-1; i!=-1; i--){
            if(tabuleiro[linha][i] =='*')
                cont++;
        }
        for (i=coluna; i<colunas+1; i++){
            if(tabuleiro[linha][i] =='*'){
                cont++;
                break;
            }
        }
    return cont;

}
int tabuleiro_impossivel(int verifica[], int n_verifica){
    int i;
    for(i=0; verifica[i]<n_verifica; i++){
        if(verifica[i]==1)
            return 0;
    }
    return 1;
}   

int main(){

    int i, j, k, linhas, colunas, valor_no_tabuleiro, n_palavras;

    scanf("%d",&linhas);
    scanf("%d",&colunas);
    char tabuleiro [linhas][colunas];
    /*Criando tabuleiro*/
    for(i = 0; i<linhas; i++){
        for(j = 0; j<colunas; j++){
            scanf("%d",&valor_no_tabuleiro);
            if (valor_no_tabuleiro == -1)
                tabuleiro[i][j] = '*';
            else
                tabuleiro[i][j] = '0';   
        }
    }
    scanf("%d",&n_palavras);
    int tamanho = maior(linhas,colunas);
    char palavras [n_palavras][256];
    char palavra [tamanho];
    int verifica[n_palavras];
    
    for(i=0; i<n_palavras ; i++){
        verifica[i] = 0;
        scanf("%s",palavras[i]);
    }

    pilha * guarda_coordenada_lin = cria();
    pilha * guarda_coordenada_col = cria();
    pilha * guarda_direcao = cria();
    pilha * guarda_ordem = cria();

    int cont_space_line, cont_space_col, pega_palavra;
    char requesito[tamanho];
    int cont_1,cont_2,cont_3,cont_4;
    int flag1, flag2, flag3, flag4;
    int aux1,aux2,aux3,aux4;
    int ordem,ordem_i; /*Ordem na lista da palavra escolhida antes do backtraking e depois do backtraking (ordem_i)*/
    int confere_coluna[colunas][linhas]; /*Confere se uma posicao da coluna ja foi visitada*/
    int confere_linha [colunas][linhas]; /*Confere se uma posicao da linha ja foi visitada*/
    int backtraking=0; /*Estamos ou nao fazendo backtraking*/
    int ordem_desempilhada, direcao, primeira_col_verificada, lin, col, posicao_desempilhada, posicao, guarda_linha_i;
    ordem_i=0;
    aux1=0;
    aux2=0;
    aux3=0;
    flag2=1;
    flag3=1;
    /*iremos percorrer todas as linhas. Assim, preecheremos com palavras primeiramente as linhas e depois as colunas de acordo com seus requesitos*/
    for(i=aux1; i<linhas;i++){
        zera_requesito(tamanho, requesito);
        cont_space_line=0;     
        cont_3=0;   
        flag3=1;
        flag4=1;
        if(backtraking==0){
        aux3=0;
        aux4=i;
        }
        if(!flag2)
            i=aux1;
        for(j=aux2,cont_1=0,cont_4=0;j<colunas+1 && flag2;j++){     
            if(tabuleiro[i][j]=='*'){
                cont_4=0; 
                cont_1=j;
                flag3=1;
            }
            if(tabuleiro[i][j]!='*' && flag3){
                primeira_col_verificada=j;
                flag3=0;
            }
            if(tabuleiro[i][j]=='*' && j==0){
                cont_space_line=0;
                continue;
            }        
            else if(tabuleiro[i][j]=='*' && cont_space_line<2){
                cont_space_line=0;
                cont_3=cont_1+1;
                continue;
            } 
            else if (tabuleiro[i][j]!='*' && j!=colunas){
                cont_space_line++;
                requesito[cont_4] = tabuleiro[i][j];
                cont_4++;
            }
            else if ((j==colunas || tabuleiro[i][j]=='*') && cont_space_line>1){    
                posicao = posicao_lin(linhas, colunas, tabuleiro, i, j);
                zera_palavra(tamanho, palavra);
                pega_palavra = pega(n_palavras, palavras, verifica, palavra, requesito, tamanho, cont_space_line,&ordem, &ordem_i); /*Nos dara uma palavra a ser colocada*/
                ordem_i=0;
                backtraking=0;
                if (tabuleiro_impossivel(verifica,n_palavras)){
                    printf("Não Há Solução");
                    printf("\n");
                    return 0;
                }
                /*BACKTRAKING*/
                if (pega_palavra==0){
                    int h;
                    backtraking=1;
                    ordem_desempilhada = desempilha(guarda_ordem);
                    direcao = desempilha(guarda_direcao); /*direcao 0 se linha e 1 se coluna*/
                    lin = desempilha(guarda_coordenada_lin);
                    col = desempilha(guarda_coordenada_col);
                    verifica[ordem_desempilhada]=0;
                    if(direcao==0){
                        for(h = col; h<colunas && tabuleiro[lin][h]!='*'; h++){
                            posicao_desempilhada = posicao_col(linhas,colunas,tabuleiro,lin,h);
                            if(confere_coluna[col][posicao_desempilhada]!=1 || lin==0)
                                tabuleiro[lin][h] = '0';
                        }imprime(linhas,colunas,tabuleiro); 
                        i = lin-1;
                        aux2 = col-1;
                        ordem_i = ordem_desempilhada+1;
                        posicao_desempilhada = posicao_lin(linhas,colunas,tabuleiro,lin,col);
                        confere_linha[lin][posicao_desempilhada] = 0;
                        flag4=0;
                        break;
                    }else{
                        for(h = lin; h<colunas && tabuleiro[h][col]!='*'; h++){
                            posicao_desempilhada = posicao_lin(linhas,colunas,tabuleiro,h,col);
                            if(confere_linha[h][posicao_desempilhada]!=1)
                                tabuleiro[h][col] = '0';
                        }
                        imprime(linhas,colunas,tabuleiro);                         
                        aux3= col;
                        aux4= lin;
                        ordem_i=ordem_desempilhada+1;
                        flag2=0;
                        posicao_desempilhada=posicao_col(linhas,colunas,tabuleiro,lin,col);     
                        confere_coluna[col][posicao_desempilhada] = 0;  
                        break;
                    }
                } 
                empilha(guarda_coordenada_lin,i);
                empilha(guarda_coordenada_col,primeira_col_verificada);
                empilha(guarda_ordem,ordem);
                empilha(guarda_direcao,0);
                zera_requesito(tamanho,requesito);
                aux2=0;
                confere_linha[i][posicao]=1;                 
                cont_space_line=0;  
                /*Transcreve no tabuleiro*/
                if( tabuleiro[i][0]=='*'){
                    flag1=1;
                }
                for(k=cont_3, cont_2=0; k<colunas && (tabuleiro[i][k]!='*' || flag1) && palavra[0]!='\0'; k++){
                    if (tabuleiro[i][k]=='*'){
                        flag1=0;
                        continue;
                    }else{
                        tabuleiro[i][k] = palavra[cont_2];
                        cont_2++;
                    }                     
                }imprime(linhas,colunas,tabuleiro);
                cont_3=cont_1;       
            }
        }/*Aqui vamos percorrer as colunas e preeche-las com as palavras da lista*/
        for(j=aux3; j<colunas && (aux3!=linhas-1 || backtraking) && flag4; j++){ 
            zera_requesito(colunas,requesito);
            zera_palavra(tamanho,palavra);
            flag2=1;
            cont_space_col=0;
            guarda_linha_i=i;
            posicao=0;
            for(k = aux4; k<linhas; k++){
                if(tabuleiro[k][j] == '*'){
                    posicao=k;
                    break;
                }
                else{
                    requesito[k-aux4] = tabuleiro[k][j];
                    cont_space_col++;
                    posicao=k;                    
                } 
            }
            posicao = posicao_col(linhas,colunas,tabuleiro,i,j);
            if(cont_space_col>1 && (confere_coluna[j][posicao]!=1 || backtraking)){
                zera_palavra(tamanho,palavra);
                pega_palavra = pega(n_palavras,palavras,verifica,palavra, requesito,tamanho, cont_space_col,&ordem,&ordem_i);
                backtraking=0;
                ordem_i=0;
                /*BACKTRAKING*/
                if (pega_palavra==0){
                    int h;
                    backtraking=1;
                    ordem_desempilhada = desempilha(guarda_ordem);
                    direcao = desempilha(guarda_direcao);
                    lin = desempilha(guarda_coordenada_lin);
                    col = desempilha(guarda_coordenada_col);
                    verifica[ordem_desempilhada]=0;
                
                    if(direcao==0){

                        for(h =col; h<colunas && tabuleiro[lin][h]!='*'; h++){
                            posicao_desempilhada = posicao_col(linhas,colunas,tabuleiro,lin,h);
                            if(confere_coluna[h][posicao_desempilhada]!=1 || lin==0)
                                tabuleiro[lin][h] = '0';
                                
                        }imprime(linhas,colunas,tabuleiro);
                        posicao_desempilhada=posicao_col(linhas,colunas,tabuleiro,lin,col);
                        confere_coluna[col][posicao_desempilhada] = 0;                         
                        posicao_desempilhada=posicao_lin(linhas,colunas,tabuleiro,lin,col);
                        confere_linha[lin][posicao_desempilhada] = 0;
                        i = lin-1;
                        aux2 = col-1;
                        ordem_i=ordem_desempilhada+1;
                        break;;
                    }else{
                        for(h = lin; h<colunas && tabuleiro[h][col]!='*'; h++){
                            posicao_desempilhada = posicao_lin(linhas,colunas,tabuleiro,h,col);
                            if(confere_linha[h][posicao_desempilhada]!=1)
                                tabuleiro[h][col] = '0';
                        }imprime(linhas,colunas,tabuleiro);

                        posicao_desempilhada = posicao_col(linhas,colunas,tabuleiro,lin,col);     
                        confere_coluna[col][posicao_desempilhada] = 0;                    
                        aux3= col;
                        aux4= lin;
                        ordem_i=ordem_desempilhada+1;
                        flag2=0;
                        break;
                    }
                }  
                empilha(guarda_coordenada_lin,i);
                empilha(guarda_coordenada_col,j);
                empilha(guarda_ordem,ordem);
                empilha(guarda_direcao,1);
                confere_coluna[j][posicao]= 1; 
            }
                /*Transcreve no tabuleiro*/
                flag1=0;
                for(k=i,guarda_linha_i=i,cont_2=0; (tabuleiro[k][j]!='*' || k==guarda_linha_i) && palavra[0]!='\0' && tabuleiro[k][j]!='\0';k++){
                    tabuleiro[k][j] = palavra[cont_2];
                    cont_2++;    
                }imprime(linhas,colunas,tabuleiro);            
        } 
    }             
             
return 0;
}        

/*Alguns testes:

5 4
-1 0 0 -1
0 0 0 0
0 0 -1 0
0 0 0 0
0 -1 0 0
10
ad
ntas
soda
carn
casa
do
lado
ur
lu
os


3 3
-1 0 0
0 0 0
0 -1 0
5
ab
au
bug
la
lua


5 5             
-1 -1 0 0 -1
0 0 0 0 0
0 0 -1 0 -1
0 0 0 0 0
0 -1 0 0 0
10
ua
casa
ado
ur
antas
carno
ad
sodap
dp 
pss


6 9
-1 0 0 0 0 -1 0 0 -1
-1 0 0 0 0 0 0 0 0 
0 0 0 0 0 -1 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 -1 0 0 0 0
0 0 -1 -1 -1 0 0 0 -1
19
casa
mo
ttpd
comida
atrai
sitar
amar
maninh
otavin
aore
otimoata
tmrta
tiaaraivr
ari
nao
pdir
rnie
da
ihn


5 5             
-1 -1 0 0 -1
0 0 0 0 0
0 0 -1 0 -1
0 0 0 0 0
-1 -1 0 0 0
10
ua
cas
ado
ur
antas
carno
ad
pa
sodap
esa


5 5             
-1 -1 0 0 -1
0 0 0 0 0
0 0 -1 0 -1
0 0 0 0 0
-1 -1 0 0 0
9
ua
ado
ur
antas
carno
ad
pa
sodap
esa

*/
