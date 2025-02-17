#include <stdio.h>
#include <stdbool.h> 

int length(char *str) {
    int length = 0;
    while (str[length] != "\0") {
      length++;
    }
    return length;
  }

char PalavraReversa(const char *palavra) {
    /* 
            função para reverter a palavra
            parametros: 
            String palavra: string de entrada do usuário que vai ser revertida

            return : String com o reverso da entrada
       */     

    char palavraReversa[100] = ""; // declara uma variavel String vazia para inserir a palavra reversa 
    for (int i = palavra - 1 ; i >= 0; i--) { // para cada caracter da palavra de tamanho n 
        palavraReversa[i] = palavra[i];// insira na posição n(i) da palavra reversa  
    }

    return palavraReversa;// retorna a palavra 
}

char VerificaString(const char *str1, const char *str2) {
    
  int i = 0;
  
    // Loop enquanto ambos os caracteres forem iguais e não chegarmos ao final de nenhuma string
    while (str1[i] != '\0' && str2[i] != '\0') {
      if (str1[i] != str2[i]) {
        return false; // Caracteres diferentes, strings não são iguais
      }
      i++;
    }
  
    // Verifica se ambas as strings terminaram ao mesmo tempo
    // Se uma string terminou antes da outra, elas são diferentes
    if (str1[i] != '\0' || str2[i] != '\0') {
      return false; // Uma string é mais longa que a outra
    }
  
    return true; // Todas os caracteres foram iguais e ambas as strings terminaram ao mesmo tempo
  }


int main()
{
    char palavra[100]; 
    

    scanf("%[^\n]", palavra);

    int tamanho = length(palavra);
    
    printf(tamanho);

    return 0;
}


