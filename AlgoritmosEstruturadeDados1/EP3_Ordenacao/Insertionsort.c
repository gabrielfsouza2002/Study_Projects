#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insertionSort(char** v, int n) {

    char *x;
    x = malloc (10* sizeof(char));
    int i, j;
    for(i = 1; i < n; i++) {
        x = v[i];
        j = i - 1;
        while(j >= 0 && (strcmp(v[j],x))>0) {
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = x;
        free(x)
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