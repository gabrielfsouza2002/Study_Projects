#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void quickSort(char** vet, int inicio, int fim) { 

	if(inicio < fim){ 
        char *pivot;
        pivot = malloc (10* sizeof(char));
		pivot = vet[inicio]; 
        char *temp;
        temp = malloc (10* sizeof(char));
	
		int i = inicio;
		int f = fim;
		while (1){
			while(strcmp(pivot,vet[f]) <0){  
				f--;
			}
			while(strcmp(pivot,vet[i]) >0){
				i++;
			}
			if (i >= f){
				break;
			}
			temp = vet[i];
			vet[i] = vet[f];
			vet[f] = temp;
		}
		quickSort(vet, inicio, f);  
		quickSort(vet, f +1, fim);
		free(pivot);
		free(temp);
	}
}

int main(){
    char** matrix = (char**)malloc(10*sizeof(char*));
    matrix[0] = "casa";
    matrix[1] = "aba";
    matrix[2] = "boi";
    matrix[3] = "dad";
    matrix[4] = "dO";
    matrix[5] = "mA";
    quickSort(matrix, 0, 6-1);
    printf("%s %s %s %s %s %s",matrix[0],matrix[1],matrix[2],matrix[3],matrix[4],matrix[5]);
	free(matrix);
	return 0;
}