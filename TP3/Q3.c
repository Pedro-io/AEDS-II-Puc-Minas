#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>

// Estrutura que representa um programa de TV ou filme
typedef struct {
    char showId[20];
    char type[20];
    char title[200];
    char director[200];
    char** cast;
    int numCast;
    char country[100];
    time_t dateAdded;
    int releaseYear;
    char rating[20];
    char duration[50];
    char listedIn[200];
    char description[500];
} Show;

// Vetor global para armazenar todos os programas lidos do CSV
Show* allShows = NULL;
int numAllShows = 0;
int capacityAllShows = 10000;

// Inicializa um Show com valores padrão
void inicializarShow(Show* s) {
    s->cast = NULL;
    s->numCast = 0;
    s->dateAdded = 0;
    s->releaseYear = 0;
    strcpy(s->showId, "NaN");
    strcpy(s->type, "NaN");
    strcpy(s->title, "NaN");
    strcpy(s->director, "NaN");
    strcpy(s->country, "NaN");
    strcpy(s->rating, "NaN");
    strcpy(s->duration, "NaN");
    strcpy(s->listedIn, "NaN");
    strcpy(s->description, "NaN");
}

// Libera memória alocada dinamicamente para um Show
void liberarShow(Show* s) {
    if (s->cast != NULL) {
        for (int i = 0; i < s->numCast; i++) {
            if (s->cast[i] != NULL) {
                free(s->cast[i]);
            }
        }
        free(s->cast);
        s->cast = NULL;
    }
}

// Realiza uma cópia profunda de um Show
Show copiarShow(const Show* origem) {
    Show destino;
    inicializarShow(&destino);

    strcpy(destino.showId, origem->showId);
    strcpy(destino.type, origem->type);
    strcpy(destino.title, origem->title);
    strcpy(destino.director, origem->director);
    strcpy(destino.country, origem->country);
    destino.dateAdded = origem->dateAdded;
    destino.releaseYear = origem->releaseYear;
    strcpy(destino.rating, origem->rating);
    strcpy(destino.duration, origem->duration);
    strcpy(destino.listedIn, origem->listedIn);
    strcpy(destino.description, origem->description);

    destino.numCast = origem->numCast;
    if (origem->numCast > 0) {
        destino.cast = (char**)malloc(origem->numCast * sizeof(char*));
        if (destino.cast == NULL) {
            fprintf(stderr, "Falha ao alocar memória para elenco (deep copy)\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < origem->numCast; i++) {
            destino.cast[i] = strdup(origem->cast[i]);
            if (destino.cast[i] == NULL) {
                fprintf(stderr, "Falha ao alocar memória para membro do elenco\n");
                exit(EXIT_FAILURE);
            }
        }
    } else {
        destino.cast = NULL;
    }
    return destino;
}

// Função para separar campos de uma linha CSV
void separarCamposCSV(char* linha, char** campos, int* quantidade) {
    bool entreAspas = false;
    int idxCampo = 0, idxChar = 0;
    char buffer[1000];

    linha[strcspn(linha, "\r\n")] = 0;

    for (int i = 0; linha[i] != '\0'; i++) {
        char c = linha[i];
        if (c == '\"') {
            entreAspas = !entreAspas;
        } else if (c == ',' && !entreAspas) {
            buffer[idxChar] = '\0';
            campos[idxCampo] = strdup(buffer);
            idxCampo++;
            idxChar = 0;
            if (idxCampo >= 12) {
                i = strlen(linha); // força saída do laço
            }
        } else {
            buffer[idxChar++] = c;
            if (idxChar >= sizeof(buffer) - 1) {
                fprintf(stderr, "Atenção: possível estouro de buffer ao separar campos CSV.\n");
                idxChar = sizeof(buffer) - 2;
            }
        }
    }
    buffer[idxChar] = '\0';
    campos[idxCampo] = strdup(buffer);
    *quantidade = idxCampo + 1;
}

// Converte string de data para time_t
time_t converterData(const char* dataStr) {
    struct tm tm_obj = {0};
    char mes[20];
    int dia, ano;

    if (sscanf(dataStr, "%s %d, %d", mes, &dia, &ano) != 3) {
        return 0;
    }

    if (strcmp(mes, "January") == 0) tm_obj.tm_mon = 0;
    else if (strcmp(mes, "February") == 0) tm_obj.tm_mon = 1;
    else if (strcmp(mes, "March") == 0) tm_obj.tm_mon = 2;
    else if (strcmp(mes, "April") == 0) tm_obj.tm_mon = 3;
    else if (strcmp(mes, "May") == 0) tm_obj.tm_mon = 4;
    else if (strcmp(mes, "June") == 0) tm_obj.tm_mon = 5;
    else if (strcmp(mes, "July") == 0) tm_obj.tm_mon = 6;
    else if (strcmp(mes, "August") == 0) tm_obj.tm_mon = 7;
    else if (strcmp(mes, "September") == 0) tm_obj.tm_mon = 8;
    else if (strcmp(mes, "October") == 0) tm_obj.tm_mon = 9;
    else if (strcmp(mes, "November") == 0) tm_obj.tm_mon = 10;
    else if (strcmp(mes, "December") == 0) tm_obj.tm_mon = 11;
    else return 0;

    tm_obj.tm_mday = dia;
    tm_obj.tm_year = ano - 1900;

    return mktime(&tm_obj);
}

// Macro para copiar strings com tratamento de campos vazios ou entre aspas
#define COPIA_SEGURA(dest, src) \
    do { \
        if (src == NULL || strlen(src) == 0) { \
            strcpy(dest, "NaN"); \
        } else { \
            char* temp = strdup(src); \
            if (temp[0] == '\"' && temp[strlen(temp) - 1] == '\"') { \
                temp[strlen(temp) - 1] = '\0'; \
                memmove(temp, temp + 1, strlen(temp)); \
            } \
            strcpy(dest, temp); \
            free(temp); \
        } \
    } while(0)

// Lê uma linha do CSV e preenche um Show
void lerShowCSV(Show* s, char* linha) {
    inicializarShow(s);

    char* campos[12];
    int qtdCampos = 0;
    separarCamposCSV(linha, campos, &qtdCampos);

    for (int i = qtdCampos; i < 12; i++) {
        campos[i] = strdup("");
    }

    COPIA_SEGURA(s->showId, campos[0]);
    COPIA_SEGURA(s->type, campos[1]);
    COPIA_SEGURA(s->title, campos[2]);
    COPIA_SEGURA(s->director, campos[3]);

    char* elenco = campos[4];
    if (elenco == NULL || strlen(elenco) == 0) {
        s->cast = NULL;
        s->numCast = 0;
    } else {
        char* tempElenco = strdup(elenco);
        if (tempElenco[0] == '\"' && tempElenco[strlen(tempElenco) - 1] == '\"') {
            tempElenco[strlen(tempElenco) - 1] = '\0';
            memmove(tempElenco, tempElenco + 1, strlen(tempElenco));
        }

        char* token = strtok(tempElenco, ",");
        s->numCast = 0;
        while (token != NULL) {
            char* inicio = token;
            while (*inicio == ' ') inicio++;
            size_t tam = strlen(inicio);
            while (tam > 0 && inicio[tam - 1] == ' ') tam--;
            inicio[tam] = '\0';

            s->numCast++;
            s->cast = (char**)realloc(s->cast, s->numCast * sizeof(char*));
            if (s->cast == NULL) {
                fprintf(stderr, "Erro ao alocar memória para elenco\n");
                exit(EXIT_FAILURE);
            }
            s->cast[s->numCast - 1] = strdup(inicio);
            if (s->cast[s->numCast - 1] == NULL) {
                fprintf(stderr, "Erro ao alocar memória para membro do elenco\n");
                exit(EXIT_FAILURE);
            }
            token = strtok(NULL, ",");
        }
        free(tempElenco);
    }

    COPIA_SEGURA(s->country, campos[5]);

    char* data = campos[6];
    if (data == NULL || strlen(data) == 0) {
        s->dateAdded = 0;
    } else {
        char* tempData = strdup(data);
        if (tempData[0] == '\"' && tempData[strlen(tempData) - 1] == '\"') {
            tempData[strlen(tempData) - 1] = '\0';
            memmove(tempData, tempData + 1, strlen(tempData));
        }
        s->dateAdded = converterData(tempData);
        free(tempData);
    }

    char* anoLancamento = campos[7];
    if (anoLancamento == NULL || strlen(anoLancamento) == 0) {
        s->releaseYear = 0;
    } else {
        char* tempAno = strdup(anoLancamento);
        if (tempAno[0] == '\"' && tempAno[strlen(tempAno) - 1] == '\"') {
            tempAno[strlen(tempAno) - 1] = '\0';
            memmove(tempAno, tempAno + 1, strlen(tempAno));
        }
        s->releaseYear = atoi(tempAno);
        free(tempAno);
    }

    COPIA_SEGURA(s->rating, campos[8]);
    COPIA_SEGURA(s->duration, campos[9]);
    COPIA_SEGURA(s->listedIn, campos[10]);
    COPIA_SEGURA(s->description, campos[11]);

    for (int i = 0; i < 12; i++) {
        free(campos[i]);
    }
}

// Função de comparação para ordenar strings (usada no elenco)
int compararStrings(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

// Exibe um Show formatado
void exibirShow(const Show* s) {
    printf("=> %s ## %s ## %s ## %s ## [", s->showId, s->title, s->type, s->director);

    if (s->numCast > 0) {
        char** elencoOrdenado = (char**)malloc(s->numCast * sizeof(char*));
        if (elencoOrdenado == NULL) {
            fprintf(stderr, "Erro ao alocar memória para elenco ordenado\n");
            exit(EXIT_FAILURE);
        }
        for (int i = 0; i < s->numCast; i++) {
            elencoOrdenado[i] = s->cast[i];
        }
        qsort(elencoOrdenado, s->numCast, sizeof(char*), compararStrings);

        for (int i = 0; i < s->numCast; i++) {
            printf("%s", elencoOrdenado[i]);
            if (i < s->numCast - 1) printf(", ");
        }
        free(elencoOrdenado);
    } else {
        printf("NaN");
    }
    printf("] ## %s ## ", s->country);

    if (s->dateAdded != 0) {
        char buffer[80];
        struct tm* info = localtime(&s->dateAdded);
        strftime(buffer, sizeof(buffer), "%B %d, %Y", info);
        printf("%s", buffer);
    } else {
        printf("NaN");
    }

    printf(" ## %d ## %s ## %s ## [%s] ##\n",
           s->releaseYear, s->rating, s->duration, s->listedIn);
}

// Estrutura para pilha dinâmica de Shows
typedef struct {
    Show* array;
    int topo;
    int capacidade;
} PilhaShow;

// Inicializa a pilha de Shows
void criarPilha(PilhaShow* pilha, int tamanho) {
    pilha->array = (Show*)malloc(tamanho * sizeof(Show));
    if (pilha->array == NULL) {
        fprintf(stderr, "Erro ao alocar memória para pilha\n");
        exit(EXIT_FAILURE);
    }
    pilha->topo = -1;
    pilha->capacidade = tamanho;
}

// Libera toda a memória da pilha
void destruirPilha(PilhaShow* pilha) {
    while (pilha->topo >= 0) {
        liberarShow(&pilha->array[pilha->topo]);
        pilha->topo--;
    }
    free(pilha->array);
    pilha->array = NULL;
    pilha->capacidade = 0;
}

// Adiciona um Show ao topo da pilha
void empilharShow(PilhaShow* pilha, Show show) {
    if (pilha->topo == pilha->capacidade - 1) {
        fprintf(stderr, "Pilha cheia, não é possível empilhar.\n");
        return;
    }
    pilha->topo++;
    pilha->array[pilha->topo] = copiarShow(&show);
}

// Remove e retorna o Show do topo da pilha
Show desempilharShow(PilhaShow* pilha) {
    if (pilha->topo == -1) {
        fprintf(stderr, "Pilha vazia, não é possível desempilhar.\n");
        Show vazio;
        inicializarShow(&vazio);
        return vazio;
    }
    Show removido = pilha->array[pilha->topo];
    pilha->topo--;
    return removido;
}

// Mostra todos os Shows da pilha do topo até a base
void mostrarConteudoPilha(const PilhaShow* pilha) {
    for (int i = pilha->topo; i >= 0; i--) {
        exibirShow(&pilha->array[i]);
    }
}

// Lê todos os programas do arquivo CSV para o vetor global
void carregarCSV(const char* caminho) {
    FILE* arq = fopen(caminho, "r");
    if (arq == NULL) {
        perror("Falha ao abrir arquivo");
        exit(EXIT_FAILURE);
    }

    char linha[1024];
    fgets(linha, sizeof(linha), arq); // ignora cabeçalho

    allShows = (Show*)malloc(capacityAllShows * sizeof(Show));
    if (allShows == NULL) {
        fprintf(stderr, "Erro ao alocar memória para allShows\n");
        exit(EXIT_FAILURE);
    }

    while (fgets(linha, sizeof(linha), arq) != NULL) {
        if (numAllShows >= capacityAllShows) {
            capacityAllShows *= 2;
            allShows = (Show*)realloc(allShows, capacityAllShows * sizeof(Show));
            if (allShows == NULL) {
                fprintf(stderr, "Erro ao realocar memória para allShows\n");
                exit(EXIT_FAILURE);
            }
        }
        lerShowCSV(&allShows[numAllShows], linha);
        numAllShows++;
    }
    fclose(arq);
}

// Busca um Show pelo showId no vetor global
Show* buscarShowPorId(const char* showId) {
    for (int i = 0; i < numAllShows; i++) {
        if (strcmp(allShows[i].showId, showId) == 0) {
            return &allShows[i];
        }
    }
    return NULL;
}

// Lê uma linha específica do CSV pelo showId
char* obterLinhaPorId(const char* showId) {
    FILE* arq = fopen("/tmp/disneyplus.csv", "r");
    if (arq == NULL) {
        perror("Falha ao abrir arquivo");
        return NULL;
    }

    char linha[1024];
    fgets(linha, sizeof(linha), arq); // ignora cabeçalho

    char* resultado = NULL;
    int encontrou = 0;
    while (fgets(linha, sizeof(linha), arq) != NULL && !encontrou) {
        char tempId[20];
        if (sscanf(linha, "%19[^,]", tempId) == 1) {
            if (strcmp(tempId, showId) == 0) {
                resultado = strdup(linha);
                encontrou = 1;
            }
        }
    }
    fclose(arq);
    return resultado;
}

int main() {
    setlocale(LC_ALL, "en_US.UTF-8");

    carregarCSV("/tmp/disneyplus.csv");

    PilhaShow pilha;
    criarPilha(&pilha, 1000);

    char id[20];
    // Leitura inicial dos IDs e empilhamento
    while (scanf("%19s", id) == 1 && strcmp(id, "FIM") != 0) {
        Show* s = buscarShowPorId(id);
        if (s != NULL) {
            empilharShow(&pilha, *s);
        }
    }

    int qtdComandos;
    scanf("%d", &qtdComandos);
    getchar();

    for (int i = 0; i < qtdComandos; i++) {
        char linhaComando[256];
        if (fgets(linhaComando, sizeof(linhaComando), stdin) == NULL) {
            i = qtdComandos; // força saída do laço
        } else {
            linhaComando[strcspn(linhaComando, "\n")] = 0;

            char comando[2];
            char argumento[20];

            sscanf(linhaComando, "%s", comando);

            if (strcmp(comando, "I") == 0) {
                sscanf(linhaComando, "%*s %19s", argumento);
                char* linhaArquivo = obterLinhaPorId(argumento);
                if (linhaArquivo != NULL) {
                    Show novo;
                    lerShowCSV(&novo, linhaArquivo);
                    empilharShow(&pilha, novo);
                    liberarShow(&novo);
                    free(linhaArquivo);
                } else {
                    fprintf(stderr, "Show '%s' não encontrado para inserção.\n", argumento);
                }
            } else if (strcmp(comando, "R") == 0) {
                Show removido = desempilharShow(&pilha);
                printf("(R) %s\n", removido.title);
                liberarShow(&removido);
            }
        }
    }

    mostrarConteudoPilha(&pilha);

    destruirPilha(&pilha);

    if (allShows != NULL) {
        for (int i = 0; i < numAllShows; i++) {
            liberarShow(&allShows[i]);
        }
        free(allShows);
        allShows = NULL;
    }

    return 0;
}