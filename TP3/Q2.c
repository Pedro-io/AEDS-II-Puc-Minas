#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SHOWS 1000
#define MAX_LINE 1024
#define MAX_CAST 20
#define MAX_FIELD 128

typedef struct {
    char showId[MAX_FIELD];
    char type[MAX_FIELD];
    char title[MAX_FIELD];
    char director[MAX_FIELD];
    char cast[MAX_CAST][MAX_FIELD];
    int castCount;
    char country[MAX_FIELD];
    char dataAdded[MAX_FIELD];
    int releaseYear;
    char rating[MAX_FIELD];
    char duration[MAX_FIELD];
    char listedIn[MAX_FIELD];
    char description[MAX_FIELD];
} Show;

typedef struct {
    Show array[MAX_SHOWS];
    int n;
} ListaShow;

// Função para remover aspas e espaços extras
void trim(char *str) {
    char *src = str, *dst = str;
    while (*src) {
        if (*src != '\"') *dst++ = *src;
        src++;
    }
    *dst = '\0';
    // Remove espaços do início
    while (*str == ' ') memmove(str, str+1, strlen(str));
    // Remove espaços do fim
    int len = strlen(str);
    while (len > 0 && str[len-1] == ' ') str[--len] = '\0';
}

// Função para dividir uma linha CSV em campos, considerando aspas
int parseLinhaCSV(char *linha, char campos[][MAX_FIELD], int maxCampos) {
    int i = 0, campo = 0, pos = 0;
    bool emAspas = false;
    char temp[MAX_FIELD] = {0};
    while (linha[i] && campo < maxCampos) {
        if (linha[i] == '\"') {
            emAspas = !emAspas;
        } else if (linha[i] == ',' && !emAspas) {
            temp[pos] = '\0';
            strncpy(campos[campo], temp, MAX_FIELD);
            trim(campos[campo]);
            campo++;
            pos = 0;
            temp[0] = '\0';
        } else {
            if (pos < MAX_FIELD-1) temp[pos++] = linha[i];
        }
        i++;
    }
    temp[pos] = '\0';
    strncpy(campos[campo], temp, MAX_FIELD);
    trim(campos[campo]);
    return campo+1;
}

void lerShow(Show *show, char *linha) {
    char campos[20][MAX_FIELD];
    int nCampos = parseLinhaCSV(linha, campos, 20);

    strcpy(show->showId, nCampos > 0 ? campos[0] : "NaN");
    strcpy(show->type, nCampos > 1 ? campos[1] : "NaN");
    strcpy(show->title, nCampos > 2 ? campos[2] : "NaN");
    strcpy(show->director, nCampos > 3 ? campos[3] : "NaN");

    // Cast
    show->castCount = 0;
    if (nCampos > 4 && strcmp(campos[4], "") != 0) {
        char *token = strtok(campos[4], ",");
        while (token && show->castCount < MAX_CAST) {
            trim(token);
            strcpy(show->cast[show->castCount++], token);
            token = strtok(NULL, ",");
        }
    }

    strcpy(show->country, nCampos > 5 ? campos[5] : "NaN");
    strcpy(show->dataAdded, nCampos > 6 ? campos[6] : "NaN");
    show->releaseYear = (nCampos > 7 && strcmp(campos[7], "") != 0) ? atoi(campos[7]) : 0;
    strcpy(show->rating, nCampos > 8 ? campos[8] : "NaN");
    strcpy(show->duration, nCampos > 9 ? campos[9] : "NaN");
    strcpy(show->listedIn, nCampos > 10 ? campos[10] : "NaN");
    strcpy(show->description, nCampos > 11 ? campos[11] : "NaN");
}

void formatarShow(Show *show, char *saida) {
    // Ordena o cast
    char castOrdenado[MAX_CAST][MAX_FIELD];
    for (int i = 0; i < show->castCount; i++)
        strcpy(castOrdenado[i], show->cast[i]);
    // Bubble sort simples
    for (int i = 0; i < show->castCount-1; i++)
        for (int j = 0; j < show->castCount-i-1; j++)
            if (strcmp(castOrdenado[j], castOrdenado[j+1]) > 0) {
                char tmp[MAX_FIELD];
                strcpy(tmp, castOrdenado[j]);
                strcpy(castOrdenado[j], castOrdenado[j+1]);
                strcpy(castOrdenado[j+1], tmp);
            }

    char castStr[MAX_LINE] = "NaN";
    if (show->castCount > 0) {
        castStr[0] = '\0';
        for (int i = 0; i < show->castCount; i++) {
            strcat(castStr, castOrdenado[i]);
            if (i < show->castCount-1) strcat(castStr, ", ");
        }
    }

    sprintf(saida, "=> %s ## %s ## %s ## %s ## [%s] ## %s ## %s ## %d ## %s ## %s ## [%s] ##",
        show->showId,
        show->title,
        show->type,
        show->director,
        castStr,
        show->country,
        show->dataAdded,
        show->releaseYear,
        show->rating,
        show->duration,
        show->listedIn
    );
}

// ListaShow funções
void inserirInicio(ListaShow *lista, Show show) {
    if (lista->n >= MAX_SHOWS) return;
    for (int i = lista->n; i > 0; i--)
        lista->array[i] = lista->array[i-1];
    lista->array[0] = show;
    lista->n++;
}

void inserirFim(ListaShow *lista, Show show) {
    if (lista->n >= MAX_SHOWS) return;
    lista->array[lista->n++] = show;
}

void inserirPos(ListaShow *lista, Show show, int pos) {
    if (lista->n >= MAX_SHOWS || pos < 0 || pos > lista->n) return;
    for (int i = lista->n; i > pos; i--)
        lista->array[i] = lista->array[i-1];
    lista->array[pos] = show;
    lista->n++;
}

Show removerInicio(ListaShow *lista) {
    Show resp = lista->array[0];
    for (int i = 0; i < lista->n-1; i++)
        lista->array[i] = lista->array[i+1];
    lista->n--;
    return resp;
}

Show removerFim(ListaShow *lista) {
    return lista->array[--lista->n];
}

Show removerPos(ListaShow *lista, int pos) {
    Show resp = lista->array[pos];
    for (int i = pos; i < lista->n-1; i++)
        lista->array[i] = lista->array[i+1];
    lista->n--;
    return resp;
}

void mostrarLista(ListaShow *lista) {
    char saida[MAX_LINE*2];
    for (int i = 0; i < lista->n; i++) {
        formatarShow(&lista->array[i], saida);
        printf("%s\n", saida);
    }
}

// Busca uma linha no CSV pelo showId
bool lerLinhaPorArquivo(const char *showId, char *linhaOut) {
    FILE *fp = fopen("/tmp/disneyplus.csv", "r");
    if (!fp) return false;
    char linha[MAX_LINE];
    fgets(linha, MAX_LINE, fp); // pula cabeçalho
    while (fgets(linha, MAX_LINE, fp)) {
        if (strncmp(linha, showId, strlen(showId)) == 0 && linha[strlen(showId)] == ',') {
            strcpy(linhaOut, linha);
            fclose(fp);
            return true;
        }
    }
    fclose(fp);
    return false;
}

int main() {
    ListaShow lista;
    lista.n = 0;
    char id[MAX_FIELD];
    char linha[MAX_LINE];

    // Primeira parte: ler IDs e adicionar na lista
    while (scanf("%s", id) == 1 && strcmp(id, "FIM") != 0) {
        if (lerLinhaPorArquivo(id, linha)) {
            Show s;
            lerShow(&s, linha);
            inserirFim(&lista, s);
        }
    }

    int n;
    scanf("%d", &n);
    getchar(); // Consome o \n

    for (int i = 0; i < n; i++) {
        char comando[8], arg1[MAX_FIELD], arg2[MAX_FIELD];
        fgets(linha, MAX_LINE, stdin);
        int pos;
        if (sscanf(linha, "%s %s %s", comando, arg1, arg2) >= 2) {
            if (strcmp(comando, "II") == 0) {
                if (lerLinhaPorArquivo(arg1, linha)) {
                    Show s;
                    lerShow(&s, linha);
                    inserirInicio(&lista, s);
                }
            } else if (strcmp(comando, "IF") == 0) {
                if (lerLinhaPorArquivo(arg1, linha)) {
                    Show s;
                    lerShow(&s, linha);
                    inserirFim(&lista, s);
                }
            } else if (strcmp(comando, "I*") == 0) {
                pos = atoi(arg1);
                if (lerLinhaPorArquivo(arg2, linha)) {
                    Show s;
                    lerShow(&s, linha);
                    inserirPos(&lista, s, pos);
                }
            } else if (strcmp(comando, "RI") == 0) {
                Show removido = removerInicio(&lista);
                printf("(R) %s\n", removido.title);
            } else if (strcmp(comando, "RF") == 0) {
                Show removido = removerFim(&lista);
                printf("(R) %s\n", removido.title);
            } else if (strcmp(comando, "R*") == 0) {
                pos = atoi(arg1);
                Show removido = removerPos(&lista, pos);
                printf("(R) %s\n", removido.title);
            }
        }
    }

    mostrarLista(&lista);
    return 0;
}