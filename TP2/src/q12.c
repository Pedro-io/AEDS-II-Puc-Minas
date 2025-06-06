#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define MAX_SHOWS 5000
#define MAX_LINE 1000

int comparacoes = 0;
int movimentacoes = 0;

typedef struct {
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
    int i = 0, j = 0;
    char temp[strlen(str) + 1];
    while (str[i] != '\0') {
        if (str[i] != '"') {
            temp[j] = str[i];
            j++;
        }
        i++;
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

void ordenarEUnir(char* campo) {
    if (strcmp(campo, "NaN") == 0 || strlen(campo) == 0) return;
    char* tokens[50];
    int count = 0;
    char* token = strtok(campo, ",");
    while (token != NULL && count < 50) {
        trim(token);
        tokens[count] = strdup(token);
        count++;
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
        free(tokens[i]);
    }
}

int lerCSV(char* linha, Show* s) {
    char* campos[20];
    int i = 0, in_quotes = 0;
    char* p = strtok(linha, ",");
    char buffer[300] = "";
    while (p != NULL) {
        if (in_quotes || strchr(p, '"') != NULL) {
            strcat(buffer, p);
            if (strchr(p, '"') != NULL) in_quotes = !in_quotes;
            if (in_quotes == 0) {
                limparAspas(buffer);
                campos[i] = strdup(buffer);
                i++;
                buffer[0] = '\0';
            } else {
                strcat(buffer, ",");
            }
        } else {
            campos[i] = strdup(p);
            i++;
        }
        p = strtok(NULL, ",");
    }

    if (i > 0) strcpy(s->show_id, campos[0]); else strcpy(s->show_id, "NaN");
    if (i > 1) strcpy(s->type, campos[1]); else strcpy(s->type, "NaN");
    if (i > 2) strcpy(s->title, campos[2]); else strcpy(s->title, "NaN");
    if (i > 3) strcpy(s->director, campos[3]); else strcpy(s->director, "NaN");
    if (i > 4) strcpy(s->cast, campos[4]); else strcpy(s->cast, "NaN");
    if (i > 5) strcpy(s->country, campos[5]); else strcpy(s->country, "NaN");
    if (i > 6) strcpy(s->date_added, campos[6]); else strcpy(s->date_added, "NaN");
    if (i > 7 && strcmp(campos[7], "") != 0) s->release_year = atoi(campos[7]);
    else s->release_year = 0;
    if (i > 8) strcpy(s->rating, campos[8]); else strcpy(s->rating, "NaN");
    if (i > 9) strcpy(s->duration, campos[9]); else strcpy(s->duration, "NaN");
    if (i > 10) strcpy(s->listed_in, campos[10]); else strcpy(s->listed_in, "NaN");

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

int compararData(const char* d1, const char* d2) {
    if (strcmp(d1, "NaN") == 0 && strcmp(d2, "NaN") != 0) return -1;
    if (strcmp(d1, "NaN") != 0 && strcmp(d2, "NaN") == 0) return 1;
    return strcmp(d1, d2);
}

void bubbleSort(Show* v, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (compararData(v[j].date_added, v[j + 1].date_added) > 0 ||
                (compararData(v[j].date_added, v[j + 1].date_added) == 0 &&
                 strcmp(v[j].title, v[j + 1].title) > 0)) {
                Show temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
                movimentacoes += 3;
            }
        }
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

    int lendo = 1;
    while (lendo == 1 && fgets(entrada, sizeof(entrada), stdin) != NULL) {
        entrada[strcspn(entrada, "\r\n")] = '\0';
        if (strcmp(entrada, "FIM") == 0) lendo = 0;
        else {
            int i = 0, achou = 0;
            while (i < totalBase) {
                if (achou == 0 && strcmp(base[i].show_id, entrada) == 0) {
                    inseridos[totalInseridos] = base[i];
                    totalInseridos++;
                    achou = 1;
                }
                i++;
            }
        }
    }

    bubbleSort(inseridos, totalInseridos);

    for (int i = 0; i < totalInseridos; i++) {
        imprimir_Show(inseridos[i]);
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    FILE* log = fopen("matricula_bolha.txt", "w");
    if (log != NULL) {
        fprintf(log, "793406\t%d\t%d\t%.6lf", comparacoes, movimentacoes, tempo);
        fclose(log);
    }

    free(base);
    free(inseridos);
    return 0;
}
