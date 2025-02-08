#include <stdio.h>
#include <string.h>  // Para usar strcmp e strcspn

// Função para contar caracteres maiúsculos
int contarMaiusculos(char *str) {
    int count = 0;  // Contador de maiúsculos
    int i = 0;      // Índice para percorrer a string

    // Percorre a string até encontrar o caractere nulo (\0)
    while (str[i] != '\0') {
        // Verifica se o caractere atual é maiúsculo (A-Z na tabela ASCII)
        if (str[i] >= 'A' && str[i] <= 'Z') {
            count++;  // Incrementa o contador
        }
        i++;  // Avança para o próximo caractere
    }

    return count;  // Retorna o total de maiúsculos
}

int main() {
    char linha[100];  // Buffer para armazenar cada linha de entrada

    // Loop infinito para ler várias linhas
    while (1) {
        // Lê uma linha da entrada padrão
        fgets(linha, sizeof(linha), stdin);

        // Remove o caractere de nova linha (\n) no final da string
        linha[strcspn(linha, "\n")] = '\0';

        // Verifica se a linha é "FIM" para encerrar o programa
        if (strcmp(linha, "FIM") == 0) {
            break;
        }

        // Chama a função para contar maiúsculos e imprime o resultado
        int maiusculos = contarMaiusculos(linha);
        printf("%d\n", maiusculos);
    }

    return 0;
}