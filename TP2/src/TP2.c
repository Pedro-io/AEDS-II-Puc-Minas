#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // Para usar bool, true, false
#include <ctype.h> // Para isspace

#define MAX_LINE_SIZE 4096 // Tamanho máximo de uma linha do CSV
#define MAX_FIELD_SIZE 1024 // Tamanho máximo de um campo do CSV
#define MAX_FIELDS 20       // Número máximo de campos esperados
#define MAX_ARRAY_SIZE 10000 // Tamanho do array de Shows
#define MAX_CAST_LISTED_ITEMS 50 // Estimativa para itens em cast/listed_in


typedef struct {
    char* show_id;
    char* type;
    char* title;
    char* director;
    char* cast;
    char* country;
    char* date_added;
    int release_year;
    char* rating;
    char* duration;
    char* listed_in;
} Show;

// --- Funções Auxiliares ---

// Função strdup (pode não ser padrão em C, implementando se necessário)
// Aloca memória e copia a string
char* strdup_custom(const char* s) {
    if (s == NULL) return NULL;
    size_t len = strlen(s) + 1;
    char* new_str = (char*)malloc(len);
    if (new_str == NULL) {
        perror("Erro ao alocar memória em strdup_custom");
        exit(EXIT_FAILURE);
    }
    memcpy(new_str, s, len);
    return new_str;
}

// Função para liberar a memória alocada para uma string se não for NULL
void free_string(char** str_ptr) {
    if (str_ptr && *str_ptr) {
        free(*str_ptr);
        *str_ptr = NULL;
    }
}

// Função para fazer trim (remover espaços no início e fim)
// Modifica a string original e retorna um ponteiro para o início do conteúdo
char* trim(char* str) {
    if (!str) return NULL;
    char* end;

    // Trim início
    while (isspace((unsigned char)*str)) str++;

    if (*str == 0) // String só contém espaços
        return str;

    // Trim fim
    end = str + strlen(str) - 1;
    while (end > str && isspace((unsigned char)*end)) end--;

    // Escreve o novo terminador nulo
    *(end + 1) = '\0';

    return str;
}

// Função de comparação para qsort (para ordenar strings)
int compare_strings(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

// Função para separar, ordenar e juntar strings (como cast e listed_in)
char* sortAndJoin(const char* campo) {
    if (campo == NULL || strcmp(campo, "NaN") == 0) {
        return strdup_custom("NaN");
    }

    char* campo_copy = strdup_custom(campo); // Trabalhar com uma cópia
    if (!campo_copy) return strdup_custom("NaN");

    char* items[MAX_CAST_LISTED_ITEMS];
    int count = 0;
    char* token = strtok(campo_copy, ",");

    while (token != NULL && count < MAX_CAST_LISTED_ITEMS) {
        char* trimmed_token = trim(token); // Remove espaços antes/depois
        if (strlen(trimmed_token) > 0) {
            items[count++] = strdup_custom(trimmed_token);
            if (!items[count - 1]) {
                 perror("Erro ao alocar memória para item em sortAndJoin");
                 // Liberar memória alocada até agora
                 for(int i = 0; i < count -1; ++i) free(items[i]);
                 free(campo_copy);
                 return strdup_custom("NaN"); // Ou tratar erro de outra forma
            }
        }
        token = strtok(NULL, ",");
    }
    free(campo_copy); // Libera a cópia usada pelo strtok

    // Ordenar os itens
    qsort(items, count, sizeof(char*), compare_strings);

    // Juntar os itens ordenados em uma nova string
    size_t total_len = 0;
    for (int i = 0; i < count; i++) {
        total_len += strlen(items[i]);
    }
    // Adicionar espaço para ", " e terminador nulo
    total_len += (count > 1 ? (count - 1) * 2 : 0) + 1;

    char* resultado = (char*)malloc(total_len);
    if (!resultado) {
        perror("Erro ao alocar memória para resultado em sortAndJoin");
        // Liberar itens
        for(int i = 0; i < count; ++i) free(items[i]);
        return strdup_custom("NaN"); // Ou tratar erro
    }
    resultado[0] = '\0'; // Iniciar string vazia

    for (int i = 0; i < count; i++) {
        strcat(resultado, items[i]);
        if (i < count - 1) {
            strcat(resultado, ", ");
        }
        free(items[i]); // Liberar cada item após usar
    }

    return resultado;
}



// Função para inicializar um Show com valores padrão "NaN"
// Retorna true se sucesso, false se erro de alocação
bool init_Show_default(Show* s) {
    s->show_id = strdup_custom("NaN");
    s->type = strdup_custom("NaN");
    s->title = strdup_custom("NaN");
    s->director = strdup_custom("NaN");
    s->cast = strdup_custom("NaN");
    s->country = strdup_custom("NaN");
    // Data padrão diferente na versão Java, mas "NaN" é mais consistente
    s->date_added = strdup_custom("NaN");
    s->release_year = 0;
    s->rating = strdup_custom("NaN");
    s->duration = strdup_custom("NaN");
    s->listed_in = strdup_custom("NaN");

    // Verifica se alguma alocação falhou
    if (!s->show_id || !s->type || !s->title || !s->director || !s->cast ||
        !s->country || !s->date_added || !s->rating || !s->duration || !s->listed_in)
    {
        // Libera o que foi alocado antes de retornar erro
        free_string(&s->show_id);
        free_string(&s->type);
        free_string(&s->title);
        free_string(&s->director);
        free_string(&s->cast);
        free_string(&s->country);
        free_string(&s->date_added);
        free_string(&s->rating);
        free_string(&s->duration);
        free_string(&s->listed_in);
        return false;
    }
    return true;
}

// Função para liberar a memória alocada por um Show
void free_Show(Show* s) {
    if (s) {
        free_string(&s->show_id);
        free_string(&s->type);
        free_string(&s->title);
        free_string(&s->director);
        free_string(&s->cast);
        free_string(&s->country);
        free_string(&s->date_added);
        free_string(&s->rating);
        free_string(&s->duration);
        free_string(&s->listed_in);
        // Note: Não usamos free(s) aqui se s não foi alocado dinamicamente.
        // Se a struct Show em si foi alocada com malloc, free(s) seria necessário.
    }
}

// Função para clonar um Show (deep copy)
Show* clone_Show(const Show* original) {
    if (!original) return NULL;

    Show* clone = (Show*)malloc(sizeof(Show));
    if (!clone) {
        perror("Erro ao alocar memória para clone de Show");
        return NULL;
    }

    clone->show_id = strdup_custom(original->show_id);
    clone->type = strdup_custom(original->type);
    clone->title = strdup_custom(original->title);
    clone->director = strdup_custom(original->director);
    clone->cast = strdup_custom(original->cast); // Já está ordenado/formatado no original
    clone->country = strdup_custom(original->country);
    clone->date_added = strdup_custom(original->date_added);
    clone->release_year = original->release_year;
    clone->rating = strdup_custom(original->rating);
    clone->duration = strdup_custom(original->duration);
    clone->listed_in = strdup_custom(original->listed_in); // Já está ordenado/formatado

    // Verifica se alguma alocação falhou durante a clonagem
    if (!clone->show_id || !clone->type || !clone->title || !clone->director || !clone->cast ||
        !clone->country || !clone->date_added || !clone->rating || !clone->duration || !clone->listed_in)
    {
        fprintf(stderr, "Erro: Falha ao alocar memória para string durante clone_Show.\n");
        free_Show(clone); // Libera o que foi alocado
        free(clone); // Libera a struct clone
        return NULL;
    }

    return clone;
}

// Função para imprimir um Show
void imprimir_Show(const Show* s) {
    if (!s) return;
    printf("=> %s ## %s ## %s ## %s ## [%s] ## %s ## %s ## %d ## %s ## %s ## [%s]##\n",
           s->show_id ? s->show_id : "NaN",
           s->title ? s->title : "NaN",
           s->type ? s->type : "NaN",
           s->director ? s->director : "NaN",
           s->cast ? s->cast : "NaN",
           s->country ? s->country : "NaN",
           s->date_added ? s->date_added : "NaN",
           s->release_year,
           s->rating ? s->rating : "NaN",
           s->duration ? s->duration : "NaN",
           s->listed_in ? s->listed_in : "NaN");
}

// Função auxiliar para pegar o campo ou "NaN"
// Retorna uma cópia alocada da string ou "NaN"
char* get_field_or_NaN(char** campos, int index, int max_index) {
    if (index >= max_index || campos[index] == NULL || strlen(campos[index]) == 0) {
        return strdup_custom("NaN");
    }
    // Faz trim antes de retornar para consistência
    char* trimmed_field = trim(campos[index]);
    if (strlen(trimmed_field) == 0){
        return strdup_custom("NaN");
    }
    return strdup_custom(trimmed_field);
}


// Função para ler uma linha CSV e preencher a struct Show
// Retorna true se sucesso, false se erro ou linha inválida
bool ler_Show(Show* s, char* linha) {
    char* campos[MAX_FIELDS];
    int campoIndex = 0;
    bool entreAspas = false;
    char campoAtual[MAX_FIELD_SIZE] = {0}; // Buffer para campo atual
    int charIndex = 0;
    int linha_len = strlen(linha);

    // Limpa a struct Show antes de preencher (libera memória antiga)
    free_Show(s); // Garante que strings antigas sejam liberadas

    // Parsing manual do CSV (simplificado, pode falhar com casos complexos de aspas)
    for (int i = 0; i < linha_len && campoIndex < MAX_FIELDS; i++) {
        char c = linha[i];

        if (c == '"') {
            // Verifica aspas duplas dentro de um campo citado ("")
            if (entreAspas && i + 1 < linha_len && linha[i+1] == '"') {
                 if (charIndex < MAX_FIELD_SIZE - 1) {
                    campoAtual[charIndex++] = '"';
                 }
                 i++; // Pula a segunda aspa
            } else {
                entreAspas = !entreAspas;
            }
        } else if (c == ',' && !entreAspas) {
            campoAtual[charIndex] = '\0'; // Termina a string do campo
            campos[campoIndex++] = strdup_custom(campoAtual);
            if (!campos[campoIndex - 1]) return false; // Erro de alocação
            // Reseta para o próximo campo
            charIndex = 0;
            campoAtual[0] = '\0';
        } else {
            // Adiciona caractere ao campo atual, se houver espaço
            if (charIndex < MAX_FIELD_SIZE - 1) {
                 // Ignora \r (comum em arquivos windows)
                 if (c != '\r') {
                    campoAtual[charIndex++] = c;
                 }
            }
        }
    }
    // Adiciona o último campo
    if (campoIndex < MAX_FIELDS) {
        campoAtual[charIndex] = '\0';
        campos[campoIndex++] = strdup_custom(campoAtual);
         if (!campos[campoIndex - 1]) return false; // Erro de alocação
    }

    // Usar get_field_or_NaN para tratar campos vazios/ausentes
    s->show_id = get_field_or_NaN(campos, 0, campoIndex);
    s->type = get_field_or_NaN(campos, 1, campoIndex);
    s->title = get_field_or_NaN(campos, 2, campoIndex);
    s->director = get_field_or_NaN(campos, 3, campoIndex);

    // Cast e Listed In precisam de tratamento especial (sortAndJoin)
    char* temp_cast = get_field_or_NaN(campos, 4, campoIndex);
    s->cast = sortAndJoin(temp_cast);
    free(temp_cast); // Libera a string temporária retornada por get_field_or_NaN

    s->country = get_field_or_NaN(campos, 5, campoIndex);
    s->date_added = get_field_or_NaN(campos, 6, campoIndex);

    // Release Year
    char* year_str = get_field_or_NaN(campos, 7, campoIndex);
    if (strcmp(year_str, "NaN") != 0) {
        s->release_year = atoi(year_str); // Converte string para int
    } else {
        s->release_year = 0; // Valor padrão se NaN ou erro
    }
    free(year_str);

    s->rating = get_field_or_NaN(campos, 8, campoIndex);
    s->duration = get_field_or_NaN(campos, 9, campoIndex);

    // Listed In
    char* temp_listed_in = get_field_or_NaN(campos, 10, campoIndex);
    s->listed_in = sortAndJoin(temp_listed_in);
    free(temp_listed_in); // Libera a string temporária

    // Libera a memória alocada para os campos individuais
    for (int i = 0; i < campoIndex; i++) {
        free(campos[i]);
    }

    // Verifica se alguma alocação crucial dentro de get_field_or_NaN ou sortAndJoin falhou
    if (!s->show_id || !s->type || !s->title || !s->director || !s->cast ||
        !s->country || !s->date_added || !s->rating || !s->duration || !s->listed_in)
    {
        fprintf(stderr, "Erro: Falha ao alocar memória ao preencher Show struct.\n");
        free_Show(s); // Tenta limpar o que foi alocado
        return false;
    }


    return true; // Leitura bem-sucedida
}

// Função para obter o show_id (retorna const char* para segurança)
const char* getShow_id(const Show* s) {
    return s ? s->show_id : NULL;
}


int main() {
    
    Show base[MAX_ARRAY_SIZE]; // Array de structs
    int count = 0;


    const char* filename = "/tmp/disneyplus.csv";
    FILE* file = fopen(filename, "r");

    char linha[MAX_LINE_SIZE];

    // Pular cabeçalho
    if (fgets(linha, sizeof(linha), file) == NULL) {
        fprintf(stderr, "Erro ao ler o cabeçalho do arquivo CSV.\n");
        fclose(file);
        return 1;
    }

    // Ler cada linha do arquivo
    while (count < MAX_ARRAY_SIZE && fgets(linha, sizeof(linha), file) != NULL) {
        // Remove o caractere de nova linha, se presente
        linha[strcspn(linha, "\n\r")] = 0;

        // Inicializa a struct Show na posição atual do array
        // Não precisamos alocar dinamicamente a struct em si pois está no array `base`
        if (!init_Show_default(&base[count])) {
             fprintf(stderr, "Erro ao inicializar Show na posição %d.\n", count);
             // Libera memória dos shows lidos anteriormente
             for(int i=0; i<count; ++i) free_Show(&base[i]);
             fclose(file);
             return 1;
        }

        // Tenta ler a linha e preencher a struct
        if (ler_Show(&base[count], linha)) {
            count++; // Incrementa contador apenas se a leitura for bem-sucedida
        } else {
            fprintf(stderr, "Aviso: Falha ao processar a linha: %s\n", linha);
            // A memória para base[count] já foi (ou deveria ter sido) liberada dentro de ler_Show em caso de falha.
            // Se init_Show_default foi chamada mas ler_Show falhou, free_Show é necessário.
            // Como ler_Show chama free_Show no início, está coberto.
            // Não incrementamos count.
        }
    }
    fclose(file); // Fecha o arquivo CSV

    // Ler entradas do stdin até encontrar "FIM"
    char entrada[MAX_FIELD_SIZE]; // Buffer para ler a entrada (ID)
    // printf("Digite os IDs dos shows (ou 'FIM' para terminar):\n"); // Opcional: prompt
    while (fgets(entrada, sizeof(entrada), stdin) != NULL) {
        // Remove o caractere de nova linha da entrada
        entrada[strcspn(entrada, "\n\r")] = 0;

        // Verifica se a entrada é "FIM"
        if (strcmp(entrada, "FIM") == 0) {
            break; // Sai do loop
        }

        // Procurar o show_id na base de dados
        bool encontrado = false;
        for (int i = 0; i < count; i++) {
            const char* current_id = getShow_id(&base[i]);
            if (current_id != NULL && strcmp(current_id, entrada) == 0) {
                imprimir_Show(&base[i]);
                encontrado = true;
                break; // Encontrou, não precisa continuar procurando
            }
        }
         // Opcional: Mensagem se não encontrar
        // if (!encontrado) {
        //     printf("ID '%s' não encontrado.\n", entrada);
        // }

    }

    // Liberar toda a memória alocada para as strings dentro das structs Show
    for (int i = 0; i < count; i++) {
        free_Show(&base[i]);
    }

    return 0; // Indica sucesso
}