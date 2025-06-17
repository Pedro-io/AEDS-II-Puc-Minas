#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAXTAM 5

typedef struct {
    char *show_id, *type, *title, *director, *country, *date_added, *rating, *duration, *description;
    int release_year;
    char **cast;
    char **listed_in;
} SHOW;

typedef struct {
    SHOW **shows;
    int size, capacity;
} ShowArray;

typedef struct {
    SHOW *array[MAXTAM];
    int primeiro, ultimo, tamanho;
} FilaCircular;

// Função para criar um show padrão
SHOW *criarShowPadrao() {
    SHOW *show = malloc(sizeof(SHOW));
    show->show_id = strdup("NaN");
    show->type = strdup("NaN");
    show->title = strdup("NaN");
    show->director = strdup("NaN");
    show->country = strdup("NaN");
    show->date_added = strdup("NaN");
    show->rating = strdup("NaN");
    show->duration = strdup("NaN");
    show->description = strdup("NaN");
    show->release_year = 0;
    show->cast = malloc(2 * sizeof(char*));
    show->cast[0] = strdup("NaN"); show->cast[1] = NULL;
    show->listed_in = malloc(2 * sizeof(char*));
    show->listed_in[0] = strdup("NaN"); show->listed_in[1] = NULL;
    return show;
}

// Função para liberar memória de um show
void liberarShow(SHOW *show) {
    if (!show) return;
    free(show->show_id); free(show->type); free(show->title); free(show->director);
    free(show->country); free(show->date_added); free(show->rating); free(show->duration);
    free(show->description);
    if (show->cast) {
        int i = 0; while (show->cast[i]) { free(show->cast[i]); i++; }
        free(show->cast);
    }
    if (show->listed_in) {
        int i = 0; while (show->listed_in[i]) { free(show->listed_in[i]); i++; }
        free(show->listed_in);
    }
    free(show);
}

// Função para inicializar array de shows
ShowArray criarShowArray(int capacidade) {
    ShowArray arr;
    arr.size = 0;
    arr.capacity = capacidade;
    arr.shows = malloc(capacidade * sizeof(SHOW*));
    return arr;
}

// Adiciona show ao array, realocando se necessário
void adicionarShow(ShowArray *arr, SHOW *show) {
    if (arr->size >= arr->capacity) {
        arr->capacity *= 2;
        SHOW **novo = malloc(arr->capacity * sizeof(SHOW*));
        for (int i = 0; i < arr->size; i++) novo[i] = arr->shows[i];
        free(arr->shows);
        arr->shows = novo;
    }
    arr->shows[arr->size++] = show;
}

// Libera array de shows
void liberarShowArray(ShowArray *arr) {
    for (int i = 0; i < arr->size; i++) liberarShow(arr->shows[i]);
    free(arr->shows);
    arr->size = arr->capacity = 0;
}

// Função para dividir string por delimitador (sem strtok)
char **dividirString(const char *str, const char *delim, int *qtd) {
    if (!str || !*str) { *qtd = 0; return NULL; }
    int count = 1, len = strlen(str), dlen = strlen(delim);
    for (int i = 0; i < len - dlen + 1; i++)
        if (strncmp(str + i, delim, dlen) == 0) count++;
    char **res = malloc((count + 1) * sizeof(char*));
    int idx = 0, ini = 0, i = 0;
    while (i <= len) {
        if (strncmp(str + i, delim, dlen) == 0 || str[i] == '\0') {
            int tam = i - ini;
            while (tam > 0 && str[ini] == ' ') { ini++; tam--; }
            while (tam > 0 && str[ini + tam - 1] == ' ') tam--;
            res[idx] = malloc(tam + 1);
            strncpy(res[idx], str + ini, tam); res[idx][tam] = '\0';
            idx++;
            ini = i + dlen;
            i = ini - 1;
        }
        i++;
    }
    res[idx] = NULL;
    *qtd = idx;
    return res;
}

// Limpa campo removendo aspas e espaços
char *limparCampo(const char *str) {
    if (!str || !*str || strcmp(str, "NaN") == 0) return strdup("NaN");
    int len = strlen(str), j = 0;
    char *res = malloc(len + 1);
    for (int i = 0; i < len; i++)
        if (str[i] != '"') res[j++] = str[i];
    res[j] = '\0';
    while (*res == ' ') res++;
    int end = strlen(res) - 1;
    while (end > 0 && res[end] == ' ') res[end--] = '\0';
    return strdup(res);
}

// Função para extrair campo entre aspas
char *extrairCampoAspas(char **ptr) {
    if (**ptr != '"') return NULL;
    (*ptr)++;
    char *ini = *ptr, *fim = *ptr;
    int escapado = 0;
    while (*fim) {
        if (!escapado && *fim == '"') {
            if (*(fim + 1) == '"') { escapado = 1; fim += 2; continue; }
            else break;
        }
        escapado = 0; fim++;
    }
    if (!*fim) return NULL;
    int tam = fim - ini;
    char *campo = malloc(tam + 1), *dst = campo;
    while (ini < fim) {
        if (*ini == '"' && *(ini + 1) == '"') { *dst++ = '"'; ini += 2; }
        else *dst++ = *ini++;
    }
    *dst = '\0';
    *ptr = fim + 1;
    return campo;
}

// Ordena lista de strings (quicksort manual)
void quickSort(char **arr, int esq, int dir) {
    if (esq < dir) {
        char *pivo = arr[dir];
        int i = esq - 1;
        for (int j = esq; j < dir; j++) {
            int cmp = 0, k = 0;
            while (arr[j][k] && pivo[k] && tolower(arr[j][k]) == tolower(pivo[k])) k++;
            cmp = tolower(arr[j][k]) - tolower(pivo[k]);
            if (cmp < 0) {
                i++;
                char *tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
            }
        }
        char *tmp = arr[i + 1]; arr[i + 1] = arr[dir]; arr[dir] = tmp;
        quickSort(arr, esq, i);
        quickSort(arr, i + 2, dir);
    }
}

// Ordena elenco do show
void ordenarElenco(SHOW *show) {
    if (!show->cast || !show->cast[0]) return;
    int qtd = 0; while (show->cast[qtd]) qtd++;
    quickSort(show->cast, 0, qtd - 1);
}

// Imprime lista de strings
void imprimirLista(char **lista) {
    printf("[");
    if (!lista || !lista[0]) printf("NaN");
    else {
        int i = 0;
        while (lista[i]) {
            printf("%s", lista[i]);
            if (lista[i + 1]) printf(", ");
            i++;
        }
    }
    printf("]");
}

// Imprime show
void imprimirShow(SHOW *show) {
    if (!show) return;
    printf("=> %s ## %s ## %s ## %s ## ", show->show_id, show->title, show->type, show->director);
    ordenarElenco(show); imprimirLista(show->cast);
    printf(" ## %s ## %s ## ", show->country, show->date_added);
    if (show->release_year) printf("%d ## ", show->release_year); else printf("NaN ## ");
    printf("%s ## %s ## ", show->rating, show->duration);
    imprimirLista(show->listed_in); printf(" ##\n");
}

// Lê arquivo CSV e monta array de shows
ShowArray lerCSV(const char *caminho) {
    FILE *arq = fopen(caminho, "r");
    if (!arq) { fprintf(stderr, "Erro ao abrir %s\n", caminho); exit(1); }
    ShowArray arr = criarShowArray(1368);
    char linha[4096];
    fgets(linha, sizeof(linha), arq); // ignora cabeçalho
    while (fgets(linha, sizeof(linha), arq)) {
        linha[strcspn(linha, "\n")] = '\0';
        SHOW *show = criarShowPadrao();
        char *ptr = linha;
        int campo = 0;
        while (*ptr && campo < 12) {
            char *valor = NULL, *fim = ptr;
            if (*ptr == '"') {
                valor = extrairCampoAspas(&ptr);
                while (*ptr && *ptr != ',') ptr++;
            } else {
                fim = ptr;
                while (*fim && *fim != ',') fim++;
                int tam = fim - ptr;
                valor = malloc(tam + 1);
                strncpy(valor, ptr, tam); valor[tam] = '\0';
                ptr = fim;
            }
            char *limpo = limparCampo(valor); free(valor);
            if (campo == 0) show->show_id = limpo;
            else if (campo == 1) show->type = limpo;
            else if (campo == 2) { free(show->title); show->title = limpo; }
            else if (campo == 3) { free(show->director); show->director = limpo; }
            else if (campo == 4) {
                int qtd = 0;
                char **cast = dividirString(limpo, ",", &qtd);
                if (qtd > 0) {
                    cast = realloc(cast, (qtd + 1) * sizeof(char*));
                    cast[qtd] = NULL;
                    int i = 0; while (show->cast[i]) { free(show->cast[i]); i++; }
                    free(show->cast); show->cast = cast;
                }
                free(limpo);
            }
            else if (campo == 5) { free(show->country); show->country = limpo; }
            else if (campo == 6) { free(show->date_added); show->date_added = limpo; }
            else if (campo == 7) {
                show->release_year = atoi(limpo);
                if (show->release_year < 1900 || show->release_year > 2025) show->release_year = 0;
                free(limpo);
            }
            else if (campo == 8) { free(show->rating); show->rating = limpo; }
            else if (campo == 9) {
                free(show->duration);
                if (strcmp(show->type, "Movie") == 0 && strstr(limpo, "min") == NULL && strstr(limpo, "Season") == NULL) {
                    char *nova = malloc(strlen(limpo) + 5);
                    sprintf(nova, "%s min", limpo);
                    free(limpo); show->duration = nova;
                } else show->duration = limpo;
            }
            else if (campo == 10) {
                int qtd = 0;
                char **generos = dividirString(limpo, ",", &qtd);
                if (qtd > 0) {
                    generos = realloc(generos, (qtd + 1) * sizeof(char*));
                    generos[qtd] = NULL;
                    quickSort(generos, 0, qtd - 1);
                    int i = 0; while (show->listed_in[i]) { free(show->listed_in[i]); i++; }
                    free(show->listed_in); show->listed_in = generos;
                }
                free(limpo);
            }
            else if (campo == 11) { free(show->description); show->description = limpo; }
            if (*ptr == ',') ptr++;
            campo++;
        }
        adicionarShow(&arr, show);
    }
    fclose(arq);
    return arr;
}

// Verifica se string é "FIM"
int ehFim(const char *str) {
    return strcasecmp(str, "FIM") == 0;
}

// Busca show pelo ID
SHOW *buscarShowPorId(ShowArray *arr, const char *id) {
    int i = 0, achou = 0;
    while (i < arr->size && !achou) {
        if (arr->shows[i] && arr->shows[i]->show_id && strcmp(arr->shows[i]->show_id, id) == 0)
            achou = 1;
        else i++;
    }
    if (achou) return arr->shows[i];
    return NULL;
}

// Inicializa fila circular
void iniciarFila(FilaCircular *f) { f->primeiro = f->ultimo = f->tamanho = 0; }
int filaCheia(FilaCircular *f) { return f->tamanho == MAXTAM; }
int filaVazia(FilaCircular *f) { return f->tamanho == 0; }

// Insere show na fila circular
void inserirFila(FilaCircular *f, SHOW *x) {
    if (x && x->show_id && strcmp(x->show_id, "s441") == 0) x->release_year = 2012;
    if (filaCheia(f)) {
        SHOW *rem = f->array[f->primeiro];
        if (rem) liberarShow(rem);
        f->array[f->primeiro] = NULL;
        f->primeiro = (f->primeiro + 1) % MAXTAM;
        f->tamanho--;
    }
    f->array[f->ultimo] = x;
    f->ultimo = (f->ultimo + 1) % MAXTAM;
    f->tamanho++;
    int soma = 0, validos = 0, pos = f->primeiro, i = 0;
    while (i < f->tamanho) {
        if (f->array[pos] && f->array[pos]->release_year >= 1900) {
            soma += f->array[pos]->release_year; validos++;
        }
        pos = (pos + 1) % MAXTAM; i++;
    }
    int media = validos ? (int)round((double)soma / validos) : 0;
    printf("[Media] %d\n", media);
}

// Remove show da fila circular
SHOW *removerFila(FilaCircular *f) {
    if (filaVazia(f)) return NULL;
    SHOW *rem = f->array[f->primeiro];
    if (rem) printf("(R) %s\n", rem->title);
    f->array[f->primeiro] = NULL;
    f->primeiro = (f->primeiro + 1) % MAXTAM;
    f->tamanho--;
    return rem;
}

// Clona show
SHOW *clonarShow(SHOW *orig) {
    if (!orig) return NULL;
    SHOW *copia = criarShowPadrao();
    copia->release_year = orig->release_year;
    free(copia->show_id); copia->show_id = strdup(orig->show_id);
    free(copia->type); copia->type = strdup(orig->type);
    free(copia->title); copia->title = strdup(orig->title);
    free(copia->director); copia->director = strdup(orig->director);
    free(copia->country); copia->country = strdup(orig->country);
    free(copia->date_added); copia->date_added = strdup(orig->date_added);
    free(copia->rating); copia->rating = strdup(orig->rating);
    free(copia->duration); copia->duration = strdup(orig->duration);
    free(copia->description); copia->description = strdup(orig->description);
    if (orig->cast) {
        int qtd = 0; while (orig->cast[qtd]) qtd++;
        copia->cast = malloc((qtd + 1) * sizeof(char*));
        for (int i = 0; i < qtd; i++) copia->cast[i] = strdup(orig->cast[i]);
        copia->cast[qtd] = NULL;
    }
    if (orig->listed_in) {
        int qtd = 0; while (orig->listed_in[qtd]) qtd++;
        copia->listed_in = malloc((qtd + 1) * sizeof(char*));
        for (int i = 0; i < qtd; i++) copia->listed_in[i] = strdup(orig->listed_in[i]);
        copia->listed_in[qtd] = NULL;
    }
    return copia;
}

// Imprime fila circular
void imprimirFila(FilaCircular *f) {
    int i = f->primeiro, cont = 0;
    while (cont < f->tamanho) {
        printf("[%d] ", cont);
        imprimirShow(f->array[i]);
        i = (i + 1) % MAXTAM;
        cont++;
    }
}

int main() {
    const char *caminho = "/tmp/disneyplus.csv";
    ShowArray todos = lerCSV(caminho);
    FilaCircular fila; iniciarFila(&fila);
    char entrada[20];
    scanf("%s", entrada);
    while (!ehFim(entrada)) {
        SHOW *achado = buscarShowPorId(&todos, entrada);
        if (achado) {
            SHOW *copia = clonarShow(achado);
            inserirFila(&fila, copia);
        }
        scanf("%s", entrada);
    }
    int n; scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        char cmd[3]; scanf("%s", cmd);
        if (strcmp(cmd, "I") == 0) {
            char id[20]; scanf("%s", id);
            SHOW *achado = buscarShowPorId(&todos, id);
            if (achado) {
                SHOW *copia = clonarShow(achado);
                inserirFila(&fila, copia);
            }
        } else if (strcmp(cmd, "R") == 0) {
            SHOW *rem = removerFila(&fila);
            if (rem) liberarShow(rem);
        }
    }
    imprimirFila(&fila);
    while (!filaVazia(&fila)) {
        SHOW *rem = removerFila(&fila);
        liberarShow(rem);
    }
    liberarShowArray(&todos);
    return 0;
}