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

    char* tokens[50];
    int count = 0;
    char* token = strtok(campo, ",");
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

    campo[0] = '\0';
    for (int i = 0; i < count; i++) {
        strcat(campo, tokens[i]);
        if (i < count - 1) strcat(campo, ", ");
        free(tokens[i]);
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
                    if (buffer[j] != '"') buffer[k++] = buffer[j];
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
            campos[i++] = strdup(p);
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

void countingSortPorDigito(Show* arr, int n, int exp) {
    Show output[n];
    int count[10] = {0};

    for (int i = 0; i < n; i++) count[(arr[i].release_year / exp) % 10]++;
    for (int i = 1; i < 10; i++) count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i].release_year / exp) % 10] - 1] = arr[i];
        count[(arr[i].release_year / exp) % 10]--;
        movimentacoes++;
    }

    for (int i = 0; i < n; i++) arr[i] = output[i];
}

void stableSortPorTitle(Show* arr, int n) {
    for (int i = 1; i < n; i++) {
        Show temp = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].release_year == temp.release_year && strcmp(arr[j].title, temp.title) > 0) {
            arr[j + 1] = arr[j];
            j--;
            movimentacoes++;
            comparacoes++;
        }
        arr[j + 1] = temp;
        movimentacoes++;
    }
}

void radixSort(Show* arr, int n) {
    int max = arr[0].release_year;
    for (int i = 1; i < n; i++) if (arr[i].release_year > max) max = arr[i].release_year;

    for (int exp = 1; max / exp > 0; exp *= 10)
        countingSortPorDigito(arr, n, exp);

    stableSortPorTitle(arr, n);
}

int main() {
    clock_t inicio = clock();
    Show* base = (Show*) malloc(MAX_SHOWS * sizeof(Show));
    Show* inseridos = (Show*) malloc(MAX_SHOWS * sizeof(Show));
    int totalBase = 0, totalInseridos = 0;
    char linha[MAX_LINE];
    char entrada[200];

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

    radixSort(inseridos, totalInseridos);

    for (int i = 0; i < totalInseridos; i++) imprimir_Show(inseridos[i]);

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    FILE* log = fopen("matricula_radixsort.txt", "w");
    if (log != NULL) {
        fprintf(log, "793406\t%d\t%d\t%.6lf\n", comparacoes, movimentacoes, tempo);
        fprintf(log, "Radix Sort ÃRadix Sort \xC3©Radix Sort \xC3\xA9 um algoritmo de ordenaÃRadix Sort \xC3\xA9 um algoritmo de ordena\xC3§Radix Sort \xC3\xA9 um algoritmo de ordena\xC3\xA7ÃRadix Sort \xC3\xA9 um algoritmo de ordena\xC3\xA7\xC3£Radix Sort \xC3\xA9 um algoritmo de ordena\xC3\xA7\xC3\xA3o nÃRadix Sort \xC3\xA9 um algoritmo de ordena\xC3\xA7\xC3\xA3o n\xC3£Radix Sort \xC3\xA9 um algoritmo de ordena\xC3\xA7\xC3\xA3o n\xC3\xA3o comparativo, usado para ordenar inteiros (ou dados que podem ser tratados como inteiros).\n");
        fprintf(log, "Ele processa os nÃEle processa os n\xC3ºEle processa os n\xC3\xBAmeros dÃEle processa os n\xC3\xBAmeros d\xC3­Ele processa os n\xC3\xBAmeros d\xC3\xADgito por dÃEle processa os n\xC3\xBAmeros d\xC3\xADgito por d\xC3­Ele processa os n\xC3\xBAmeros d\xC3\xADgito por d\xC3\xADgito, da menor para a maior casa decimal (da direita para a esquerda), utilizando um algoritmo\n");
        fprintf(log, "estÃest\xC3¡est\xC3\xA1vel como o Counting Sort em cada passo.\n\n");
        fprintf(log, "Este algoritmo foi utilizado para ordenar os registros do arquivo 'disneyplus.csv' com base no campo 'release_year'.\n");
        fprintf(log, "Como critÃComo crit\xC3©Como crit\xC3\xA9rio de desempate, utilizamos o atributo 'title' com ordenaÃComo crit\xC3\xA9rio de desempate, utilizamos o atributo 'title' com ordena\xC3§Como crit\xC3\xA9rio de desempate, utilizamos o atributo 'title' com ordena\xC3\xA7ÃComo crit\xC3\xA9rio de desempate, utilizamos o atributo 'title' com ordena\xC3\xA7\xC3£Como crit\xC3\xA9rio de desempate, utilizamos o atributo 'title' com ordena\xC3\xA7\xC3\xA3o estÃComo crit\xC3\xA9rio de desempate, utilizamos o atributo 'title' com ordena\xC3\xA7\xC3\xA3o est\xC3¡Como crit\xC3\xA9rio de desempate, utilizamos o atributo 'title' com ordena\xC3\xA7\xC3\xA3o est\xC3\xA1vel adicional ao final do Radix Sort.\n\n");
        fprintf(log, "Complexidade:\n");
        fprintf(log, "- Tempo: O(n * k), onde n Ã- Tempo: O(n * k), onde n \xC3©- Tempo: O(n * k), onde n \xC3\xA9 o nÃ- Tempo: O(n * k), onde n \xC3\xA9 o n\xC3º- Tempo: O(n * k), onde n \xC3\xA9 o n\xC3\xBAmero de elementos e k Ã- Tempo: O(n * k), onde n \xC3\xA9 o n\xC3\xBAmero de elementos e k \xC3©- Tempo: O(n * k), onde n \xC3\xA9 o n\xC3\xBAmero de elementos e k \xC3\xA9 o nÃ- Tempo: O(n * k), onde n \xC3\xA9 o n\xC3\xBAmero de elementos e k \xC3\xA9 o n\xC3º- Tempo: O(n * k), onde n \xC3\xA9 o n\xC3\xBAmero de elementos e k \xC3\xA9 o n\xC3\xBAmero de dÃ- Tempo: O(n * k), onde n \xC3\xA9 o n\xC3\xBAmero de elementos e k \xC3\xA9 o n\xC3\xBAmero de d\xC3­- Tempo: O(n * k), onde n \xC3\xA9 o n\xC3\xBAmero de elementos e k \xC3\xA9 o n\xC3\xBAmero de d\xC3\xADgitos do maior valor.\n");
        fprintf(log, "- EspaÃ- Espa\xC3§- Espa\xC3\xA7o: O(n + k), dependendo da implementaÃ- Espa\xC3\xA7o: O(n + k), dependendo da implementa\xC3§- Espa\xC3\xA7o: O(n + k), dependendo da implementa\xC3\xA7Ã- Espa\xC3\xA7o: O(n + k), dependendo da implementa\xC3\xA7\xC3£- Espa\xC3\xA7o: O(n + k), dependendo da implementa\xC3\xA7\xC3\xA3o do Counting Sort utilizado.\n");
        fprintf(log, "- Ã- \xC3- \xC3\x89 eficiente quando k Ã- \xC3\x89 eficiente quando k \xC3©- \xC3\x89 eficiente quando k \xC3\xA9 relativamente pequeno em relaÃ- \xC3\x89 eficiente quando k \xC3\xA9 relativamente pequeno em rela\xC3§- \xC3\x89 eficiente quando k \xC3\xA9 relativamente pequeno em rela\xC3\xA7Ã- \xC3\x89 eficiente quando k \xC3\xA9 relativamente pequeno em rela\xC3\xA7\xC3£- \xC3\x89 eficiente quando k \xC3\xA9 relativamente pequeno em rela\xC3\xA7\xC3\xA3o a n.\n");
        fclose(log);
    }

    free(base);
    free(inseridos);
    return 0;
}
