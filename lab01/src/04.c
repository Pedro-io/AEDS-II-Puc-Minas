#include <stdio.h>
#include <string.h>

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

const char* verificaLinha(char *linha){

int  maiusculas = 0;
int i = 0;
    if(strcmp(linha, "FIM")){
        
        i += 1;
        maiusculas = 0; 
        maiusculas = contarMaiusculos(verificaLinha(linha));
        printf("%d\n", maiusculas);

    }


return linha; 

}

int main()
{

char linha[100];
scanf("[^ \n]", linha);

verificaLinha(linha);

    return 0;
}


