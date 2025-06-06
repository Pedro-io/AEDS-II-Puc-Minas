#include <stdio.h>
#include <stdlib.h>

// Protótipos
void Insercao(int *vetor, int n);
void Mostrar(int *vetor, int n);

int main()
{
    int vetor[] = {50, 3, 4, 5, 10};
    int n = 5;

    printf("Vetor nao ordenado: ");
    Mostrar(vetor, n);
    printf("\n");

    Insercao(vetor, n);

    printf("Vetor ordenado: ");
    Mostrar(vetor, n);
    printf("\n");

    return 0;
}

void Insercao(int *vetor, int n)
{
    int tmp, j;
    for(int i = 1; i < n; i++){
        tmp = vetor[i];
        j = i - 1;

        while ((j >= 0) && (vetor[j] > tmp) ){
            vetor[j +1] = vetor[j];
            j--;
        }
        vetor[j+1] = tmp;
        
    } 

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
