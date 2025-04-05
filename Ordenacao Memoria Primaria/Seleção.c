#include <stdio.h>
#include <stdlib.h> 

void selecao(int* entrada, int n){
    int temp;

    for(int i = 0; i < (n-1); i++){
        int menor = i; 
        for(int j = (i+1); j < n; j++){
            if(entrada[menor] > entrada[j]){
                menor = j;
            }
        } 

        temp = entrada[i];
        entrada[i] = entrada[menor];
        entrada[menor] = temp;
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

    selecao(vetor, n);

    printf("Este eh o seu vetor ordenado: ");
    for(int i = 0; i < n; i++){
        if(i < n - 1)
            printf("%d, ", vetor[i]);
        else
            printf("%d.\n", vetor[i]);
    }
}
