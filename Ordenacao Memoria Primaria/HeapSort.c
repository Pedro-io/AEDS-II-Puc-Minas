#include <stdio.h>
#include <stdlib.h>

// Protótipos
void heapsort(int *vetor, int n);
void heapify(int *vetor, int n, int i);
void Mostrar(int *vetor, int n);

int main() {
    int vetor[] = {50, 3, 4, 5, 10};
    int n = 5;

    printf("Vetor nao ordenado: ");
    Mostrar(vetor, n);
    printf("\n");

    heapsort(vetor, n);

    printf("Vetor ordenado: ");
    Mostrar(vetor, n);
    printf("\n");

    return 0;
}


// Função principal do Heap Sort
void heapsort(int *vetor, int n) {
    // Constrói o heap (reorganiza o vetor)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(vetor, n, i);
    }

    // Extrai os elementos um por um do heap
    for (int i = n - 1; i >= 0; i--) {
        // Move o maior elemento (raiz) para o fim
        int tmp = vetor[0];
        vetor[0] = vetor[i];
        vetor[i] = tmp;

        // Chama heapify na raiz para manter a propriedade de heap
        heapify(vetor, i, 0);
    }
}


// Garante a propriedade de heap máximo a partir do índice i
void heapify(int *vetor, int n, int i) {
    int maior = i;         // Inicialmente assume que a raiz é o maior
    int esq = 2 * i + 1;   // Índice do filho da esquerda
    int dir = 2 * i + 2;   // Índice do filho da direita

    // Se o filho da esquerda for maior que o pai
    if (esq < n && vetor[esq] > vetor[maior])
        maior = esq;

    // Se o filho da direita for maior que o maior até agora
    if (dir < n && vetor[dir] > vetor[maior])
        maior = dir;

    // Se o maior não for a raiz, troca e continua o processo recursivamente
    if (maior != i) {
        int tmp = vetor[i];
        vetor[i] = vetor[maior];
        vetor[maior] = tmp;

        heapify(vetor, n, maior);  // Chama recursivamente
    }
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
