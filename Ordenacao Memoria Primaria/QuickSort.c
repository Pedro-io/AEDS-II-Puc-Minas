#include <stdio.h>
#include <stdlib.h>

// Protótipos
void quicksort(int *vetor, int esq, int dir);
void Mostrar(int *vetor, int n);

int main()
{
    int vetor[] = {50, 3, 4, 5, 10};
    int n = 5;

    printf("Vetor nao ordenado: ");
    Mostrar(vetor, n);
    printf("\n");

    quicksort(vetor, 0, n-1);

    printf("Vetor ordenado: ");
    Mostrar(vetor, n);
    printf("\n");

    return 0;
}

void quicksort(int *vetor, int esq, int dir)
{
    int i = esq, j = dir, pivo = vetor[(esq + dir) / 2];
    
    while(i <= j){
        while (vetor[i] < pivo) i++;
        while (vetor[j] > pivo) j--;

        if(i <= j){
            swap(vetor, i, j);
            i++;
            j--; 
        }
    }
    
    if(esq < j){
        quicksort(vetor, esq, j);
    }

    if(i < dir){
        quicksort(vetor, i, dir); 
    }
}


void swap(int* vetor, int pos1, int pos2){
    int tmp;
    tmp = vetor[pos1];
    vetor[pos1] = vetor[pos2];
    vetor[pos2] = tmp;
}


void Mostrar(int *vetor, int n)
{
    printf("[");
    for (int i = 0; i < n; i++)
    {
        printf("%d", vetor[i]);
        if (i < n - 1)
            printf(", ");
    }
    printf("]");
}
