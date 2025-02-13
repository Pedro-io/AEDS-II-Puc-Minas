#include <stdio.h>

int main()
{
    char palavra[100]; 

    scanf("%s", palavra);
    
    while(palavra != "FIM")
    {

    }

    return 0;
}

char PalavraReversa(char *palavra) {
    /* 
            função para reverter a palavra
            parametros: 
            String palavra: string de entrada do usuário que vai ser revertida

            return : String com o reverso da entrada
       */     

    char palavraReversa[100] = ""; // declara uma variavel String vazia para inserir a palavra reversa 
    for (int i = palavra - 1 ; i >= 0; i--) { // para cada caracter da palavra de tamanho n 
        palavraReversa += palavra.charAt(i);// insira na posição n(i) da palavra reversa  
    }

    return palavraReversa;// retorna a palavra 
}
