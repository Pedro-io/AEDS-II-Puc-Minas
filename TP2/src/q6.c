#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_SHOWS 5000
#define MAX_LINE 1000

int comparacoes = 0;
int movimentacoes = 0;

typedef struct Show {
    char show_id[50];
    char title[200];
    char type[50];
    char director[200];
    char cast[400];
    char country[100];
    char date_added[100];
    int release_year;
    char rating[20];
    char duration[30];
    char listed_in[300];
} Show;

void trim(char* str) {
    int i = 0;
    while (isspace(str[i])) i++;
    int j = strlen(str) - 1;
    while (j > i && isspace(str[j])) j--;
    memmove(str, str + i, j - i + 1);
    str[j - i + 1] = '\0';
}

void ordenarEUnir(char* campo) {
    if (strcmp(campo, "NaN") == 0 || strlen(campo) == 0) return;

    char copia[400];
    strcpy(copia, campo);

    char* tokens[50];
    int count = 0;

    char* token = strtok(copia, ",");
    while (token != NULL && count < 50) {
        trim(token);
        tokens[count++] = token;
        token = strtok(NULL, ",");
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (strcmp(tokens[i], tokens[j]) > 0) {
                char* temp = tokens[i];
                tokens[i] = tokens[j];
                tokens[j] = temp;
            }
        }
    }

    campo[0] = '\0';
    for (int i = 0; i < count; i++) {
        strcat(campo, tokens[i]);
        if (i < count - 1) strcat(campo, ", ");
    }
}

void limparAspas(char* str) {
    int i = 0, j = 0;
    char temp[strlen(str) + 1];
    while (str[i]) {
        if (str[i] != '"') {
            temp[j++] = str[i];
        }
        i++;
    }
    temp[j] = '\0';
    strcpy(str, temp);
}

int lerCSV(char* linha, Show* s) {
    char* campos[20];
    int i = 0, in_quotes = 0;
    char* token = strtok(linha, ",");
    char buffer[300] = "";

    while (token != NULL) {
        if (in_quotes || strchr(token, '"')) {
            strcat(buffer, token);
            if (strchr(token, '"')) in_quotes = !in_quotes;
            if (!in_quotes) {
                limparAspas(buffer);
                campos[i++] = strdup(buffer);
                buffer[0] = '\0';
            } else {
                strcat(buffer, ",");
            }
        } else {
            campos[i++] = strdup(token);
        }
        token = strtok(NULL, ",");
    }

    strcpy(s->show_id, i > 0 ? campos[0] : "NaN");
    strcpy(s->type, i > 1 ? campos[1] : "NaN");
    strcpy(s->title, i > 2 ? campos[2] : "NaN");
    strcpy(s->director, i > 3 ? campos[3] : "NaN");
    strcpy(s->cast, i > 4 ? campos[4] : "NaN");
    strcpy(s->country, i > 5 ? campos[5] : "NaN");
    strcpy(s->date_added, i > 6 ? campos[6] : "NaN");
    s->release_year = (i > 7 && strcmp(campos[7], "") != 0) ? atoi(campos[7]) : 0;
    strcpy(s->rating, i > 8 ? campos[8] : "NaN");
    strcpy(s->duration, i > 9 ? campos[9] : "NaN");
    strcpy(s->listed_in, i > 10 ? campos[10] : "NaN");

    ordenarEUnir(s->cast);
    ordenarEUnir(s->listed_in);

    for (int j = 0; j < i; j++) free(campos[j]);

    return 1;
}

void imprimir_Show(Show s) {
    printf("=> %s ## %s ## %s ## %s ## [%s] ## %s ## %s ## %d ## %s ## %s ## [%s] ##\n",
           s.show_id, s.title, s.type, s.director, s.cast,
           s.country, s.date_added, s.release_year,
           s.rating, s.duration, s.listed_in);
}

void swap(Show* a, Show* b) {
    Show temp = *a;
    *a = *b;
    *b = temp;
    movimentacoes += 3;
}

int menorIndice(Show* v, int i, int j) {
    if (i == j) return i;
    int k = menorIndice(v, i + 1, j);
    comparacoes++;
    return (strcmp(v[i].title, v[k].title) < 0) ? i : k;
}

void selectionSortRec(Show* v, int i, int n) {
    if (i >= n - 1) return;
    int k = menorIndice(v, i, n - 1);
    if (k != i) swap(&v[i], &v[k]);
    selectionSortRec(v, i + 1, n);
}

int main() {
    clock_t inicio = clock();

    Show* base = (Show*) malloc(MAX_SHOWS * sizeof(Show));
    Show* inseridos = (Show*) malloc(MAX_SHOWS * sizeof(Show));
    int totalBase = 0;
    int totalInseridos = 0;
    char linha[MAX_LINE], entrada[200];

    FILE* file = fopen("/tmp/disneyplus.csv", "r");
    if (file == NULL) return 1;

    fgets(linha, MAX_LINE, file);
    while (fgets(linha, MAX_LINE, file) != NULL && totalBase < MAX_SHOWS) {
        linha[strcspn(linha, "\r\n")] = '\0';
        if (lerCSV(linha, &base[totalBase]) == 1) totalBase++;
    }
    fclose(file);

    int lendoIds = 1;
    while (lendoIds == 1 && fgets(entrada, sizeof(entrada), stdin) != NULL) {
        entrada[strcspn(entrada, "\r\n")] = '\0';
        if (strcmp(entrada, "FIM") == 0) {
            lendoIds = 0;
        } else {
            for (int i = 0; i < totalBase; i++) {
                if (strcmp(base[i].show_id, entrada) == 0 && totalInseridos < MAX_SHOWS) {
                    inseridos[totalInseridos++] = base[i];
                }
            }
        }
    }

    selectionSortRec(inseridos, 0, totalInseridos);

    for (int i = 0; i < totalInseridos; i++) {
        imprimir_Show(inseridos[i]);
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    FILE* log = fopen("matricula_selecao.txt", "w");
    if (log != NULL) {
        fprintf(log, "793406\t%d\t%d\t%.6lf", comparacoes, movimentacoes, tempo);
        fclose(log);
    }

    free(base);
    free(inseridos);
    return 0;
}
