#include <stdio.h>
#include <stdlib.h>

int main() {
    int n;
    float valor;

    // Lê o número inteiro n
    scanf("%d", &n);

    // Abre o arquivo para escrita binária
    FILE *arquivo = fopen("dados.bin", "wb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Salva os n números reais no arquivo
    for (int i = 0; i < n; i++) {
        scanf("%f", &valor);
        fwrite(&valor, sizeof(double), 1, arquivo);
    }

    // Fecha o arquivo após a escrita
    fclose(arquivo);

    // Reabre o arquivo para leitura binária
    arquivo = fopen("dados.bin", "rb");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    // Posiciona o ponteiro no final do arquivo
    fseek(arquivo, 0, SEEK_END);
    long tamanhoArquivo = ftell(arquivo);

    // Lê os valores de trás para frente
    for (long posicao = tamanhoArquivo - sizeof(double); posicao >= 0; posicao -= sizeof(double)) {
        fseek(arquivo, posicao, SEEK_SET);
        fread(&valor, sizeof(double), 1, arquivo);
        printf("%g\n", valor); // Exibe o valor com 6 casas decimais
    }

    // Fecha o arquivo após a leitura
    fclose(arquivo);

    // Remove o arquivo temporário
    remove("dados.bin");

    return 0;
}