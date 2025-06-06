#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


void ordenarLista(char* campo) {
    if (strcmp(campo, "NaN") == 0) return;

    char copia[400];
    strcpy(copia, campo);

    char* elementos[50];
    int qtd = 0;

    char* token = strtok(copia, ",");
    while (token != NULL && qtd < 50) {
        while (*token == ' ') token++;  // trim left
        elementos[qtd++] = token;
        token = strtok(NULL, ",");
    }

    for (int i = 0; i < qtd - 1; i++) {
        for (int j = i + 1; j < qtd; j++) {
            if (strcmp(elementos[i], elementos[j]) > 0) {
                char* temp = elementos[i];
                elementos[i] = elementos[j];
                elementos[j] = temp;
            }
        }
    }

    campo[0] = '\0';
    for (int i = 0; i < qtd; i++) {
        strcat(campo, elementos[i]);
        if (i < qtd - 1) strcat(campo, ", ");
    }
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
                int j = 0, k = 0;
                while (buffer[j]) {
                    if (buffer[j] != '"') {
                        buffer[k++] = buffer[j];
                    }
                    j++;
                }
                buffer[k] = '\0';
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
    if (i > 7 && strcmp(campos[7], "") != 0) s->release_year = atoi(campos[7]); else s->release_year = 0;
    if (i > 8) strcpy(s->rating, campos[8]); else strcpy(s->rating, "NaN");
    if (i > 9) strcpy(s->duration, campos[9]); else strcpy(s->duration, "NaN");
    if (i > 10) strcpy(s->listed_in, campos[10]); else strcpy(s->listed_in, "NaN");

    ordenarLista(s->cast);
    ordenarLista(s->listed_in);

    for (int j = 0; j < i; j++) {
        free(campos[j]);
    }

    return 1;
}

void imprimir_Show(Show s) {
    printf("=> %s ## %s ## %s ## %s ## [%s] ## %s ## %s ## %d ## %s ## %s ## [%s] ##\n",
           s.show_id, s.title, s.type, s.director, s.cast,
           s.country, s.date_added, s.release_year,
           s.rating, s.duration, s.listed_in);
}

void shellSort(Show* v, int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Show temp = v[i];
            int j = i;

            while (j >= gap &&
                  (strcmp(v[j - gap].type, temp.type) > 0 ||
                  (strcmp(v[j - gap].type, temp.type) == 0 &&
                   strcmp(v[j - gap].title, temp.title) > 0))) {
                v[j] = v[j - gap];
                j -= gap;
                comparacoes++;
                movimentacoes++;
            }

            v[j] = temp;
            movimentacoes++;
        }
    }
}

int main() {
    clock_t inicio = clock();

    Show* base = (Show*) malloc(MAX_SHOWS * sizeof(Show));
    Show* inseridos = (Show*) malloc(MAX_SHOWS * sizeof(Show));
    int totalBase = 0;
    int totalInseridos = 0;
    char linha[MAX_LINE];
    char entrada[200];

    FILE* file = fopen("/tmp/disneyplus.csv", "r");
    if (file == NULL) return 1;

    fgets(linha, MAX_LINE, file);
    while (fgets(linha, MAX_LINE, file) != NULL && totalBase < MAX_SHOWS) {
        linha[strcspn(linha, "\r\n")] = '\0';
        if (lerCSV(linha, &base[totalBase]) == 1) {
            totalBase++;
        }
    }
    fclose(file);

    int lendoIds = 1;
    while (lendoIds == 1 && fgets(entrada, sizeof(entrada), stdin) != NULL) {
        entrada[strcspn(entrada, "\r\n")] = '\0';
        if (strcmp(entrada, "FIM") == 0) {
            lendoIds = 0;
        } else {
            int i = 0;
            int achou = 0;
            while (i < totalBase) {
                if (achou == 0 && strcmp(base[i].show_id, entrada) == 0) {
                    inseridos[totalInseridos++] = base[i];
                    achou = 1;
                }
                i++;
            }
        }
    }

    shellSort(inseridos, totalInseridos);

    for (int i = 0; i < totalInseridos; i++) {
        imprimir_Show(inseridos[i]);
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    FILE* log = fopen("matricula_shellsort.txt", "w");
    if (log != NULL) {
        fprintf(log, "793406\t%d\t%d\t%.6lf", comparacoes, movimentacoes, tempo);
        fclose(log);
    }

    free(base);
    free(inseridos);
    return 0;
}
