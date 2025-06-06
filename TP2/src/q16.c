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

void limparAspas(char* str) {
    int i, j = 0;
    char temp[strlen(str) + 1];
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != '"') {
            temp[j++] = str[i];
        }
    }
    temp[j] = '\0';
    strcpy(str, temp);
}

void trim(char* str) {
    int i = 0;
    while (isspace(str[i])) i++;
    int j = strlen(str) - 1;
    while (j > i && isspace(str[j])) j--;
    memmove(str, str + i, j - i + 1);
    str[j - i + 1] = '\0';
}

void ordenarEUnir(char* campo, char* destino) {
    if (strcmp(campo, "NaN") == 0 || strlen(campo) == 0) {
        strcpy(destino, "NaN");
        return;
    }

    char* tokens[50];
    int count = 0;
    char buffer[400];
    strcpy(buffer, campo);

    char* token = strtok(buffer, ",");
    while (token != NULL && count < 50) {
        trim(token);
        tokens[count++] = strdup(token);
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

    destino[0] = '\0';
    strcat(destino, "[");
    for (int i = 0; i < count; i++) {
        strcat(destino, tokens[i]);
        if (i < count - 1) strcat(destino, ", ");
        free(tokens[i]);
    }
    strcat(destino, "]");
}

int lerCSV(char* linha, Show* s) {
    char* campos[20];
    int i = 0;
    int in_quotes = 0;
    char* p = strtok(linha, ",");
    char buffer[300] = "";

    while (p != NULL) {
        if (in_quotes || strchr(p, '"') != NULL) {
            strcat(buffer, p);
            if (strchr(p, '"') != NULL) in_quotes = !in_quotes;
            if (!in_quotes) {
                limparAspas(buffer);
                campos[i++] = strdup(buffer);
                buffer[0] = '\0';
            } else {
                strcat(buffer, ",");
            }
        } else {
            campos[i++] = strdup(p);
        }
        p = strtok(NULL, ",");
    }

    if (i > 0 && campos[0]) strcpy(s->show_id, campos[0]); else strcpy(s->show_id, "NaN");
    if (i > 1 && campos[1]) strcpy(s->type, campos[1]); else strcpy(s->type, "NaN");
    if (i > 2 && campos[2]) strcpy(s->title, campos[2]); else strcpy(s->title, "NaN");
    if (i > 3 && campos[3]) strcpy(s->director, campos[3]); else strcpy(s->director, "NaN");
    if (i > 5 && campos[5]) strcpy(s->country, campos[5]); else strcpy(s->country, "NaN");
    if (i > 6 && campos[6]) strcpy(s->date_added, campos[6]); else strcpy(s->date_added, "NaN");
    if (i > 7 && campos[7] && strcmp(campos[7], "") != 0) s->release_year = atoi(campos[7]); else s->release_year = 0;
    if (i > 8 && campos[8]) strcpy(s->rating, campos[8]); else strcpy(s->rating, "NaN");
    if (i > 9 && campos[9]) strcpy(s->duration, campos[9]); else strcpy(s->duration, "NaN");

    if (i > 4 && campos[4]) ordenarEUnir(campos[4], s->cast); else strcpy(s->cast, "[NaN]");
    if (i > 10 && campos[10]) ordenarEUnir(campos[10], s->listed_in); else strcpy(s->listed_in, "[NaN]");

    for (int j = 0; j < i; j++) free(campos[j]);
    return 1;
}

void imprimir_Show(Show s) {
    printf("=> %s ## %s ## %s ## %s ## %s ## %s ## %s ## %d ## %s ## %s ## %s ##\n",
           s.show_id, s.title, s.type, s.director, s.cast,
           s.country, s.date_added, s.release_year,
           s.rating, s.duration, s.listed_in);
}

void insercaoParcial(Show* v, int n, int k) {
    for (int i = 1; i < k && i < n; i++) {
        Show tmp = v[i];
        int j = i - 1;
        while (j >= 0 &&
              (strcmp(v[j].type, tmp.type) > 0 ||
              (strcmp(v[j].type, tmp.type) == 0 &&
               strcmp(v[j].title, tmp.title) > 0))) {
            v[j + 1] = v[j];
            j--;
            comparacoes++;
            movimentacoes++;
        }
        v[j + 1] = tmp;
        movimentacoes++;
    }
}

int main() {
    clock_t inicio = clock();

    Show* base = (Show*) malloc(MAX_SHOWS * sizeof(Show));
    Show* inseridos = (Show*) malloc(MAX_SHOWS * sizeof(Show));
    int totalBase = 0, totalInseridos = 0;
    char linha[MAX_LINE], entrada[200];

    FILE* file = fopen("/tmp/disneyplus.csv", "r");
    if (file == NULL) return 1;

    fgets(linha, MAX_LINE, file);
    while (fgets(linha, MAX_LINE, file) != NULL && totalBase < MAX_SHOWS) {
        linha[strcspn(linha, "\r\n")] = '\0';
        if (lerCSV(linha, &base[totalBase]) == 1) totalBase++;
    }
    fclose(file);

    while (fgets(entrada, sizeof(entrada), stdin) != NULL) {
        entrada[strcspn(entrada, "\r\n")] = '\0';
        if (strcmp(entrada, "FIM") == 0) break;

        for (int i = 0; i < totalBase; i++) {
            if (strcmp(base[i].show_id, entrada) == 0) {
                inseridos[totalInseridos++] = base[i];
            }
        }
    }

    insercaoParcial(inseridos, totalInseridos, 10);

    for (int i = 0; i < totalInseridos; i++) {
        imprimir_Show(inseridos[i]);
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    FILE* log = fopen("matricula_insercao.txt", "w");
    if (log != NULL) {
        fprintf(log, "793406\t%d\t%d\t%.6lf", comparacoes, movimentacoes, tempo);
        fclose(log);
    }

    free(base);
    free(inseridos);
    return 0;
}
