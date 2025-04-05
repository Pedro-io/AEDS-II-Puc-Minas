#include <stdio.h> 
#include <stdlib.h> 

void insercao(int* vet, int n){
    int tmp, j;

    for(int i = 1; i < n ; i ++)
    {
        tmp = vet[i];
        j = i-1;

        while((j >= 0) && (vet[j] > tmp) )
    }
}


int main(){
    int vetor[6] = {1, 5, 10, 24, 2, 88};
    int n = 6;

    printf("--------------------------------------------------------------\n");
    printf("Fala cabaco, esse aqui eh seu vetor sem ordenar: ");
    for(int i = 0; i < n; i++){
        if(i < n - 1)
            printf("%d, ", vetor[i]);
        else
            printf("%d.\n", vetor[i]);
    }

    insercao(vetor, n);

    printf("Este eh o seu vetor ordenado: ");
    for(int i = 0; i < n; i++){
        if(i < n - 1)
            printf("%d, ", vetor[i]);
        else
            printf("%d.\n", vetor[i]);
    }
}