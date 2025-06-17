#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Estrutura para armazenar informações de um show
typedef struct {
    char *id;
    char *genero;
    char *nome;
    char *autor;
    char **atores;
    char *origem;
    char *adicionado_em;
    int ano;
    char *faixa_etaria;
    char *tempo;
    char **tags;
    char *sinopse;
} Show;

// Estrutura para coleção dinâmica de shows
typedef struct {
    Show **dados;
    int qtd;
    int max;
} Colecao;

// Fila circular de shows (tamanho fixo)
typedef struct {
    Show *itens[5];
    int inicio;
    int fim;
    int total;
} FilaShow;

// Função para criar um novo show com valores padrão
Show* criarShow() {
    Show *s = malloc(sizeof(Show));
    s->id = strdup("NaN");
    s->genero = strdup("NaN");
    s->nome = strdup("NaN");
    s->autor = strdup("NaN");
    s->atores = malloc(2 * sizeof(char*));
    s->atores[0] = strdup("NaN");
    s->atores[1] = NULL;
    s->origem = strdup("NaN");
    s->adicionado_em = strdup("NaN");
    s->ano = 0;
    s->faixa_etaria = strdup("NaN");
    s->tempo = strdup("NaN");
    s->tags = malloc(2 * sizeof(char*));
    s->tags[0] = strdup("NaN");
    s->tags[1] = NULL;
    s->sinopse = strdup("NaN");
    return s;
}

// Libera memória de um show
void liberarShow(Show *s) {
    if (!s) return;
    free(s->id); free(s->genero); free(s->nome); free(s->autor);
    free(s->origem); free(s->adicionado_em); free(s->faixa_etaria);
    free(s->tempo); free(s->sinopse);
    if (s->atores) { for (int i = 0; s->atores[i]; i++) free(s->atores[i]); free(s->atores); }
    if (s->tags) { for (int i = 0; s->tags[i]; i++) free(s->tags[i]); free(s->tags); }
    free(s);
}

// Função para copiar um show
Show* copiarShow(Show *orig) {
    Show *novo = criarShow();
    free(novo->id); novo->id = strdup(orig->id);
    free(novo->genero); novo->genero = strdup(orig->genero);
    free(novo->nome); novo->nome = strdup(orig->nome);
    free(novo->autor); novo->autor = strdup(orig->autor);
    free(novo->origem); novo->origem = strdup(orig->origem);
    free(novo->adicionado_em); novo->adicionado_em = strdup(orig->adicionado_em);
    novo->ano = orig->ano;
    free(novo->faixa_etaria); novo->faixa_etaria = strdup(orig->faixa_etaria);
    free(novo->tempo); novo->tempo = strdup(orig->tempo);
    free(novo->sinopse); novo->sinopse = strdup(orig->sinopse);
    int i = 0;
    while (orig->atores && orig->atores[i]) i++;
    novo->atores = malloc((i+1)*sizeof(char*));
    for (int j = 0; j < i; j++) novo->atores[j] = strdup(orig->atores[j]);
    novo->atores[i] = NULL;
    i = 0;
    while (orig->tags && orig->tags[i]) i++;
    novo->tags = malloc((i+1)*sizeof(char*));
    for (int j = 0; j < i; j++) novo->tags[j] = strdup(orig->tags[j]);
    novo->tags[i] = NULL;
    return novo;
}

// Inicializa a fila circular de shows
void inicializarFila(FilaShow *fila) {
    fila->inicio = 0;
    fila->fim = 0;
    fila->total = 0;
    for (int i = 0; i < 5; i++) fila->itens[i] = NULL;
}

// Insere um show na fila circular, removendo o mais antigo se cheia
void inserirFilaShow(FilaShow *fila, Show *s) {
    if (fila->total == 5) {
        Show *removido = fila->itens[fila->inicio];
        printf("(R) %s\n", removido->nome);
        liberarShow(removido);
        fila->inicio = (fila->inicio + 1) % 5;
        fila->total--;
    }
    fila->itens[fila->fim] = copiarShow(s);
    fila->fim = (fila->fim + 1) % 5;
    fila->total++;

    // Calcula e imprime a média dos anos dos shows na fila
    int soma = 0, cont = 0, idx = fila->inicio;
    for (int i = 0; i < fila->total; i++) {
        if (fila->itens[idx]->ano) {
            soma += fila->itens[idx]->ano;
            cont++;
        }
        idx = (idx + 1) % 5;
    }
    if (cont > 0)
        printf("%d\n", (int)((soma/(float)cont)+0.5));
    else
        printf("NaN\n");
}

// Remove o show mais antigo da fila circular
Show* removerFilaShow(FilaShow *fila) {
    if (fila->total == 0) return NULL;
    Show *rem = fila->itens[fila->inicio];
    fila->inicio = (fila->inicio + 1) % 5;
    fila->total--;
    return rem;
}

// Exibe todos os shows da fila circular
void mostrarFilaShow(FilaShow *fila);

// Funções auxiliares para parsing e exibição (mantidas do código original)
char **dividirString(const char *str, const char *sep, int *qtd) {
    if (!str || strlen(str) == 0) { *qtd = 0; return NULL; }
    char *copia = strdup(str);
    if (!copia) return NULL;
    *qtd = 1;
    char *p = copia;
    while ((p = strstr(p, sep))) { (*qtd)++; p += strlen(sep); }
    char **saida = malloc((*qtd + 1) * sizeof(char *));
    if (!saida) { free(copia); return NULL; }
    int i = 0;
    char *tok = strtok(copia, sep);
    while (tok) {
        while (*tok == ' ') tok++;
        int tam = strlen(tok);
        while (tam > 0 && tok[tam - 1] == ' ') tok[--tam] = '\0';
        saida[i++] = strdup(tok);
        tok = strtok(NULL, sep);
    }
    saida[i] = NULL;
    free(copia);
    return saida;
}

// Ordenação dos atores (quicksort)
int particionar(char *arr[], int esq, int dir) {
    char *pivo = arr[dir];
    int i = esq - 1;
    for (int j = esq; j < dir; j++) {
        if (strcasecmp(arr[j], pivo) < 0) {
            i++;
            char *tmp = arr[i]; arr[i] = arr[j]; arr[j] = tmp;
        }
    }
    char *tmp = arr[i + 1]; arr[i + 1] = arr[dir]; arr[dir] = tmp;
    return i + 1;
}
void quicksort(char *arr[], int esq, int dir) {
    if (esq < dir) {
        int p = particionar(arr, esq, dir);
        quicksort(arr, esq, p - 1);
        quicksort(arr, p + 1, dir);
    }
}
void ordenarAtores(Show *s) {
    if (!s->atores || !s->atores[0]) return;
    int n = 0; while (s->atores[n]) n++;
    quicksort(s->atores, 0, n - 1);
}

// Exibe lista de strings
void exibirLista(char **lista) {
    printf("[");
    if (!lista || !lista[0]) printf("NaN");
    else {
        for (int i = 0; lista[i]; i++) {
            printf("%s", lista[i]);
            if (lista[i + 1]) printf(", ");
        }
    }
    printf("]");
}

// Exibe informações de um show
void exibirShow(Show *s) {
    if (!s) return;
    printf("=> %s ## ", s->id ? s->id : "NaN");
    printf("%s ## ", s->nome ? s->nome : "NaN");
    printf("%s ## ", s->genero ? s->genero : "NaN");
    printf("%s ## ", s->autor ? s->autor : "NaN");
    ordenarAtores(s);
    exibirLista(s->atores);
    printf(" ## %s ## ", s->origem ? s->origem : "NaN");
    printf("%s ## ", s->adicionado_em ? s->adicionado_em : "NaN");
    if (s->ano != 0) printf("%d ## ", s->ano);
    else printf("NaN ## ");
    printf("%s ## ", s->faixa_etaria ? s->faixa_etaria : "NaN");
    printf("%s ## ", s->tempo ? s->tempo : "NaN");
    exibirLista(s->tags);
    printf(" ##\n");
}

// Exibe todos os shows da fila circular
void mostrarFilaShow(FilaShow *fila) {
    int idx = fila->inicio;
    for (int i = 0; i < fila->total; i++) {
        exibirShow(fila->itens[idx]);
        idx = (idx + 1) % 5;
    }
}

// Função para limpar campo removendo aspas e espaços
char* campoLimpo(const char *str) {
    if (!str || str[0] == '\0' || strcmp(str, "NaN") == 0) return strdup("NaN");
    int ini = 0, fim = strlen(str) - 1;
    while (str[ini] == ' ' || str[ini] == '"') ini++;
    while (fim > ini && (str[fim] == ' ' || str[fim] == '"')) fim--;
    int tam = fim - ini + 1;
    char *res = malloc(tam + 1);
    for (int i = 0; i < tam; i++) res[i] = str[ini + i];
    res[tam] = '\0';
    return res;
}

// Lê arquivo CSV e monta coleção de shows
Colecao lerArquivo(const char *arquivo) {
    FILE *f = fopen(arquivo, "r");
    if (!f) { fprintf(stderr, "Falha ao abrir %s\n", arquivo); exit(1); }
    Colecao c;
    c.dados = malloc(1000 * sizeof(Show*));
    c.qtd = 0; c.max = 1000;
    char linha[4096];
    fgets(linha, sizeof(linha), f); // ignora cabeçalho
    while (fgets(linha, sizeof(linha), f)) {
        linha[strcspn(linha, "\n")] = '\0';
        Show *s = criarShow();
        char *campos[12];
        int campo = 0, i = 0, aspas = 0, ini = 0;
        for (i = 0; linha[i] && campo < 12; i++) {
            if (linha[i] == '"') aspas = !aspas;
            if ((linha[i] == ',' && !aspas) || linha[i+1] == '\0') {
                int fim = (linha[i+1] == '\0') ? i+1 : i;
                int tam = fim-ini;
                char *tmp = malloc(tam+1);
                strncpy(tmp, linha+ini, tam);
                tmp[tam] = '\0';
                campos[campo++] = campoLimpo(tmp);
                free(tmp);
                ini = i+1;
            }
        }
        while (campo < 12) campos[campo++] = strdup("NaN");
        free(s->id); s->id = campos[0];
        free(s->genero); s->genero = campos[1];
        free(s->nome); s->nome = campos[2];
        free(s->autor); s->autor = campos[3];
        int qtdAtores = 0;
        char **atores = dividirString(campos[4], ",", &qtdAtores);
        if (atores) {
            for (int j = 0; s->atores[j]; j++) free(s->atores[j]);
            free(s->atores);
            s->atores = atores;
        }
        free(s->origem); s->origem = campos[5];
        free(s->adicionado_em); s->adicionado_em = campos[6];
        s->ano = atoi(campos[7]);
        free(s->faixa_etaria); s->faixa_etaria = campos[8];
        free(s->tempo); s->tempo = campos[9];
        int qtdTags = 0;
        char **tags = dividirString(campos[10], ",", &qtdTags);
        if (tags) {
            for (int j = 0; s->tags[j]; j++) free(s->tags[j]);
            free(s->tags);
            s->tags = tags;
        }
        free(s->sinopse); s->sinopse = campos[11];
        if (c.qtd == c.max) {
            c.max *= 2;
            c.dados = realloc(c.dados, c.max * sizeof(Show*));
        }
        c.dados[c.qtd++] = s;
    }
    fclose(f);
    return c;
}

// Busca show pelo id
Show* buscarPorId(Colecao *c, const char *id) {
    for (int i = 0; i < c->qtd; i++)
        if (strcmp(c->dados[i]->id, id) == 0)
            return c->dados[i];
    return NULL;
}

// Função principal
int main() {
    const char *arquivo = "/tmp/disneyplus.csv";
    Colecao c = lerArquivo(arquivo);
    FilaShow fila;
    inicializarFila(&fila);

    char entrada[32];
    scanf("%s", entrada);
    while (strcasecmp(entrada, "FIM") != 0) {
        Show *s = buscarPorId(&c, entrada);
        if (s) inserirFilaShow(&fila, s);
        scanf("%s", entrada);
    }

    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        char cmd[4], arg[32];
        scanf("%s", cmd);
        if (strcmp(cmd, "I") == 0) {
            scanf("%s", arg);
            Show *s = buscarPorId(&c, arg);
            if (s) inserirFilaShow(&fila, s);
        } else if (strcmp(cmd, "R") == 0) {
            Show *rem = removerFilaShow(&fila);
            if (rem) {
                printf("(R) %s\n", rem->nome);
                liberarShow(rem);
            }
        }
    }

    mostrarFilaShow(&fila);

    // Libera memória da coleção
    for (int i = 0; i < c.qtd; i++) liberarShow(c.dados[i]);
    free(c.dados);

    // Libera memória da fila
    while (fila.total > 0) {
        Show *rem = removerFilaShow(&fila);
        liberarShow(rem);
    }
    return 0;
}