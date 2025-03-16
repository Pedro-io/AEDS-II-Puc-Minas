#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Função recursiva para calcular o tamanho da string
int length(const char *str, int index) {
    if (str[index] == '\0') {
        return index; // Caso base: fim da string
    } else {
        return length(str, index + 1); // Chamada recursiva: incrementa o índice
    }
}

// Função recursiva para inverter a palavra
void PalavraReversaRecursivo(const char *palavra, char *rev, int tamanho, int index) {
    if (index < tamanho) {
        rev[tamanho - 1 - index] = palavra[index]; // Copia do final para o início
        PalavraReversaRecursivo(palavra, rev, tamanho, index + 1); // Chamada recursiva
    } else {
        rev[tamanho] = '\0'; // Adiciona o terminador nulo ao final
    }
}

char *PalavraReversa(const char *palavra, int tamanho) {
    char *rev = (char *)malloc((tamanho + 1) * sizeof(char));
    PalavraReversaRecursivo(palavra, rev, tamanho, 0); // Chama a função recursiva
    return rev;
}


// Função recursiva para verificar se a string é "FIM"
bool EhFIMRecursivo(const char *palavra, int tamanho, int index) {
    if (index == 0){
        return (tamanho == 3 && palavra[0] == 'F' && palavra[1] == 'I' && palavra[2] == 'M');
    }
    else{
        return false;
    }
}

bool EhFIM(const char *palavra, int tamanho) {
  return EhFIMRecursivo(palavra, tamanho,0);
}

int main() {
    char palavra[2000];

    scanf("%[^\n]", palavra);
    getchar();

    int tamanho = length(palavra, 0);
    char *palavraReversa = PalavraReversa(palavra, tamanho);

    while (!EhFIM(palavra, tamanho)) {
        printf("%s\n", palavraReversa);
        free(palavraReversa);
        scanf(" %[^\n]", palavra);
        tamanho = length(palavra, 0);
        palavraReversa = PalavraReversa(palavra, tamanho);
    }

    free(palavraReversa); // Libera a memória alocada para a última palavraReversa

    return 0;
}