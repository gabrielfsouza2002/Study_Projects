#include<stdio.h>
#include <stdlib.h>
#define M_comp 255
#define MAX 256

int *load_image_from_file(char *filename, int *w, int *h){

    int tamanho,valor;
    int *Imagem ;
    char line [MAX];
    int i,j;

    FILE *arq;
    arq = fopen(filename, "r");

    if (arq == NULL){
    printf("\nNao consegui abrir o arquivo %s.\n\n", filename);
    return 0;
    }

    fscanf(arq, "%s", line);
    fscanf(arq, "%d", w);
    fscanf(arq, "%d", h);

    Imagem = malloc(sizeof(int)*(*w)*(*h));
    fscanf(arq, "%d", &tamanho);

    for (i = 0; i<(*h); i++){
        for (j = 0; j<(*w); j++){
            fscanf(arq, "%d", &valor);
            Imagem [i*(*w) + j] = valor;
        } 
    }
    fclose(arq);
    return Imagem;
}

void save_image_to_file(char *filename2, int *I, int w, int h){

    int i,j;

    FILE *file;
    file = fopen(filename2, "w");
    

    if(file){

        fprintf(file, "P2\n");
        fprintf(file, "%d %d\n", w, h);
        fprintf(file, "%d\n",255);

        for(i = 0; i<h; i++){
            for(j = 0; j<w; j++){
                fprintf(file, "%d ", I[i*w + j]);
            }
            fprintf(file, "\n");
        }
         
    fclose(file);
    }
    else{
        printf("\nERRO ao executar comando arquivo!\n\n");
    }
}

int *invert_image(int *I, int w, int h){

    int *R;
    int i,j;
    R = malloc(sizeof(int)*w*h);

    for (i = 0; i<h; i++){
        for (j = 0; j<w; j++){
            R[i*w + j] = I[i*w + j];
        }
    }

    for (i = 0; i<h; i++){
        for (j = 0; j<w; j++){
            R[i*w + j] = 255 - I[i*w + j];
        }
    }
    return R;
}

int *binarize(int *I, int w, int h, int t) {

    int i,j;
    int *R;
    R = malloc(sizeof(int)*w*h);

    for (i = 0; i<h; i++){
        for (j = 0; j<w; j++){
                R[i*w + j] = I[i*w + j];
        }
    }

    for (i = 0; i<h; i++){
        for (j = 0; j<w; j++){
            if(I[i*w + j] >= t){
                R[i*w + j] = 255;
            }
            else{
                R[i*w + j] = 0;
            }
        }
    }
    return R;
    }

int *adiciona_bordas(int *I,int h,int w,int d){

    int *Imagem_BS;
    int *Imagem_BI;
    int *Imagem_BE;
    int *Imagem_BD;
    int new_h,new_w, cont, i, j;

    new_h = h + (d/2);
    new_w = w + (d/2);

    Imagem_BS = malloc(sizeof(int)*new_h*w);
    Imagem_BI = malloc(sizeof(int)*(new_h + d/2)*w);
    Imagem_BE = malloc(sizeof(int)*(new_h + d/2)*(new_w));
    Imagem_BD = malloc(sizeof(int)*(new_h* + d/2)*(new_w + d/2));

    cont = 0;
    while (cont < (d/2)){
        for (i = 0; i < w; i++){
            Imagem_BS[cont*w + i] = I[0*w +i];
        }
        cont ++;
    }
    for (i = 0; i < h; i++){
        for (j = 0; j < w; j++){
            Imagem_BS[(i+(d/2))*w + j] = I[i*w +j];
        }
    }

    for (i = 0; i < new_h; i++){
        for (j = 0; j < w; j++){
            Imagem_BI[i*w + j] = Imagem_BS[i*w +j];
        }
    }

    cont = 0;
    while (cont < (d/2)){
        for (i = 0; i < w; i++){
            Imagem_BI[(new_h+cont)*w + i] = Imagem_BS[(new_h-1)*w +i];
        }
        cont ++;
    }

    cont = 0;
    while (cont < (d/2)){
        for (i = 0; i < new_h + d/2; i++){
            Imagem_BE[i*(new_w) + cont] = Imagem_BI[i*w +0];
        }
        cont ++;
    }
    for (i = 0; i < w; i++){
        for (j = 0; j < new_h+d/2; j++){
            Imagem_BE[j*(new_w) + (i+d/2)] = Imagem_BI[j*w +i];
        }
    }

    for (i = 0; i < new_h + d/2; i++){
        for (j = 0; j < new_w; j++){
            Imagem_BD[i*(new_w + d/2) + j] = Imagem_BE[i*(new_w) +j];
        }
    }

    cont = 0;
    while (cont < (d/2)){
        for (i = 0; i < new_h + d/2; i++){
            Imagem_BD[(i)*(new_w + d/2) + (new_w+cont)] = Imagem_BE[i*(new_w) + (new_w-1)];
        }
        cont ++;
    }
    return Imagem_BD;
}

void adiciona_borda_0(int *A, int m, int n, int *B) {

    int i, j;

    for(i=0; i<m; i++) {
        for(j=0;j<n; j++) {
            B[(i+1)*(n+2) + (j+1)] = A[i*n +j] ;
        }
        B[(i+1)*(n+2)+0] = 0 ;
        B[(i+1)*(n+2)+(n+1)] = 0 ;
    }
    for(j=0; j<n+2; j++) {
        B[0 *(n+2) +j] = 0 ;
        B[(m+1)*(n+2)+j] = 0 ;
    }
}

int *filter_image(int *I, int w, int h, int d, int tipo){

    int *Imagem;
    int *I_borda;
    int *V;
    int menor, maior, mediana, cont, aux, m,n,i,j;

    if (d%2 == 0){
        printf("\nNao foi possivel filtrar a imagem. Digite um tamanho impar!\n\n");
        return 0;
    }
    if (tipo > 3){
        printf("\nTipo incorreto. Digite um tipo de 1 a 3!\n\n");
        return 0;
    }

    Imagem = malloc(sizeof(int)*h*w);
    V = malloc(sizeof(int)*(d*d));

    I_borda = adiciona_bordas(I,h,w,d);
   
    for (m =0; m<h; m++){
        for (n=0; n<w; n++){
            menor = I_borda[m*(w+d-1)+n];
            maior = I_borda[m*(w+d-1)+n];
            cont = 0;

        
            for (i = m; i<d+m; i++){
                for (j = n; j<d+n; j++){
                    V[cont] = I_borda[i*(w+d-1)+j];
                    if (I_borda[i*(w+d-1)+j] < menor){
                        menor = I_borda[i*(w+d-1)+j];
                    }
                    if (I_borda[i*(w+d-1)+j] > maior){
                        maior = I_borda[i*(w+d-1)+j];
                    }
                    cont ++;
                }
            }

            for(i=0;i<(d*d)-1;i++){
                for(j=1+i;j<(d*d);j++){
                    if(V[i] > V[j]){
                    aux = V[i];
                    V[i] = V[j];
                    V[j] = aux;
                    }
                }
            }  

            if (tipo == 1){
            Imagem[m*w+n] = menor;
            }
            else if (tipo == 2){
            mediana = V[(d*d)/2];
            Imagem[m*w+n] = mediana;
            }   
            else if (tipo == 3) {
            Imagem[m*w+n] = maior;
            }   
        }
    }

    return Imagem;
}    

int *contorno(int *I, int w, int h){
    int *I_contorno;
    int *F;
    int i,j;
    
    I_contorno = malloc (sizeof(int)*w*h);
    F = filter_image(I,w,h,3,1);

    for(i = 0; i<h; i++){
        for (j = 0; j<w; j++){
            I_contorno[i*w+j] = I[i*w+j] - F[i*w+j];
        }
    }
    return I_contorno;
}

int *label_components(int *I, int w, int h, int *ncc){
    int *Imagem;
    int *Imagem_completa;
    int *V_linha;
    int *V_coluna;
    int l = h+2;
    int c = w+2;
    int n = 0;
    int aux = 0 ;
    int cont, i, j;
    V_linha = malloc (sizeof(int)*l*c);
    V_coluna = malloc (sizeof(int)*l*c);
    Imagem = malloc(sizeof(int)*l*c);
    Imagem_completa = malloc(sizeof(int)*h*w);

    adiciona_borda_0(I,h,w,Imagem);

    for (i = 1; i<h+1; i++){
        for (j = 1; j<w+1; j++){
            if (Imagem[i*c + j] == M_comp){
                n++;
                if (n == 255){
                    n ++;
                }

                cont = 0;
                Imagem[i*c + j] = n;

                if (Imagem[(i-1)*c + j] == M_comp){
                    V_linha[cont] = i-1;
                    V_coluna[cont] = j;
                    cont ++;
                    Imagem[(i-1)*c + j] = n;
                }

                if (Imagem[(i-1)*c + (j+1)] == M_comp){
                    V_linha[cont] = i-1;
                    V_coluna[cont] = j+1;
                    cont ++;
                    Imagem[(i-1)*c + (j+1)] = n;
                }                

                if (Imagem[(i-1)*c + (j-1)] == M_comp){
                    V_linha[cont] = i-1;
                    V_coluna[cont] = j+1;
                    cont ++;
                    Imagem[(i-1)*c + (j-1)] = n;
                }
                
                if (Imagem[i*c + (j+1)] == M_comp){
                    V_linha[cont] = i;
                    V_coluna[cont] = j+1;
                    cont ++;
                    Imagem[i*c + (j+1)] = n;
                }

                if (Imagem[i*c + (j-1)] == M_comp){
                    V_linha[cont] = i;
                    V_coluna[cont] = j-1;
                    cont ++;
                    Imagem[i*c + (j-1)] = n;
                }

                if (Imagem[(i+1)*c + j] == M_comp){
                    V_linha[cont] = i+1;
                    V_coluna[cont] = j;
                    cont ++;
                    Imagem[(i+1)*c + j] = n;
                }

                if (Imagem[(i+1)*c + (j+1)] == M_comp){
                    V_linha[cont] = i+1;
                    V_coluna[cont] = j+1;
                    cont ++;
                    Imagem[(i+1)*c + (j+1)] = n;
                }

                if (Imagem[(i+1)*c + (j-1)] == M_comp){
                    V_linha[cont] = i+1;
                    V_coluna[cont] = j-1;
                    cont ++;
                    Imagem[(i+1)*c + (j-1)] = n;
                } 

        aux = 0;
        while (aux != cont && cont != 0){ 

                    if (Imagem[(V_linha[aux]-1)*c + V_coluna[aux]] == M_comp){
                        V_linha[cont] = V_linha[aux]-1;
                        V_coluna[cont] = V_coluna[aux];
                        cont ++;                     
                        Imagem[(V_linha[aux]-1)*c + V_coluna[aux]] = n;
                    }

                    if (Imagem[(V_linha[aux]-1)*c + (V_coluna[aux]+1)] == M_comp){
                        V_linha[cont] = V_linha[aux]-1;
                        V_coluna[cont] = V_coluna[aux]+1;
                        cont ++;                     
                        Imagem[(V_linha[aux]-1)*c + (V_coluna[aux]+1)] = n;
                    }

                    if (Imagem[(V_linha[aux]-1)*c + (V_coluna[aux]-1)] == M_comp){
                        V_linha[cont] = V_linha[aux]-1;
                        V_coluna[cont] = V_coluna[aux]-1;
                        cont ++;                     
                        Imagem[(V_linha[aux]-1)*c + (V_coluna[aux]-1)] = n;
                    }

                    if (Imagem[V_linha[aux]*c + (V_coluna[aux]+1)] == M_comp){
                        V_linha[cont] = V_linha[aux];
                        V_coluna[cont] = V_coluna[aux]+1;
                        cont ++;                     
                        Imagem[V_linha[aux]*c + (V_coluna[aux]+1)] = n;
                    }
                    if (Imagem[V_linha[aux]*c + (V_coluna[aux]-1)] == M_comp){
                        V_linha[cont] = V_linha[aux];
                        V_coluna[cont] = V_coluna[aux]-1;
                        cont ++; 
                        Imagem[V_linha[aux]*c + (V_coluna[aux]-1)] = n;
                    }
                    if (Imagem[(V_linha[aux]+1)*c + V_coluna[aux]] == M_comp){
                        V_linha[cont] = V_linha[aux]+1;
                        V_coluna[cont] = V_coluna[aux];
                        cont ++;                 
                        Imagem[(V_linha[aux]+1)*c + V_coluna[aux]] = n;
                    }
                    if (Imagem[(V_linha[aux]+1)*c + (V_coluna[aux]+1)] == M_comp) {
                        V_linha[cont] = V_linha[aux]+1;
                        V_coluna[cont] = V_coluna[aux]+1;
                        cont ++; 
                        Imagem[(V_linha[aux]+1)*c + (V_coluna[aux]+1)] = n;
                    }
                    
                    if (Imagem[(V_linha[aux]+1)*c + (V_coluna[aux]-1)] == M_comp){
                        V_linha[cont] = V_linha[aux]+1;
                        V_coluna[cont] = V_coluna[aux]-1;
                        cont ++; 
                        Imagem[(V_linha[aux]+1)*c + (V_coluna[aux]-1)] = n;
                    }                    
                aux ++;
                }
            }
        }
    }
    
    if (n <= 127 && n != 0){
        for (i = 1; i<h+1; i++){
            for (j = 1; j<w+1; j++){        
                Imagem[i*c + j] = Imagem[i*c + j]*(M_comp/n);
            }
        }
    }

    for(i = 0; i <h; i++){
        for (j = 0; j <w; j++){
            Imagem_completa[i*w + j] = Imagem[(i+1)*c + (j+1)];
        }
    }

    *ncc = n;
    return Imagem_completa;
}    


int main(){
    
    char filename [MAX];
    char new_filename [MAX];
    char resposta;
    int w, h, t, tipo, d, ncc;
    int *Imagem;

    printf("\n\nDigite o nome do arquivo de entrada: ");
    scanf("%s", filename);
    Imagem = load_image_from_file(filename, &w, &h);

    if(Imagem != 0){

        printf("\nq. Quit\nl. Ler um arquivo \ns. Salvar imagem em arquivo \nm. Manter entrada original \n\nb. Binarizar a imagem \nc. Contorno da imagem \ni. Inverter a imagem \nf. Filtrar a imagem \nr. Rotular os componentes conexos\n\n=====> ");
        scanf("%s", &resposta);

        while(resposta != 'q' && Imagem != 0){

            if(resposta == 's'){
                printf("Digite o nome do arquivo de saída: ");
                scanf("%s",new_filename);
                save_image_to_file(new_filename,Imagem,w,h);
                printf("\nA imagem foi Salva \n");
            }
            else if(resposta == 'm'){
                Imagem = load_image_from_file(filename, &w, &h);
                printf ("\nA imagem foi restaurada\n");
            }
            else if(resposta == 'l'){
                printf ("\nDigite o nome do novo arquivo: ");
                scanf("%s",new_filename);
                Imagem = load_image_from_file(new_filename, &w, &h);
                printf ("\nO arquivo foi carregado\n");
            }
            else if(resposta == 'b'){
                printf ("\nDigite o Limiar: ");
                scanf("%d",&t);
                Imagem = binarize(Imagem,w,h,t);
                printf ("\nA imagem foi binarizada. \n");
            }
            else if(resposta == 'c'){
                Imagem = contorno(Imagem,w,h);
                printf ("\nA imagem foi contornada. \n");
                
            }
            else if(resposta == 'i'){
                Imagem = invert_image(Imagem,w,h);
                printf ("\nA imagem foi Invertida \n");

            } 
            else if(resposta == 'f'){
                printf ("\nDigite o tipo do filtro: ");
                scanf("%d",&tipo);
                printf ("\nDigite o tamanho do filtro: ");
                scanf("%d",&d);
                Imagem = filter_image(Imagem,w,h,d,tipo);
                if (Imagem != 0){
                printf ("\nA imagem foi filtrada \n");
                }
            }
            else if(resposta == 'r'){
                Imagem = label_components(Imagem,w,h,&ncc);
                printf ("\nA imagem foi rotulada \n");
                printf ("Numero de Componetes: %d \n",ncc);
            }
            if ( Imagem != 0) {
                printf("\nq. Quit\nl. Ler um arquivo \ns. Salvar imagem em arquivo \nm. Manter entrada original \n\nb. Binarizar a imagem \nc. Contorno da imagem \ni. Inverter a imagem \nf. Filtrar a imagem \nr. Rotular os componentes conexos\n\n=====> ");
                scanf("%s", &resposta);                                              
            }
            else{
                printf ("\nVocê digitou uma letra indevida. Tente novamente.\n");
            }
        }
    }
    return 0; 
}




        







