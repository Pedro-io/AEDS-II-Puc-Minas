#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_SHOWS 5000
#define MAX_LINE 1000

int comparacoes = 0;

typedef struct Show
{
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
    char listed_in[200];
} Show;

int lerCSV(char *linha, Show *s)
{
    char *token;
    int campo = 0;

    token = strtok(linha, ",");
    while (token != NULL)
    {
        if (campo == 0)
            strcpy(s->show_id, token);
        if (campo == 1)
            strcpy(s->type, token);
        if (campo == 2)
            strcpy(s->title, token);
        if (campo == 3)
            strcpy(s->director, token);
        if (campo == 4)
            strcpy(s->cast, token);
        if (campo == 5)
            strcpy(s->country, token);
        if (campo == 6)
            strcpy(s->date_added, token);
        if (campo == 7)
            s->release_year = atoi(token);
        if (campo == 8)
            strcpy(s->rating, token);
        if (campo == 9)
            strcpy(s->duration, token);
        if (campo == 10)
            strcpy(s->listed_in, token);
        token = strtok(NULL, ",");
        campo++;
    }

    return campo >= 11;
}

void insertionSort(Show *v, int n)
{
    int i, j;
    Show tmp;
    for (i = 1; i < n; i++)
    {
        tmp = v[i];
        j = i - 1;
        while (j >= 0 && strcmp(v[j].title, tmp.title) > 0)
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = tmp;
    }
}

int buscaBinaria(Show *v, int n, char *chave)
{
    int esq = 0;
    int dir = n - 1;
    int meio;
    int encontrou = 0;

    while (esq <= dir && encontrou == 0)
    {
        meio = (esq + dir) / 2;
        comparacoes++;
        int cmp = strcmp(v[meio].title, chave);

        if (cmp == 0)
        {
            encontrou = 1;
        }
        else
        {
            if (cmp < 0)
            {
                esq = meio + 1;
            }
            else
            {
                dir = dir - 1;
            }
        }
    }

    return encontrou;
}

int main()
{
    clock_t inicio = clock();

    Show *base = (Show *)malloc(MAX_SHOWS * sizeof(Show));
    Show *inseridos = (Show *)malloc(MAX_SHOWS * sizeof(Show));
    int totalBase = 0;
    int totalInseridos = 0;
    char linha[MAX_LINE];
    char entrada[300];

    FILE *file = fopen("/tmp/disneyplus.csv", "r");
    if (file == NULL)
        return 1;

    fgets(linha, MAX_LINE, file); // pula cabeçalho

    while (fgets(linha, MAX_LINE, file) != NULL && totalBase < MAX_SHOWS)
    {
        linha[strcspn(linha, "\r\n")] = '\0';
        if (lerCSV(linha, &base[totalBase]) == 1)
        {
            totalBase++;
        }
    }
    fclose(file);

    // PRIMEIRA PARTE: insercao por show_id
    int lendoIds = 1;
    while (lendoIds == 1 && fgets(entrada, sizeof(entrada), stdin) != NULL)
    {
        entrada[strcspn(entrada, "\r\n")] = '\0';
        if (strcmp(entrada, "FIM") == 0)
        {
            lendoIds = 0;
        }
        else
        {
            int i = 0;
            int achou = 0;
            while (i < totalBase)
            {
                if (achou == 0 && strcmp(base[i].show_id, entrada) == 0)
                {
                    inseridos[totalInseridos] = base[i];
                    totalInseridos++;
                    achou = 1;
                }
                i = i + 1;
            }
        }
    }

    insertionSort(inseridos, totalInseridos);

    // SEGUNDA PARTE: busca binaria por title
    int achou = buscaBinaria(inseridos, totalInseridos, entrada);
    if (achou == 1)
    {
        printf("SIM\n");
    }
    else
    {
        printf("NAO\n");
    }


    int lendoTitulos = 1;
    while (lendoTitulos == 1 && fgets(entrada, sizeof(entrada), stdin) != NULL)
    {
        entrada[strcspn(entrada, "\r\n")] = '\0';
        if (strcmp(entrada, "FIM") == 0)
        {
            lendoTitulos = 0;
        }
        else
        {
            achou = buscaBinaria(inseridos, totalInseridos, entrada);
            if (achou == 1)
            {
                printf("SIM\n");
            }
            else
            {
                printf("NAO\n");
            }
        }
    }

    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;

    FILE *log = fopen("793406_binaria.txt", "w");
    if (log != NULL)
    {
        fprintf(log, "793406\t%.6lf\t%d", tempo, comparacoes);
        fclose(log);
    }

    free(base);
    free(inseridos);

    return 0;
}
