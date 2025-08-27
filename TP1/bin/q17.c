#include <stdio.h>
#include <stdlib.h>

// Função recursiva para calcular o tamanho da string
int length(const char *str) {
    if (*str == '\0') {
        return 0;
    }
    return 1 + length(str + 1);
}

// Função recursiva para inverter a palavra
void PalavraReversaRecursiva(const char *palavra, char *rev, int index) {
    if (index < 0) {
        return;
    }
    rev[index] = *palavra;
    PalavraReversaRecursiva(palavra + 1, rev, index - 1);
}

char *PalavraReversa(const char *palavra, int tamanho) {
    char *rev = (char *)malloc((tamanho + 1) * sizeof(char));
    PalavraReversaRecursiva(palavra, rev, tamanho - 1);
    rev[tamanho] = '\0';
    return rev;
}

// Função recursiva para verificar se a string é um palíndromo
const char *verificaStringRecursiva(const char *palavra, const char *palavraReversa, int index) {
    if (index < 0) {
        return "SIM";
    }
    if (palavra[index] != palavraReversa[index]) {
        return "NAO";
    }
    return verificaStringRecursiva(palavra, palavraReversa, index - 1);
}

const char *verificaString(const char *palavra, const char *palavraReversa, int tamanho) {
    return verificaStringRecursiva(palavra, palavraReversa, tamanho - 1);
}

// Função para verificar se a string é "FIM"
int EhFIM(const char *palavra, int tamanho) {
    return (tamanho == 3 && palavra[0] == 'F' && palavra[1] == 'I' && palavra[2] == 'M');
}

// Função recursiva principal
void mainRecursivo() {
    char palavra[2000];

    scanf("%[^\n]", palavra);
    getchar();

    int tamanho = length(palavra);
    char *palavraReversa = PalavraReversa(palavra, tamanho);

    if (!EhFIM(palavra, tamanho)) {
        printf("%s\n", verificaString(palavra, palavraReversa, tamanho));
        free(palavraReversa);
        mainRecursivo(); // Chamada recursiva para continuar o processo
    } else {
        free(palavraReversa);
    }
}

int main() {
    mainRecursivo();
    return 0;
}