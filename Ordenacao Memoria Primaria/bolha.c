#include <stdio.h>
#include <stdlib.h>

void bolha(int *vet, int n)
{

    int menor, tmp;

    for (int i = 0; i < (n - 1); i++)
    {
        menor = i;
        for (int j = i + 1; j < n; j++)
        {
            if (vet[i] > vet[j])
            {
                tmp = vet[i];
                vet[i] = vet[j];
                vet[j] = tmp;
            }
        }
    }
}

int main()
{
    int vetor[6] = {1, 5, 10, 24, 2, 88};
    int n = 6;

    printf("--------------------------------------------------------------\n");
    printf("Fala cabaco, esse aqui eh seu vetor sem ordenar: ");
    for (int i = 0; i < n; i++)
    {
        if (i < n - 1)
            printf("%d, ", vetor[i]);
        else
            printf("%d.\n", vetor[i]);
    }

    bolha(vetor, n);

    printf("Este eh o seu vetor ordenado: ");
    for (int i = 0; i < n; i++)
    {
        if (i < n - 1)
            printf("%d, ", vetor[i]);
        else
            printf("%d.\n", vetor[i]);
    }
}