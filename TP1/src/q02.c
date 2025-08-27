#include <stdio.h>
#include <stdlib.h>


int length(const char *str, int tam)
{
  if (str[tam] == '\0') {
    return tam;
  }
  return length(str, tam + 1);
}

void montaReversa(const char *palavra, char *rev, int i, int tamanho)
{
  if (i == tamanho) {
    rev[tamanho] = '\0';
    return;
  }
  rev[i] = palavra[tamanho - 1 - i];
  montaReversa(palavra, rev, i + 1, tamanho);
}

char *PalavraReversa(const char *palavra, int tamanho)
{
  char *rev = (char *)malloc((tamanho + 1) * sizeof(char));
  if (rev == NULL) {
    return NULL; 
  }
  montaReversa(palavra, rev, 0, tamanho);
  return rev;
}

const char *comparaRec(const char *a, const char *b, int i, int tamanho)
{
  if (i == tamanho) {
    return "SIM";
  }
  if (a[i] != b[i]) {
    return "NAO";
  }
  return comparaRec(a, b, i + 1, tamanho);
}

const char *verificaString(const char *palavra, const char *palavraReversa, int tamanho)
{
  return comparaRec(palavra, palavraReversa, 0, tamanho);
}

int EhFIM(const char *palavra, int tamanho)
{
  return (tamanho == 3 && palavra[0] == 'F' && palavra[1] == 'I' && palavra[2] == 'M');
}

int main()
{
  char palavra[2000];
  scanf("%[^\n]", palavra);
  getchar(); 

  int tamanho = 0;
  tamanho = length(palavra, tamanho);
  char *palavraReversa = PalavraReversa(palavra, tamanho);

  while (!EhFIM(palavra, tamanho))
  {
    printf("%s\n", verificaString(palavra, palavraReversa, tamanho));
    free(palavraReversa);
    scanf(" %[^\n]", palavra);
    tamanho = 0;
    tamanho = length(palavra, tamanho);
    palavraReversa = PalavraReversa(palavra, tamanho);
  }
  free(palavraReversa);

  return 0;
}
