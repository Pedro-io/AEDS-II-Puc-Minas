#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>

typedef struct {
    char showId[20], type[20], title[200], director[200];
    char **cast;
    int numCast;
    char country[100];
    time_t dateAdded;
    int releaseYear;
    char rating[20], duration[50], listedIn[200], description[500];
} Show;

typedef struct Node {
    Show data;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    int n;
} ListaShow;

Show *allShows = NULL;
int numAllShows = 0, capacityAllShows = 10000;

void inicializarShow(Show *s) {
    s->cast = NULL;
    s->numCast = 0;
    s->dateAdded = 0;
    s->releaseYear = 0;
    strcpy(s->showId, "NaN");
    strcpy(s->type, "NaN");
    strcpy(s->title, "NaN");
    strcpy(s->director, "NaN");
    strcpy(s->country, "NaN");
    strcpy(s->rating, "NaN");
    strcpy(s->duration, "NaN");
    strcpy(s->listedIn, "NaN");
    strcpy(s->description, "NaN");
}

void liberarShow(Show *s) {
    if (s->cast) {
        for (int i = 0; i < s->numCast; i++)
            if (s->cast[i]) free(s->cast[i]);
        free(s->cast);
        s->cast = NULL;
    }
}

Show copiarShow(const Show *src) {
    Show dest;
    inicializarShow(&dest);
    strcpy(dest.showId, src->showId);
    strcpy(dest.type, src->type);
    strcpy(dest.title, src->title);
    strcpy(dest.director, src->director);
    strcpy(dest.country, src->country);
    dest.dateAdded = src->dateAdded;
    dest.releaseYear = src->releaseYear;
    strcpy(dest.rating, src->rating);
    strcpy(dest.duration, src->duration);
    strcpy(dest.listedIn, src->listedIn);
    strcpy(dest.description, src->description);
    dest.numCast = src->numCast;
    if (src->numCast > 0) {
        dest.cast = malloc(src->numCast * sizeof(char*));
        for (int i = 0; i < src->numCast; i++)
            dest.cast[i] = strdup(src->cast[i]);
    } else dest.cast = NULL;
    return dest;
}

void inicializarLista(ListaShow *lista) {
    lista->head = NULL;
    lista->n = 0;
}

void liberarLista(ListaShow *lista) {
    Node *atual = lista->head, *prox;
    while (atual) {
        prox = atual->next;
        liberarShow(&atual->data);
        free(atual);
        atual = prox;
    }
    lista->head = NULL;
    lista->n = 0;
}

void inserirInicio(ListaShow *lista, Show show) {
    Node *novo = malloc(sizeof(Node));
    novo->data = copiarShow(&show);
    novo->next = lista->head;
    lista->head = novo;
    lista->n++;
}

void inserirFim(ListaShow *lista, Show show) {
    Node *novo = malloc(sizeof(Node));
    novo->data = copiarShow(&show);
    novo->next = NULL;
    if (!lista->head) lista->head = novo;
    else {
        Node *atual = lista->head;
        while (atual->next) atual = atual->next;
        atual->next = novo;
    }
    lista->n++;
}

void inserirPos(ListaShow *lista, Show show, int pos) {
    if (pos < 0 || pos > lista->n) return;
    if (pos == 0) inserirInicio(lista, show);
    else {
        Node *novo = malloc(sizeof(Node));
        novo->data = copiarShow(&show);
        Node *atual = lista->head;
        for (int i = 0; i < pos - 1; i++) atual = atual->next;
        novo->next = atual->next;
        atual->next = novo;
        lista->n++;
    }
}

Show removerInicio(ListaShow *lista) {
    Show removido;
    inicializarShow(&removido);
    if (!lista->head) return removido;
    Node *tmp = lista->head;
    removido = tmp->data;
    lista->head = tmp->next;
    free(tmp);
    lista->n--;
    return removido;
}

Show removerFim(ListaShow *lista) {
    Show removido;
    inicializarShow(&removido);
    if (!lista->head) return removido;
    if (!lista->head->next) return removerInicio(lista);
    Node *atual = lista->head, *ant = NULL;
    while (atual->next) {
        ant = atual;
        atual = atual->next;
    }
    removido = atual->data;
    ant->next = NULL;
    free(atual);
    lista->n--;
    return removido;
}

Show removerPos(ListaShow *lista, int pos) {
    Show removido;
    inicializarShow(&removido);
    if (!lista->head || pos < 0 || pos >= lista->n) return removido;
    if (pos == 0) return removerInicio(lista);
    Node *atual = lista->head, *ant = NULL;
    for (int i = 0; i < pos; i++) {
        ant = atual;
        atual = atual->next;
    }
    removido = atual->data;
    ant->next = atual->next;
    free(atual);
    lista->n--;
    return removido;
}

void mostrarShow(const Show *s) {
    printf("=> %s ## %s ## %s ## %s ## [", s->showId, s->title, s->type, s->director);
    if (s->numCast > 0) {
        // Ordenação manual do elenco (bubble sort)
        char **elenco = malloc(s->numCast * sizeof(char*));
        for (int i = 0; i < s->numCast; i++) elenco[i] = s->cast[i];
        for (int i = 0; i < s->numCast - 1; i++)
            for (int j = 0; j < s->numCast - i - 1; j++)
                if (strcmp(elenco[j], elenco[j+1]) > 0) {
                    char *tmp = elenco[j];
                    elenco[j] = elenco[j+1];
                    elenco[j+1] = tmp;
                }
        for (int i = 0; i < s->numCast; i++)
            printf("%s%s", elenco[i], (i == s->numCast - 1) ? "" : ", ");
        free(elenco);
    } else printf("NaN");
    printf("] ## %s ## ", s->country);
    if (s->dateAdded) {
        char buf[80];
        struct tm *tm_info = localtime(&s->dateAdded);
        strftime(buf, sizeof(buf), "%B %d, %Y", tm_info);
        printf("%s", buf);
    } else printf("NaN");
    printf(" ## %d ## %s ## %s ## [%s] ##\n", s->releaseYear, s->rating, s->duration, s->listedIn);
}

void mostrarLista(const ListaShow *lista) {
    Node *atual = lista->head;
    while (atual) {
        mostrarShow(&atual->data);
        atual = atual->next;
    }
}

void copiarCampo(char *dest, const char *src) {
    if (!src || strlen(src) == 0) strcpy(dest, "NaN");
    else {
        char *tmp = strdup(src);
        int len = strlen(tmp);
        if (tmp[0] == '"' && tmp[len-1] == '"') {
            tmp[len-1] = '\0';
            memmove(tmp, tmp+1, len-1);
        }
        strcpy(dest, tmp);
        free(tmp);
    }
}

void parseCSV(char *linha, char **campos, int *numCampos) {
    bool aspas = false;
    int idxCampo = 0, idxChar = 0;
    char temp[1000];
    linha[strcspn(linha, "\r\n")] = 0;
    for (int i = 0; linha[i] != '\0'; i++) {
        char c = linha[i];
        if (c == '"') aspas = !aspas;
        else if (c == ',' && !aspas) {
            temp[idxChar] = '\0';
            campos[idxCampo++] = strdup(temp);
            idxChar = 0;
            if (idxCampo >= 12) i = strlen(linha); // força saída do laço
        } else {
            temp[idxChar++] = c;
            if (idxChar >= (int)sizeof(temp) - 1) i = strlen(linha); // força saída do laço
        }
    }
    temp[idxChar] = '\0';
    campos[idxCampo++] = strdup(temp);
    *numCampos = idxCampo;
}

time_t parseData(const char *dataStr) {
    struct tm tm_obj = {0};
    char mes[20];
    int dia, ano;
    if (sscanf(dataStr, "%s %d, %d", mes, &dia, &ano) != 3) return 0;
    if (!strcmp(mes, "January")) tm_obj.tm_mon = 0;
    else if (!strcmp(mes, "February")) tm_obj.tm_mon = 1;
    else if (!strcmp(mes, "March")) tm_obj.tm_mon = 2;
    else if (!strcmp(mes, "April")) tm_obj.tm_mon = 3;
    else if (!strcmp(mes, "May")) tm_obj.tm_mon = 4;
    else if (!strcmp(mes, "June")) tm_obj.tm_mon = 5;
    else if (!strcmp(mes, "July")) tm_obj.tm_mon = 6;
    else if (!strcmp(mes, "August")) tm_obj.tm_mon = 7;
    else if (!strcmp(mes, "September")) tm_obj.tm_mon = 8;
    else if (!strcmp(mes, "October")) tm_obj.tm_mon = 9;
    else if (!strcmp(mes, "November")) tm_obj.tm_mon = 10;
    else if (!strcmp(mes, "December")) tm_obj.tm_mon = 11;
    else return 0;
    tm_obj.tm_mday = dia;
    tm_obj.tm_year = ano - 1900;
    return mktime(&tm_obj);
}

void lerShow(Show *s, char *linha) {
    inicializarShow(s);
    char *campos[12];
    int numCampos = 0;
    parseCSV(linha, campos, &numCampos);
    for (int i = numCampos; i < 12; i++) campos[i] = strdup("");
    copiarCampo(s->showId, campos[0]);
    copiarCampo(s->type, campos[1]);
    copiarCampo(s->title, campos[2]);
    copiarCampo(s->director, campos[3]);
    char *elenco_raw = campos[4];
    if (!elenco_raw || strlen(elenco_raw) == 0) {
        s->cast = NULL;
        s->numCast = 0;
    } else {
        char *tmp = strdup(elenco_raw);
        int len = strlen(tmp);
        if (tmp[0] == '"' && tmp[len-1] == '"') {
            tmp[len-1] = '\0';
            memmove(tmp, tmp+1, len-1);
        }
        s->numCast = 0;
        char *token = strtok(tmp, ",");
        while (token) {
            while (*token == ' ') token++;
            int tlen = strlen(token);
            while (tlen > 0 && token[tlen-1] == ' ') token[--tlen] = '\0';
            s->cast = realloc(s->cast, (s->numCast+1) * sizeof(char*));
            s->cast[s->numCast++] = strdup(token);
            token = strtok(NULL, ",");
        }
        free(tmp);
    }
    copiarCampo(s->country, campos[5]);
    char *dataStr = campos[6];
    if (!dataStr || strlen(dataStr) == 0) s->dateAdded = 0;
    else {
        char *tmp = strdup(dataStr);
        int len = strlen(tmp);
        if (tmp[0] == '"' && tmp[len-1] == '"') {
            tmp[len-1] = '\0';
            memmove(tmp, tmp+1, len-1);
        }
        s->dateAdded = parseData(tmp);
        free(tmp);
    }
    char *anoStr = campos[7];
    if (!anoStr || strlen(anoStr) == 0) s->releaseYear = 0;
    else {
        char *tmp = strdup(anoStr);
        int len = strlen(tmp);
        if (tmp[0] == '"' && tmp[len-1] == '"') {
            tmp[len-1] = '\0';
            memmove(tmp, tmp+1, len-1);
        }
        s->releaseYear = atoi(tmp);
        free(tmp);
    }
    copiarCampo(s->rating, campos[8]);
    copiarCampo(s->duration, campos[9]);
    copiarCampo(s->listedIn, campos[10]);
    copiarCampo(s->description, campos[11]);
    for (int i = 0; i < 12; i++) free(campos[i]);
}

void lerCSV(const char *caminho) {
    FILE *f = fopen(caminho, "r");
    if (!f) exit(1);
    char linha[1024];
    fgets(linha, sizeof(linha), f);
    allShows = malloc(capacityAllShows * sizeof(Show));
    while (fgets(linha, sizeof(linha), f)) {
        if (numAllShows >= capacityAllShows) {
            capacityAllShows *= 2;
            allShows = realloc(allShows, capacityAllShows * sizeof(Show));
        }
        lerShow(&allShows[numAllShows], linha);
        numAllShows++;
    }
    fclose(f);
}

Show* buscarShowPorId(const char *showId) {
    for (int i = 0; i < numAllShows; i++)
        if (!strcmp(allShows[i].showId, showId)) return &allShows[i];
    return NULL;
}

char* lerLinhaPorArquivo(const char *showId) {
    FILE *f = fopen("/tmp/disneyplus.csv", "r");
    if (!f) return NULL;
    char linha[1024];
    fgets(linha, sizeof(linha), f);
    char *encontrada = NULL;
    while (fgets(linha, sizeof(linha), f)) {
        char tempId[20];
        sscanf(linha, "%19[^,]", tempId);
        if (!strcmp(tempId, showId)) {
            encontrada = strdup(linha);
            fclose(f);
            return encontrada;
        }
    }
    fclose(f);
    return NULL;
}

int main() {
    setlocale(LC_ALL, "en_US.UTF-8");
    lerCSV("/tmp/disneyplus.csv");
    ListaShow lista;
    inicializarLista(&lista);
    char id[20];
    while (scanf("%19s", id) == 1 && strcmp(id, "FIM") != 0) {
        Show *s = buscarShowPorId(id);
        if (s) inserirFim(&lista, *s);
    }
    int n;
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++) {
        char linha[256], cmd[5], arg1[20], arg2[20];
        if (!fgets(linha, sizeof(linha), stdin)) continue;
        linha[strcspn(linha, "\n")] = 0;
        sscanf(linha, "%s", cmd);
        if (!strcmp(cmd, "II")) {
            sscanf(linha, "%*s %19s", arg1);
            char *linhaArq = lerLinhaPorArquivo(arg1);
            if (linhaArq) {
                Show novo;
                lerShow(&novo, linhaArq);
                inserirInicio(&lista, novo);
                liberarShow(&novo);
                free(linhaArq);
            }
        } else if (!strcmp(cmd, "IF")) {
            sscanf(linha, "%*s %19s", arg1);
            char *linhaArq = lerLinhaPorArquivo(arg1);
            if (linhaArq) {
                Show novo;
                lerShow(&novo, linhaArq);
                inserirFim(&lista, novo);
                liberarShow(&novo);
                free(linhaArq);
            }
        } else if (!strcmp(cmd, "I*")) {
            int pos;
            sscanf(linha, "%*s %d %19s", &pos, arg2);
            char *linhaArq = lerLinhaPorArquivo(arg2);
            if (linhaArq) {
                Show novo;
                lerShow(&novo, linhaArq);
                inserirPos(&lista, novo, pos);
                liberarShow(&novo);
                free(linhaArq);
            }
        } else if (!strcmp(cmd, "RI")) {
            Show removido = removerInicio(&lista);
            if (strcmp(removido.showId, "NaN")) {
                printf("(R) %s\n", removido.title);
                liberarShow(&removido);
            }
        } else if (!strcmp(cmd, "RF")) {
            Show removido = removerFim(&lista);
            if (strcmp(removido.showId, "NaN")) {
                printf("(R) %s\n", removido.title);
                liberarShow(&removido);
            }
        } else if (!strcmp(cmd, "R*")) {
            int pos;
            sscanf(linha, "%*s %d", &pos);
            Show removido = removerPos(&lista, pos);
            if (strcmp(removido.showId, "NaN")) {
                printf("(R) %s\n", removido.title);
                liberarShow(&removido);
            }
        }
    }
    mostrarLista(&lista);
    liberarLista(&lista);
    if (allShows) {
        for (int i = 0; i < numAllShows; i++) liberarShow(&allShows[i]);
        free(allShows);
        allShows = NULL;
    }
    return 0;
}