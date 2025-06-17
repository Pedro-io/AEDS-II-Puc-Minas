#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <locale.h>

typedef struct {
    char showId[20], type[20], title[200], director[200];
    char** cast;
    int numCast;
    char country[100];
    time_t dateAdded;
    int releaseYear;
    char rating[20], duration[50], listedIn[200], description[500];
} Show;

typedef struct {
    Show* array;
    int topo, capacidade;
} PilhaShow;

Show* allShows = NULL;
int numAllShows = 0, capacidadeAllShows = 10000;

void inicializarShow(Show* s) {
    s->cast = NULL; s->numCast = 0; s->dateAdded = 0; s->releaseYear = 0;
    strcpy(s->showId, "NaN"); strcpy(s->type, "NaN"); strcpy(s->title, "NaN");
    strcpy(s->director, "NaN"); strcpy(s->country, "NaN"); strcpy(s->rating, "NaN");
    strcpy(s->duration, "NaN"); strcpy(s->listedIn, "NaN"); strcpy(s->description, "NaN");
}

void liberarShow(Show* s) {
    if (s->cast) {
        for (int i = 0; i < s->numCast; i++) free(s->cast[i]);
        free(s->cast);
        s->cast = NULL;
    }
}

Show copiarShow(const Show* src) {
    Show dest;
    inicializarShow(&dest);
    strcpy(dest.showId, src->showId); strcpy(dest.type, src->type);
    strcpy(dest.title, src->title); strcpy(dest.director, src->director);
    strcpy(dest.country, src->country); dest.dateAdded = src->dateAdded;
    dest.releaseYear = src->releaseYear; strcpy(dest.rating, src->rating);
    strcpy(dest.duration, src->duration); strcpy(dest.listedIn, src->listedIn);
    strcpy(dest.description, src->description);
    dest.numCast = src->numCast;
    if (src->numCast > 0) {
        dest.cast = malloc(src->numCast * sizeof(char*));
        for (int i = 0; i < src->numCast; i++) dest.cast[i] = strdup(src->cast[i]);
    } else dest.cast = NULL;
    return dest;
}

void copiarStringSegura(char* dest, char* src) {
    if (!src || strlen(src) == 0) strcpy(dest, "NaN");
    else {
        char* temp = strdup(src);
        int len = strlen(temp);
        if (temp[0] == '\"' && temp[len - 1] == '\"') {
            temp[len - 1] = '\0';
            memmove(temp, temp + 1, len - 1);
        }
        strcpy(dest, temp);
        free(temp);
    }
}

void parseCSV(char* linha, char** campos, int* numCampos) {
    bool aspas = false;
    int campo = 0, idx = 0;
    char temp[1000];
    linha[strcspn(linha, "\r\n")] = 0;
    for (int i = 0; linha[i] != '\0'; i++) {
        char c = linha[i];
        if (c == '\"') aspas = !aspas;
        else if (c == ',' && !aspas) {
            temp[idx] = '\0';
            campos[campo++] = strdup(temp);
            idx = 0;
            if (campo >= 12) i = strlen(linha); // força saída do laço
        } else {
            temp[idx++] = c;
            if (idx >= (int)sizeof(temp) - 1) i = strlen(linha); // força saída do laço
        }
    }
    temp[idx] = '\0';
    campos[campo++] = strdup(temp);
    *numCampos = campo;
}

time_t parseData(const char* data) {
    struct tm tm_obj = {0};
    char mes[20];
    int dia, ano;
    if (sscanf(data, "%s %d, %d", mes, &dia, &ano) != 3) return 0;
    const char* meses[] = {"January","February","March","April","May","June","July","August","September","October","November","December"};
    int i = 0, encontrado = 0;
    while (i < 12 && !encontrado) {
        if (strcmp(mes, meses[i]) == 0) encontrado = 1;
        else i++;
    }
    if (!encontrado) return 0;
    tm_obj.tm_mon = i; tm_obj.tm_mday = dia; tm_obj.tm_year = ano - 1900;
    return mktime(&tm_obj);
}

void lerShow(Show* s, char* linha) {
    inicializarShow(s);
    char* campos[12];
    int numCampos = 0;
    parseCSV(linha, campos, &numCampos);
    for (int i = numCampos; i < 12; i++) campos[i] = strdup("");
    copiarStringSegura(s->showId, campos[0]);
    copiarStringSegura(s->type, campos[1]);
    copiarStringSegura(s->title, campos[2]);
    copiarStringSegura(s->director, campos[3]);
    char* elenco = campos[4];
    if (!elenco || strlen(elenco) == 0) { s->cast = NULL; s->numCast = 0; }
    else {
        char* temp = strdup(elenco);
        int len = strlen(temp);
        if (temp[0] == '\"' && temp[len - 1] == '\"') {
            temp[len - 1] = '\0';
            memmove(temp, temp + 1, len - 1);
        }
        s->numCast = 0;
        char* token = strtok(temp, ",");
        while (token) {
            while (*token == ' ') token++;
            len = strlen(token);
            while (len > 0 && token[len - 1] == ' ') len--;
            token[len] = '\0';
            s->cast = realloc(s->cast, (s->numCast + 1) * sizeof(char*));
            s->cast[s->numCast++] = strdup(token);
            token = strtok(NULL, ",");
        }
        free(temp);
    }
    copiarStringSegura(s->country, campos[5]);
    char* data = campos[6];
    if (!data || strlen(data) == 0) s->dateAdded = 0;
    else {
        char* temp = strdup(data);
        int len = strlen(temp);
        if (temp[0] == '\"' && temp[len - 1] == '\"') {
            temp[len - 1] = '\0';
            memmove(temp, temp + 1, len - 1);
        }
        s->dateAdded = parseData(temp);
        free(temp);
    }
    char* ano = campos[7];
    if (!ano || strlen(ano) == 0) s->releaseYear = 0;
    else {
        char* temp = strdup(ano);
        int len = strlen(temp);
        if (temp[0] == '\"' && temp[len - 1] == '\"') {
            temp[len - 1] = '\0';
            memmove(temp, temp + 1, len - 1);
        }
        s->releaseYear = atoi(temp);
        free(temp);
    }
    copiarStringSegura(s->rating, campos[8]);
    copiarStringSegura(s->duration, campos[9]);
    copiarStringSegura(s->listedIn, campos[10]);
    copiarStringSegura(s->description, campos[11]);
    for (int i = 0; i < 12; i++) free(campos[i]);
}

int compararStrings(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

void mostrarShow(const Show* s) {
    printf("=> %s ## %s ## %s ## %s ## [", s->showId, s->title, s->type, s->director);
    if (s->numCast > 0) {
        char** castOrdenado = malloc(s->numCast * sizeof(char*));
        for (int i = 0; i < s->numCast; i++) castOrdenado[i] = s->cast[i];
        qsort(castOrdenado, s->numCast, sizeof(char*), compararStrings);
        for (int i = 0; i < s->numCast; i++)
            printf("%s%s", castOrdenado[i], (i == s->numCast - 1) ? "" : ", ");
        free(castOrdenado);
    } else printf("NaN");
    printf("] ## %s ## ", s->country);
    if (s->dateAdded != 0) {
        char buffer[80];
        struct tm* tm_info = localtime(&s->dateAdded);
        strftime(buffer, sizeof(buffer), "%B %d, %Y", tm_info);
        printf("%s", buffer);
    } else printf("NaN");
    printf(" ## %d ## %s ## %s ## [%s] ##\n", s->releaseYear, s->rating, s->duration, s->listedIn);
}

void inicializarPilha(PilhaShow* pilha, int capacidade) {
    pilha->array = malloc(capacidade * sizeof(Show));
    pilha->topo = -1;
    pilha->capacidade = capacidade;
}

void liberarPilha(PilhaShow* pilha) {
    for (int i = pilha->topo; i >= 0; i--) liberarShow(&pilha->array[i]);
    free(pilha->array);
    pilha->array = NULL; pilha->topo = -1; pilha->capacidade = 0;
}

void empilhar(PilhaShow* pilha, Show show) {
    if (pilha->topo == pilha->capacidade - 1) {
        pilha->capacidade *= 2;
        pilha->array = realloc(pilha->array, pilha->capacidade * sizeof(Show));
    }
    pilha->topo++;
    pilha->array[pilha->topo] = copiarShow(&show);
}

Show desempilhar(PilhaShow* pilha) {
    Show vazio; inicializarShow(&vazio);
    if (pilha->topo == -1) return vazio;
    Show resp = pilha->array[pilha->topo];
    pilha->topo--;
    return resp;
}

void mostrarPilha(const PilhaShow* pilha) {
    for (int i = pilha->topo; i >= 0; i--) mostrarShow(&pilha->array[i]);
}

void lerCSV(const char* caminho) {
    FILE* f = fopen(caminho, "r");
    if (!f) { perror("Erro ao abrir arquivo"); exit(1); }
    char linha[1024];
    fgets(linha, sizeof(linha), f);
    allShows = malloc(capacidadeAllShows * sizeof(Show));
    while (fgets(linha, sizeof(linha), f)) {
        if (numAllShows >= capacidadeAllShows) {
            capacidadeAllShows *= 2;
            allShows = realloc(allShows, capacidadeAllShows * sizeof(Show));
        }
        lerShow(&allShows[numAllShows], linha);
        numAllShows++;
    }
    fclose(f);
}

Show* buscarShowPorId(const char* id) {
    int i = 0;
    while (i < numAllShows) {
        if (strcmp(allShows[i].showId, id) == 0) return &allShows[i];
        i++;
    }
    return NULL;
}

char* lerLinhaArquivo(const char* id) {
    FILE* f = fopen("/tmp/disneyplus.csv", "r");
    if (!f) return NULL;
    char linha[1024];
    fgets(linha, sizeof(linha), f);
    char* achou = NULL;
    while (fgets(linha, sizeof(linha), f)) {
        char tempId[20];
        sscanf(linha, "%19[^,]", tempId);
        if (strcmp(tempId, id) == 0 && !achou) achou = strdup(linha);
    }
    fclose(f);
    return achou;
}

int main() {
    setlocale(LC_ALL, "en_US.UTF-8");
    lerCSV("/tmp/disneyplus.csv");
    PilhaShow pilha;
    inicializarPilha(&pilha, 100);
    char id[20];
    scanf("%19s", id);
    while (strcmp(id, "FIM") != 0) {
        Show* s = buscarShowPorId(id);
        if (s) empilhar(&pilha, *s);
        scanf("%19s", id);
    }
    int n;
    scanf("%d", &n); getchar();
    int i = 0;
    while (i < n) {
        char comando[256], cmd[2], arg[20];
        if (fgets(comando, sizeof(comando), stdin)) {
            comando[strcspn(comando, "\n")] = 0;
            sscanf(comando, "%s", cmd);
            if (strcmp(cmd, "I") == 0) {
                sscanf(comando, "%*s %19s", arg);
                char* linha = lerLinhaArquivo(arg);
                if (linha) {
                    Show novo;
                    lerShow(&novo, linha);
                    empilhar(&pilha, novo);
                    liberarShow(&novo);
                    free(linha);
                }
            } else if (strcmp(cmd, "R") == 0) {
                Show removido = desempilhar(&pilha);
                if (strcmp(removido.showId, "NaN") != 0) {
                    printf("(R) %s\n", removido.title);
                    liberarShow(&removido);
                }
            }
        }
        i++;
    }
    mostrarPilha(&pilha);
    liberarPilha(&pilha);
    if (allShows) {
        int i = 0;
        while (i < numAllShows) { liberarShow(&allShows[i]); i++; }
        free(allShows); allShows = NULL;
    }
    return 0;
}