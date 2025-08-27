#include <stdio.h>
#include <stdbool.h>

// Função para verificar se a string é "FIM"
bool EhFIM(char entrada[]) {
    return (entrada[0] == 'F' && entrada[1] == 'I' && entrada[2] == 'M' && entrada[3] == '\0');
}

// Função recursiva para somar os dígitos de uma string
int somaRecursiva(char entrada[], int tamanho) {
    if (tamanho == 0) {
        return 0; // Caso base: não há mais dígitos para somar
    } else {
        // Converte o último caractere para um dígito e soma recursivamente
        int ultimoDigito = entrada[tamanho - 1] - '0'; // Converte char para int
        return ultimoDigito + somaRecursiva(entrada, tamanho - 1);
    }
}

int main() {
    char entrada[1000]; // Tamanho máximo da entrada
    
    // Loop para ler as entradas até encontrar "FIM"
    while (1) {
        scanf("%s", entrada); // Lê uma string da entrada padrão

        if (EhFIM(entrada)) {
            break; // Sai do loop se a entrada for "FIM"
        }

        // Calcula a soma dos dígitos e imprime
        int tamanho = 0;
        while (entrada[tamanho] != '\0') {
            tamanho++; // Calcula o tamanho da string
        }
        int resultado = somaRecursiva(entrada, tamanho);
        printf("%d\n", resultado);
    }

    return 0;
}