#include <stdio.h>
#include <stdlib.h>

int length(const char *str) {
    int length = 0;
    while (str[length] != '\0') {
      length++;
    }
    return length;
  }

char* PalavraReversa(const char *palavra, int tamanho){
  
  char *rev = (char*)malloc((tamanho + 1) * sizeof(char));


  for(int i = tamanho - 1, j = 0; i >= 0; i--, j++){
        
    rev[j] = palavra[i];
  }

  rev[tamanho] = '\0'; 

  return rev;
}


const char* VerificaString(const char* palavra, const char* palavraReversa, int tamanho) {
  /* Função para verificar se é um palindrono ou não 
   * parametros: 
   *  String palavra: palavra inserida pelo o usuario 
   *  String palavraReversa: o reverso da palavra inserida pelo usuario 
   * 
   * return : "SIM" ou "NÃO"
   */

  for (int i = 0; i < tamanho; i++){
      if (palavra[i] != palavraReversa[i]) {
          return "NAO"; // Se encontrar uma diferença, não é palíndromo
      }
  }

  return "SIM"; // Se chegou até aqui, todos os caracteres corresponderam, é palíndromo


}

int EhFIM(const char *palavra, int tamanho) {
  return (tamanho == 3 && palavra[0] == 'F' && palavra[1] == 'I' && palavra[2] == 'M');
}



int main()
{
    char palavra[200]; 
    
    scanf("%[^\n]", palavra);
    getchar();

    int tamanho = length(palavra);

    char* palavraReversa = PalavraReversa(palavra, tamanho);
    
    
    while (!EhFIM(palavra, tamanho))
    {
      
      printf("%s\n", VerificaString(palavra, palavraReversa, tamanho));

      scanf("%[^\n]", palavra);
      getchar();
      tamanho = length(palavra);


      palavraReversa = PalavraReversa(palavra, tamanho);
    }

    free(palavraReversa);
    

    return 0;
}

