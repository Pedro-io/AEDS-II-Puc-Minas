#include <stdio.h>
#include <stdlib.h>

// Protótipos
void Selecao(int *vetor, int n);
void Mostrar(int *vetor, int n);

int main()
{
    int vetor[] = {50, 3, 4, 5, 10};
    int n = 5;

    printf("Vetor nao ordenado: ");
    Mostrar(vetor, n);
    printf("\n");

    Selecao(vetor, n);

    printf("Vetor ordenado: ");
    Mostrar(vetor, n);
    printf("\n");

    return 0;
}

void Selecao(int *vetor, int n)
{
    int menor;
    int tmp;
    for (int i = 0; i < n -1; i++)
    {
        menor = i;
        for (int j = i + 1; j < n; j++)
        {
            if (vetor[menor] > vetor[j])
            {
                menor = j;
            }
        }
        tmp = vetor[menor];
        vetor[menor] = vetor[i];
        vetor[i] = tmp;
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
