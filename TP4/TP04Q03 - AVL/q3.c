#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h> 

#define MAXSHOWS 10000
#define MAXIDS 1000
#define MAXTAM 100
#define MAXSTR 100
#define MAX_PILHA 100
#define LINHA_TAM 300

// Metódo para passar o valor de uma string para outra.

void copiarString(char *destino, const char *origem)
{
    int i = 0;
    while (origem[i] != '\0')
    {
        destino[i] = origem[i];
        i++;
    }
    destino[i] = '\0';
}

typedef struct
{
    int dia;
    char mes[20];
    int ano;
} Data;

// Estrutura que representa uma lista de Strings.

typedef struct
{
    char array[MAXTAM][MAXSTR];
    int n;
} ListaString;

// Metódo para inserção de uma String no fim da lista.

void inserirFimLS(ListaString *lista, const char *c)
{
    if (lista->n >= MAXTAM)
    {
        printf("Erro: Lista cheia!\n");
        exit(1);
    }
    copiarString(lista->array[lista->n], c);
    lista->n++;
}

// Metódo que compara duas strings em ordem lexicográfica

int comparar(const char *str1, const char *str2)
{
    int i = 0;
    while (str1[i] == str2[i] && str1[i] != '\0' && str2[i] != '\0')
    {
        i++;
    }
    return (str1[i] - str2[i]);
}

// Metódo que ordena os elementos de uma ListaString em ordem alfabética.

void ordenar(ListaString *lista)
{
    for (int i = 0; i < lista->n - 1; i++)
    {
        for (int j = i + 1; j < lista->n; j++)
        {
            int k = 0;
            // Compara os caracteres das duas strings
            while (lista->array[i][k] != '\0' && lista->array[j][k] != '\0' && lista->array[i][k] == lista->array[j][k])
            {
                k++;
            }

            if (lista->array[i][k] > lista->array[j][k])
            {
                char temp[MAXSTR];
                copiarString(temp, lista->array[i]);
                copiarString(lista->array[i], lista->array[j]);
                copiarString(lista->array[j], temp);
            }
        }
    }
}

// Transforma uma String em uma Lista, separando seus valores.
void trasformarLista(ListaString *lista, const char *c)
{
    int i = 0;
    lista->n = 0;

    while (c[i] != '\0')
    {
        char nome[MAXSTR];
        int j = 0;

        while (c[i] == ' ' || c[i] == '"')
        {
            i++;
        }

        while (c[i] != '\0' && c[i] != ',')
        {
            if (c[i] != '"')
            {
                nome[j++] = c[i];
            }
            i++;
        }

        nome[j] = '\0';
        inserirFimLS(lista, nome);

        if (c[i] == ',')
        {
            i++;
        }
    }

    if (lista->n == 0)
    {
        inserirFimLS(lista, "NaN");
    }
}

// Metódo que mostra os elementos da Lista.

void mostrarLS(const ListaString *lista)
{
    for (int i = 0; i < lista->n; i++)
    {
        printf("%s", lista->array[i]);
        if (i < lista->n - 1)
        {
            printf(", ");
        }
    }
}

// Metódo que pega o tamanho da String.

int tamVetor(char palavra[])
{
    int tam = 0;
    for (int j = 0; palavra[j] != '\0'; j++)
    {
        tam += 1;
    }
    return tam;
}

// Estrutura que representa a classe Shows.

typedef struct
{
    char show_id[1000];
    char type[1000];
    char title[1000];
    char director[1000];
    char cast[1000];
    char country[1000];
    char data_added[1000];
    char release_year[1000];
    char rating[1000];
    char duration[1000];
    char listed_in[1000];
} Shows;

Shows *newShow()
{
    Shows *s = (Shows *)malloc(sizeof(Shows));
    return s;
}

void delShow(Shows *s)
{
    free(s);
}

// Metódo para ler uma linha do CSV e separar seus atributos.

Shows *ler(Shows *s, char *c)
{

    char campos[11][1000];
    int campo = 0, pos = 0;
    int i = 0;
    int aspas = 0;

    while (c[i] != '\0' && campo < 11)
    {
        if (c[i] == '"')
        {
            aspas = !aspas;
            i++;
        }
        else if (c[i] == ',' && aspas == 0)
        {
            if (pos < 1000)
            {
                campos[campo][pos] = '\0';
            }
            campo++;
            pos = 0;
            i++;
        }
        else
        {
            if (pos < 999)
            {
                campos[campo][pos++] = c[i++];
            }
            else
            {
                i++;
            }
        }
    }

    if (pos < 1000)
    {
        campos[campo][pos] = '\0';
    }

    for (int j = campo + 1; j < 11; j++)
    {
        copiarString(campos[j], "NaN");
    }

    for (int j = 0; j < 11; j++)
    {
        if (campos[j][0] == '\0')
        {
            copiarString(campos[j], "NaN");
        }
    }

    // Atribui os campos lidos aos respectivos atributos da estrutura Shows.
    copiarString(s->show_id, campos[0]);
    copiarString(s->title, campos[2]);
    copiarString(s->type, campos[1]);
    copiarString(s->director, campos[3]);
    copiarString(s->cast, campos[4]);
    copiarString(s->country, campos[5]);
    copiarString(s->data_added, campos[6]);
    copiarString(s->release_year, campos[7]);
    copiarString(s->rating, campos[8]);
    copiarString(s->duration, campos[9]);
    copiarString(s->listed_in, campos[10]);

    return s;
}

// Metódo para imprimir os atributos da linha no formato pedido.

void imprimir(const Shows *s)
{
    ListaString cast, listed_in;
    cast.n = 0;
    listed_in.n = 0;

    trasformarLista(&cast, s->cast);
    ordenar(&cast);
    trasformarLista(&listed_in, s->listed_in);
    ordenar(&listed_in);

    printf("=> %s ## %s ## %s ## %s ## [", s->show_id, s->title, s->type, s->director);
    mostrarLS(&cast);
    printf("] ## %s ## %s ## %s ## %s ## %s ## [", s->country, s->data_added, s->release_year, s->rating, s->duration);
    mostrarLS(&listed_in);
    printf("] ##\n");
}

// Metódo para verificar a condição de parada manualmente.

int condicaoParada(char palavra[])
{
    int resp = 0;
    if (tamVetor(palavra) == 3 && palavra[0] == 'F' && palavra[1] == 'I' && palavra[2] == 'M')
    {
        resp = 1;
    }
    return resp;
}

// Metódo para buscar o registro referente a um 'id' no csv.
Shows *procurarID(const char *caminho, const char *idBuscado)
{
    FILE *fp = fopen(caminho, "r");
    char linha[1000];
    Shows *show = NULL;

    while (fgets(linha, sizeof(linha), fp))
    {
        Shows temp;
        ler(&temp, linha);
        if (strcmp(temp.show_id, idBuscado) == 0)
        {
            show = malloc(sizeof(Shows));
            *show = temp;
        }
    }

    fclose(fp);
    return show;
}

typedef struct No
{
    Shows show;
    int nivel;
    struct No *esq, *dir;
} No;

No *novoNo(Shows show)
{
    No *novo = (No *)malloc(sizeof(No));
    novo->show = show;
    novo->nivel = 1;
    novo->esq = NULL;
    novo->dir = NULL;
    return novo;
}

int getNivel(No *no) {
		return (no == NULL) ? 0 : no->nivel;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

void setNivel(No *no) {
    no->nivel = 1 + max(getNivel(no->esq), getNivel(no->dir));
}

No *raiz;

void start()
{
    raiz = NULL;
}

No *maiorEsq(No *i, No *j)
{
    if (i->dir == NULL){
        i->show = j->show;
        j = j->esq;
    }else{
        j->dir = maiorEsq(i, j->dir);
    }
    return j;
}

No *rotacionarDir(No *no) {
    No *noEsq = no->esq;
    No *noEsqDir = noEsq->dir;

    noEsq->dir = no;
    no->esq = noEsqDir;

    setNivel(no);
    setNivel(noEsq);

    return noEsq;
}

No *rotacionarEsq(No *no) {
    No *noDir = no->dir;
    No *noDirEsq = noDir->esq;

    noDir->esq = no;
    no->dir = noDirEsq;

    setNivel(no);
    setNivel(noDir);

    return noDir;
}

No *balancear(No *no) {
    if (no != NULL) {
        int fator = getNivel(no->dir) - getNivel(no->esq);

        if (abs(fator) <= 1) {
            setNivel(no);
        } else if (fator == 2) {
            int fatorFilhoDir = getNivel(no->dir->dir) - getNivel(no->dir->esq);
            if (fatorFilhoDir < 0) {
                no->dir = rotacionarDir(no->dir);
            }
            no = rotacionarEsq(no);
        } else if (fator == -2) {
            int fatorFilhoEsq = getNivel(no->esq->dir) - getNivel(no->esq->esq);
            if (fatorFilhoEsq > 0) {
                no->esq = rotacionarEsq(no->esq);
            }
            no = rotacionarDir(no);
        } else {
            fprintf(stderr, "Fator de desbalanceamento inválido!\n");
            exit(1);
        }
    }
    return no;
}

No *inserirRec(Shows s, No *i)
{
    if (i == NULL){
        i = novoNo(s);
    }else if (strcmp(s.title, i->show.title) < 0){
        i->esq = inserirRec(s, i->esq);
    }else if (strcmp(s.title, i->show.title) > 0){
        i->dir = inserirRec(s, i->dir);
    }else{
        fprintf(stderr, "Erro ao inserir!\n");
        exit(1);

    }
    return balancear(i);
}

void inserir(Shows s)
{
    raiz = inserirRec(s, raiz);
}

int comparacoes = 0;

// Altere a função de busca para incrementar comparações:
int buscarTituloRec(char titulo[], No *nodo) {
    comparacoes++;
    if (nodo == NULL) {
        return 0;
    } else if (strcmp(titulo, nodo->show.title) == 0) {
        return 1;
    } else if (strcmp(titulo, nodo->show.title) < 0) {
        printf("esq ");
        return buscarTituloRec(titulo, nodo->esq);
    } else {
        printf("dir ");
        return buscarTituloRec(titulo, nodo->dir);
    }
}

int buscarTitulo(char titulo[]) {
    printf("raiz ");
    int achou = buscarTituloRec(titulo, raiz);
    printf(achou ? "SIM\n" : "NAO\n");
    return achou;
}

int main()
{
    struct timeval inicio, fim;
    gettimeofday(&inicio, NULL); // Marca o início

    char caminhoCSV[] = "/tmp/disneyplus.csv";
    char bufferId[100];
    scanf(" %[^\n]", bufferId);

    // Leitura dos IDs até encontrar "FIM", inserindo os registros na árvore AVL
    while (strcmp(bufferId, "FIM") != 0)
    {
        Shows *registro = procurarID(caminhoCSV, bufferId);
        inserir(*registro);
        free(registro);

        scanf(" %[^\n]", bufferId);
    }

    char consulta[1000];
    scanf(" %[^\n]", consulta);

    // Processa as consultas de busca até "FIM"
    while (strcmp(consulta, "FIM") != 0) {
        buscarTitulo(consulta);
        scanf(" %[^\n]", consulta);
    }

    gettimeofday(&fim, NULL); // Marca o fim

    // Calcula o tempo em milissegundos
    double tempo = (fim.tv_sec - inicio.tv_sec) * 1000.0;
    tempo += (fim.tv_usec - inicio.tv_usec) / 1000.0;

    // Escreve no arquivo de log
    FILE *log = fopen("793406_avl.txt", "w");
    if (log != NULL) {
        fprintf(log, "793406\t%.3f\t%d\n", tempo, comparacoes);
        fclose(log);
    }

    return 0;
}
