#include <stdio.h>
#include <stdlib.h>

// Protótipos
void mergesort(int *vetor, int inicio, int fim);
void merge(int *vetor, int inicio, int meio, int fim);
void Mostrar(int *vetor, int n);

int main() {
    int vetor[] = {50, 3, 4, 5, 10};
    int n = 5;

    printf("Vetor nao ordenado: ");
    Mostrar(vetor, n);
    printf("\n");

    mergesort(vetor, 0, n - 1);

    printf("Vetor ordenado: ");
    Mostrar(vetor, n);
    printf("\n");

    return 0;
}

void mergesort(int *vetor, int inicio, int fim) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;

        mergesort(vetor, inicio, meio);
        mergesort(vetor, meio + 1, fim);
        merge(vetor, inicio, meio, fim);
    }
}

void merge(int *vetor, int inicio, int meio, int fim) {
    // Calcula o tamanho dos dois subvetores
    int n1 = meio - inicio + 1;
    int n2 = fim - meio;

    // Cria vetores auxiliares para armazenar as metades
    int *L = (int *)malloc(n1 * sizeof(int));
    int *R = (int *)malloc(n2 * sizeof(int));

    // Copia os elementos da metade esquerda para L[]
    for (int i = 0; i < n1; i++)
        L[i] = vetor[inicio + i];

    // Copia os elementos da metade direita para R[]
    for (int j = 0; j < n2; j++)
        R[j] = vetor[meio + 1 + j];

    // Índices iniciais de L[], R[] e vetor original
    int i = 0;         // índice para L[]
    int j = 0;         // índice para R[]
    int k = inicio;    // índice para vetor original

    // Junta os dois vetores auxiliares de forma ordenada
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            vetor[k] = L[i];  // coloca L[i] no vetor original
            i++;
        } else {
            vetor[k] = R[j];  // coloca R[j] no vetor original
            j++;
        }
        k++;  // avança para o próximo índice do vetor original
    }

    // Copia os elementos restantes de L[], se houver
    while (i < n1) {
        vetor[k] = L[i];
        i++;
        k++;
    }

    // Copia os elementos restantes de R[], se houver
    while (j < n2) {
        vetor[k] = R[j];
        j++;
        k++;
    }

    // Libera a memória alocada para os vetores auxiliares
    free(L);
    free(R);
}

void Mostrar(int *vetor, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%d", vetor[i]);
        if (i < n - 1)
            printf(", ");
    }
    printf("]");
}
