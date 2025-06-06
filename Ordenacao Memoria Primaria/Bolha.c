#include <stdio.h>
#include <stdlib.h>

// Protótipos
void Bolha(int* vetor, int n);
void Mostrar(int* vetor, int n);

int main(){
    int vetor[] = {50, 3, 4, 5, 10};
    int n = 5;

    printf("Vetor nao ordenado: ");
    Mostrar(vetor, n);
    printf("\n");

    Bolha(vetor, n);

    printf("Vetor ordenado: ");
    Mostrar(vetor, n);
    printf("\n");

    return 0;
}

void Bolha(int* vetor, int n){
    int tmp;
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - 1 - i; j++){
            if(vetor[j] > vetor[j + 1]){
                tmp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = tmp;
            }
        }
    }
}

void Mostrar(int* vetor, int n){
    printf("[");
    for(int i = 0; i < n; i++){
        printf("%d", vetor[i]);
        if (i < n - 1) printf(", ");
    }
    printf("]");
}
