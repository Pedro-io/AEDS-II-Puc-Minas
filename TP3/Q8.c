#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys/time.h> // Para gettimeofday

#define TAM_LINHA 1024
#define CAMPOS 12
#define TAM_ELENCO 100

typedef struct {
    char showId[100];
    char tipo[100];
    char titulo[100];
    char diretor[100];
    char elenco[TAM_ELENCO][100];
    int tamElenco;
    char pais[100];
    struct tm dataAdicionado;
    int anoLancamento;
    char classificacao[100];
    char duracao[100];
    char categorias[100];
    char descricao[1000];
} Show;

// Variável global para contar comparações
long long comparacoes = 0;

// Função para separar campos de uma linha CSV
void separarCampos(const char *linha, char campos[][1000]) {
    int campo = 0, pos = 0, i = 0, aspas = 0;
    while (linha[i] != '\0') {
        if (linha[i] == '\"') {
            aspas = !aspas;
        } else if (linha[i] == ',' && !aspas) {
            campos[campo][pos] = '\0';
            campo++; pos = 0;
        } else {
            campos[campo][pos++] = linha[i];
        }
        i++;
    }
    campos[campo][pos] = '\0';
}

const char* valorOuNaN(char campos[][1000], int idx) {
    if (idx >= CAMPOS || strlen(campos[idx]) == 0) return "NaN";
    return campos[idx];
}

// Função para converter data em struct tm
void lerData(const char* str, struct tm* data) {
    memset(data, 0, sizeof(struct tm));
    if (strcmp(str, "NaN") == 0) return;
    char mes[20];
    int dia, ano;
    sscanf(str, "%s %d, %d", mes, &dia, &ano);
    const char* meses[] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
    for (int i = 0; i < 12; i++)
        if (strcmp(mes, meses[i]) == 0) data->tm_mon = i;
    data->tm_mday = dia;
    data->tm_year = ano - 1900;
}

// Função para separar elenco
void lerElenco(const char* str, Show* show) {
    show->tamElenco = 0;
    if (strcmp(str, "NaN") == 0) return;
    char temp[1000];
    strcpy(temp, str);
    char* p = temp;
    while (*p) {
        // Pular espaços iniciais
        while (*p == ' ' || *p == ',') p++;
        if (*p == '\0') break;
        char* ini = p;
        while (*p != ',' && *p != '\0') p++;
        int tam = p - ini;
        while (tam > 0 && isspace(ini[tam-1])) tam--;
        strncpy(show->elenco[show->tamElenco], ini, tam);
        show->elenco[show->tamElenco][tam] = '\0';
        show->tamElenco++;
    }
}

// Função para ler um show a partir de uma linha
void lerShow(Show* show, const char* linha) {
    char campos[CAMPOS][1000];
    separarCampos(linha, campos);
    strcpy(show->showId, valorOuNaN(campos, 0));
    strcpy(show->tipo, valorOuNaN(campos, 1));
    strcpy(show->titulo, valorOuNaN(campos, 2));
    strcpy(show->diretor, valorOuNaN(campos, 3));
    lerElenco(valorOuNaN(campos, 4), show);
    strcpy(show->pais, valorOuNaN(campos, 5));
    lerData(valorOuNaN(campos, 6), &show->dataAdicionado);
    const char* ano = valorOuNaN(campos, 7);
    show->anoLancamento = strcmp(ano, "NaN") == 0 ? 0 : atoi(ano);
    strcpy(show->classificacao, valorOuNaN(campos, 8));
    strcpy(show->duracao, valorOuNaN(campos, 9));
    strcpy(show->categorias, valorOuNaN(campos, 10));
    strcpy(show->descricao, valorOuNaN(campos, 11));
}

// Função para ordenar elenco em ordem alfabética 
void ordenarElenco(Show* show) {
    for (int i = 0; i < show->tamElenco-1; i++) {
        for (int j = 0; j < show->tamElenco-1-i; j++) {
            if (strcmp(show->elenco[j], show->elenco[j+1]) > 0) {
                char aux[100];
                strcpy(aux, show->elenco[j]);
                strcpy(show->elenco[j], show->elenco[j+1]);
                strcpy(show->elenco[j+1], aux);
            }
        }
    }
}

// Função para formatar a saída de um show
void formatarShow(const Show* show, char* saida) {
    char elencoStr[1000] = "";
    if (show->tamElenco == 0) {
        strcpy(elencoStr, "NaN");
    } else {
        for (int i = 0; i < show->tamElenco; i++) {
            if (i > 0) strcat(elencoStr, ", ");
            strcat(elencoStr, show->elenco[i]);
        }
    }
    char dataStr[100];
    if (show->dataAdicionado.tm_year == 0 && show->dataAdicionado.tm_mon == 0 && show->dataAdicionado.tm_mday == 0) {
        strcpy(dataStr, "NaN");
    } else {
        const char* meses[] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
        sprintf(dataStr, "%s %d, %d", meses[show->dataAdicionado.tm_mon], show->dataAdicionado.tm_mday, show->dataAdicionado.tm_year+1900);
    }
    sprintf(saida, "=> %s ## %s ## %s ## %s ## [%s] ## %s ## %s ## %d ## %s ## %s ## [%s] ##",
        show->showId, show->titulo, show->tipo, show->diretor, elencoStr, show->pais, dataStr,
        show->anoLancamento, show->classificacao, show->duracao, show->categorias);
}

// Função para ler todas as linhas do CSV
char** lerArquivo(const char* caminho, int* total) {
    FILE* arq = fopen(caminho, "r");
    if (!arq) return NULL;
    char** linhas = NULL;
    *total = 0;
    char buf[TAM_LINHA];
    fgets(buf, sizeof(buf), arq); // Pular cabeçalho
    while (fgets(buf, sizeof(buf), arq)) {
        buf[strcspn(buf, "\n")] = '\0';
        linhas = realloc(linhas, (*total+1)*sizeof(char*));
        linhas[*total] = strdup(buf);
        (*total)++;
    }
    fclose(arq);
    return linhas;
}


int compararDatas(const struct tm* d1, const struct tm* d2) {
    comparacoes++;
    if (d1->tm_year != d2->tm_year) return d1->tm_year - d2->tm_year;
    comparacoes++;
    if (d1->tm_mon != d2->tm_mon) return d1->tm_mon - d2->tm_mon;
    comparacoes++;
    return d1->tm_mday - d2->tm_mday;
}

void swap(Show** a, Show** b) {
    Show* temp = *a;
    *a = *b;
    *b = temp;
}

int compararShows(const Show* a, const Show* b) {
    int cmp = compararDatas(&a->dataAdicionado, &b->dataAdicionado);
    if (cmp != 0) return cmp;
    comparacoes++;
    return strcmp(a->titulo, b->titulo);
}

int partition(Show** lista, int low, int high) {
    Show* pivot = lista[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (compararShows(lista[j], pivot) < 0) {
            i++;
            swap(&lista[i], &lista[j]);
        }
    }
    swap(&lista[i+1], &lista[high]);
    return i+1;
}

void quicksortShows(Show** lista, int low, int high) {
    if (low < high) {
        int pi = partition(lista, low, high);
        quicksortShows(lista, low, pi - 1);
        quicksortShows(lista, pi + 1, high);
    }
}

// Substitua a função ordenarShows por esta:
void ordenarShows(Show** lista, int n) {
    quicksortShows(lista, 0, n - 1);
}

int main() {
    int totalLinhas;
    char** linhas = lerArquivo("/tmp/disneyplus.csv", &totalLinhas);
    if (!linhas) return 1;

    Show** todos = malloc(totalLinhas * sizeof(Show*));
    for (int i = 0; i < totalLinhas; i++) {
        todos[i] = malloc(sizeof(Show));
        lerShow(todos[i], linhas[i]);
        ordenarElenco(todos[i]);
        free(linhas[i]);
    }
    free(linhas);

    Show** selecionados = NULL;
    int qtdSelecionados = 0;
    char entrada[100];

    int lendo = 1;
    while (lendo) {
        if (fgets(entrada, sizeof(entrada), stdin) == NULL) break;
        entrada[strcspn(entrada, "\n")] = '\0';
        if (strcmp(entrada, "FIM") == 0) {
            lendo = 0;
        } else {
            for (int i = 0; i < totalLinhas; i++) {
                if (strcmp(todos[i]->showId, entrada) == 0) {
                    selecionados = realloc(selecionados, (qtdSelecionados+1)*sizeof(Show*));
                    selecionados[qtdSelecionados] = todos[i];
                    qtdSelecionados++;
                }
            }
        }
    }

    // Medir tempo de execução da ordenação
    struct timeval inicio, fim;
    gettimeofday(&inicio, NULL);

    ordenarShows(selecionados, qtdSelecionados);

    gettimeofday(&fim, NULL);
    double tempo = (fim.tv_sec - inicio.tv_sec) + (fim.tv_usec - inicio.tv_usec)/1000000.0;

    char saida[2000];
    for (int i = 0; i < qtdSelecionados; i++) {
        formatarShow(selecionados[i], saida);
        printf("%s\n", saida);
    }

    for (int i = 0; i < totalLinhas; i++) free(todos[i]);
    free(todos);
    free(selecionados);

    // Escrever arquivo de log
    FILE* log = fopen("matrícula_quicksort2.txt", "w");
    if (log) {
        fprintf(log, "MATRICULA\t%.6f\t%lld\n", tempo, comparacoes); // Substitua MATRÍCULA pela sua matrícula real
        fclose(log);
    }

    return 0;
}