# include <stdio.h>

void processarRegistro(int id, double preco, char* tempo, char* cidade) {
  printf("Registro lido: %d %.2f %s %s\n", id, preco, tempo, cidade);
}


int main(){
int id;
double preco;
char tempo[6];
char cidade[10];

//Ler a quantidade de registros a serem lidos
  scanf("%d", &id);

  //Ler o n registros
  while (id != 0)
  {
    scanf(" %lf %s %[^\n]", &preco, tempo, cidade);
    processarRegistro(id, preco, tempo, cidade);
    scanf("%d", &id);
  }
   

  return 0;
}


