#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

typedef struct Game
{
    int id;
    char *name;
    char *releaseDate;
    char *owners;
    double price;
    char **languages;
    int metacritic;
    double userScore;
    int achievements;
    char **publishers;
    char **developers;
    char **categories;
    char **genres;
    char **tags;
} Game;

// Estrutura para a célula da lista encadeada
typedef struct Celula
{
    Game *game;
    struct Celula *prox;
} Celula;

int comparacao = 0;
int movimentacao = 0;

// Libera a memória de um array de strings (terminado por NULL)
void freeArray(char **arr)
{
    if (arr == NULL)
        return;
    for (int i = 0; arr[i] != NULL; i++)
    {
        free(arr[i]);
    }
    free(arr);
}

// Libera toda a memória alocada para um Game
void freeGame(Game *g)
{
    if (g == NULL)
        return;
    free(g->name);
    free(g->releaseDate);
    free(g->owners);
    freeArray(g->languages);
    freeArray(g->publishers);
    freeArray(g->developers);
    freeArray(g->categories);
    freeArray(g->genres);
    freeArray(g->tags);
    free(g);
}

// Remove espaços em branco do início e do fim de uma string
char *trim(char *str)
{
    if (str == NULL)
        return NULL;
    char *end;
    while (isspace((char)*str))
        str++;
    if (*str == 0)
        return str;
    end = str + strlen(str) - 1;
    while (end > str && isspace((char)*end))
        end--;
    end[1] = '\0';
    return str;
}

// Divide uma string por um separador e remove aspas/colchetes
char **split(char *string, char *sep)
{
    if (string == NULL || strlen(string) == 0)
        return NULL;

    // Remove colchetes externos se existirem
    char *temp_str = strdup(string);
    int len = strlen(temp_str);
    if (len > 0 && temp_str[0] == '[')
    {
        memmove(temp_str, temp_str + 1, len);
        len--;
        if (len > 0 && temp_str[len - 1] == ']')
        {
            temp_str[len - 1] = '\0';
            len--;
        }
    }

    char *str = temp_str;
    char *token;
    int count = 0;

    // Contar o número de partes
    char *str_temp = strdup(str);
    char *saveptr_count;
    token = strtok_r(str_temp, sep, &saveptr_count);
    while (token != NULL)
    {
        count++;
        token = strtok_r(NULL, sep, &saveptr_count);
    }
    free(str_temp);

    if (count == 0)
    {
        free(temp_str);
        return (char **)calloc(1, sizeof(char *)); // Retorna array com NULL
    }

    char **result = (char **)malloc(sizeof(char *) * (count + 1));
    int i = 0;
    char *saveptr;

    token = strtok_r(str, sep, &saveptr);
    while (token != NULL)
    {
        char *trimmed = trim(token);

        // Remove aspas simples externas
        int trimmed_len = strlen(trimmed);
        if (trimmed_len >= 2 && trimmed[0] == '\'')
        {
            memmove(trimmed, trimmed + 1, trimmed_len);
            trimmed_len--;
            if (trimmed_len > 0 && trimmed[trimmed_len - 1] == '\'')
            {
                trimmed[trimmed_len - 1] = '\0';
            }
        }
        else if (trimmed_len > 0 && trimmed[trimmed_len - 1] == '\'')
        {
            trimmed[trimmed_len - 1] = '\0';
        }

        result[i++] = strdup(trimmed);
        token = strtok_r(NULL, sep, &saveptr);
    }
    result[i] = NULL;
    free(temp_str);
    return result;
}

// split de CSV
char *splitCSV(char **linha)
{
    if (**linha == '\0')
        return strdup("");

    char *start = *linha;
    char *coluna = NULL;

    if (*start == '"')
    {
        start++;
        char *end = start;
        while (*end != '\0' && *end != '"')
        {
            end++;
        }

        int tam = end - start;
        coluna = (char *)malloc(tam + 1);
        strncpy(coluna, start, tam);
        coluna[tam] = '\0';

        *linha = end;
        if (**linha == '"')
            (*linha)++;
        if (**linha == ',')
            (*linha)++;
    }
    else
    {
        char *c = strchr(start, ',');
        if (c)
        {
            int tam = c - start;
            coluna = (char *)malloc(tam + 1);
            strncpy(coluna, start, tam);
            coluna[tam] = '\0';
            *linha = c + 1;
        }
        else
        {
            coluna = strdup(start);
            *linha = start + strlen(start);
        }
    }

    // Remove espaços em branco antes de retornar
    char *trimmed_coluna = strdup(trim(coluna));
    free(coluna);
    return trimmed_coluna;
}

// Formata a data para dd/MM/yyyy
char *toDate(char *data)
{
    char *newData = (char *)malloc(11); // Formato dd/MM/yyyy\0
    if (data == NULL || strlen(data) == 0 || strcmp(data, "TBD") == 0)
    {
        strcpy(newData, "01/01/1900");
        return newData;
    }

    char mesStr[4] = {0};
    int dia = 1, ano = 1900;
    int args;

    // Tenta ler com dia (ex: Dec 12, 2024)
    args = sscanf(data, "%3s %d, %d", mesStr, &dia, &ano);

    if (args < 3)
    {
        // Tenta ler sem dia (ex: Dec 2024)
        args = sscanf(data, "%3s %d", mesStr, &ano);
        if (args < 2)
        {
            // Tenta ler apenas o ano (ex: 2024)
            if (sscanf(data, "%d", &ano) == 1)
            {
                dia = 1;
                mesStr[0] = 'J';
                mesStr[1] = 'a';
                mesStr[2] = 'n';
                mesStr[3] = '\0';
            }
            else
            {
                // Falha na leitura
                strcpy(newData, "01/01/1900");
                return newData;
            }
        }
    }

    char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    int mesNum = 0;
    for (int i = 0; i < 12; i++)
    {
        if (strncmp(mesStr, months[i], 3) == 0)
        {
            mesNum = i + 1;
            break;
        }
    }

    if (mesNum > 0)
    {
        sprintf(newData, "%02d/%02d/%d", dia, mesNum, ano);
    }
    else
    {
        strcpy(newData, "01/01/1900");
    }

    return newData;
}

// Construtor de Game
Game *new_game()
{
    Game *g = (Game *)malloc(sizeof(Game));
    g->id = 0;
    g->name = strdup("");
    g->releaseDate = strdup("01/01/1900");
    g->owners = strdup("0");
    g->price = 0.0;
    g->languages = (char **)calloc(1, sizeof(char *));
    g->metacritic = 0;
    g->userScore = 0.0;
    g->achievements = 0;
    g->publishers = (char **)calloc(1, sizeof(char *));
    g->developers = (char **)calloc(1, sizeof(char *));
    g->categories = (char **)calloc(1, sizeof(char *));
    g->genres = (char **)calloc(1, sizeof(char *));
    g->tags = (char **)calloc(1, sizeof(char *));
    return g;
}

// Leitura de Game
void lerGame(Game *g, char *linha)
{
    char *linha_copy = strdup(linha);
    char *atual = linha_copy;
    char *colunas[14];
    for (int i = 0; i < 14; i++)
    {
        colunas[i] = splitCSV(&atual);
    }

    g->id = atoi(colunas[0]);
    free(g->name);
    g->name = strdup(colunas[1]);
    free(g->releaseDate);
    g->releaseDate = toDate(colunas[2]);
    free(g->owners);
    g->owners = strdup(colunas[3]);
    g->price = strtod(colunas[4], NULL);

    freeArray(g->languages);
    g->languages = split(colunas[5], "[,]");

    g->metacritic = atoi(colunas[6]);
    g->userScore = strtod(colunas[7], NULL);
    g->achievements = atoi(colunas[8]);

    freeArray(g->publishers);
    g->publishers = split(colunas[9], ",");

    freeArray(g->developers);
    g->developers = split(colunas[10], ",");

    freeArray(g->categories);
    g->categories = split(colunas[11], ",");

    freeArray(g->genres);
    g->genres = split(colunas[12], ",");

    freeArray(g->tags);
    g->tags = split(colunas[13], ",");

    for (int i = 0; i < 14; i++)
    {
        free(colunas[i]);
    }
    free(linha_copy);
}

// Escrita de Game
void imprimirGame(Game *g)
{
    if (g == NULL)
        return;

    printf("=> %d ## %s ## %s ## %s ## ", g->id, g->name, g->releaseDate, g->owners);

    if (g->price == 0.0)
        printf("0.00");
    else
        printf("%.2f", g->price);

    printf(" ## [");
    if (g->languages)
        for (int i = 0; g->languages[i]; i++)
            printf("%s%s", g->languages[i], g->languages[i + 1] ? ", " : "");
    printf("] ## %d ## %.1f ## %d ## [", g->metacritic, g->userScore, g->achievements);
    if (g->publishers)
        for (int i = 0; g->publishers[i]; i++)
            printf("%s%s", g->publishers[i], g->publishers[i + 1] ? ", " : "");
    printf("] ## [");
    if (g->developers)
        for (int i = 0; g->developers[i]; i++)
            printf("%s%s", g->developers[i], g->developers[i + 1] ? ", " : "");
    printf("] ## [");
    if (g->categories)
        for (int i = 0; g->categories[i]; i++)
            printf("%s%s", g->categories[i], g->categories[i + 1] ? ", " : "");
    printf("] ## [");
    if (g->genres)
        for (int i = 0; g->genres[i]; i++)
            printf("%s%s", g->genres[i], g->genres[i + 1] ? ", " : "");
    printf("] ## [");
    if (g->tags)
        for (int i = 0; g->tags[i]; i++)
            printf("%s%s", g->tags[i], g->tags[i + 1] ? ", " : "");
    printf("] ##\n");
}

// Construtor de Celula
Celula *new_celula(Game *game)
{
    Celula *c = (Celula *)malloc(sizeof(Celula));
    c->game = game;
    c->prox = NULL;
    return c;
}

// Compara as datas (yyyy/MM/dd) e o desempate eh pelo ID
int compare(Game *a, Game *b)
{
    comparacao++;

    char **dateA = split(a->releaseDate, "/");
    char **dateB = split(b->releaseDate, "/");

    int aDia = atoi(dateA[0]);
    int aMes = atoi(dateA[1]);
    int aAno = atoi(dateA[2]);

    int bDia = atoi(dateB[0]);
    int bMes = atoi(dateB[1]);
    int bAno = atoi(dateB[2]);

    int result;

    if (aAno != bAno)
    {
        result = aAno - bAno;
    }
    else if (aMes != bMes)
    {
        result = aMes - bMes;
    }
    else if (aDia != bDia)
    {
        result = aDia - bDia;
    }
    else
    {
        result = a->id - b->id;
    }

    freeArray(dateA);
    freeArray(dateB);

    return result;
}

// Encontra o ponteiro para a célula anterior ao pivo
Celula *getAnterior(Celula *primeiro, Celula *pivo)
{
    Celula *i = primeiro;
    while (i != NULL && i->prox != pivo)
    {
        i = i->prox;
    }
    return i;
}

// Particiona a lista 
Celula *particionar(Celula *primeiro, Celula *ultimo)
{
    Game *pivo = ultimo->game;
    Celula *i = primeiro, *j = primeiro;

    while (j != ultimo)
    {
        // Se o elemento for menor que o pivô (para ordenação crescente)
        if (compare(j->game, pivo) < 0)
        {
            // Swap dos dados (Game*)
            Game *temp = i->game;
            i->game = j->game;
            j->game = temp;
            movimentacao += 3; // 3 atribuições para a troca
            i = i->prox;
        }
        j = j->prox;
    }

    // Move o pivô para sua posição final (troca com o elemento apontado por i)
    Game *temp = i->game;
    i->game = ultimo->game;
    ultimo->game = temp;
    movimentacao += 3; // 3 atribuições para a troca

    return i; // Retorna o pivô
}

// Quicksort recursivo na lista encadeada
void quicksortRec(Celula *primeiro, Celula *ultimo)
{
    // Condições de parada: lista vazia, um único elemento, ou a lista está mal formada
    if (primeiro == NULL || ultimo == NULL || primeiro == ultimo || primeiro == ultimo->prox)
        return;

    // Particiona a lista e obtém o ponteiro para a célula do pivô
    Celula *pivo = particionar(primeiro, ultimo);

    // Chamada recursiva para a sub-lista da esquerda
    if (primeiro != pivo)
    {
        // Encontra a célula anterior ao pivô
        Celula *anteriorAoPivo = getAnterior(primeiro, pivo);
        if (anteriorAoPivo != NULL)
        {
            quicksortRec(primeiro, anteriorAoPivo);
        }
    }

    // Chamada recursiva para a sub-lista da direita
    if (pivo != NULL && pivo->prox != NULL)
    {
        quicksortRec(pivo->prox, ultimo);
    }
}

// Pega a última celula da lista
Celula *getUltimo(Celula *i)
{
    while (i != NULL && i->prox != NULL)
        i = i->prox;
    return i;
}

// Chama o quicksortRec
void quicksort(Celula **lista)
{
    if (*lista == NULL)
        return;
    Celula *ultimo = getUltimo(*lista);
    quicksortRec(*lista, ultimo);
}

// Função para criar arquivo de log
void criarLog(const char *matricula, double tempoExecucao)
{
    FILE *logFile = fopen("1526815_quicksort.txt", "w");
    if (logFile != NULL)
    {
        fprintf(logFile, "%s\t%d\t%d\t%.6f\n",
                matricula, comparacao, movimentacao, tempoExecucao);
        fclose(logFile);
    }
}

int main()
{
    Celula *primeiro = NULL, *ultimo = NULL;

    FILE *fp = fopen("/tmp/games.csv", "r");
    if (fp == NULL)
    {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    char linha[4096];
    fgets(linha, sizeof(linha), fp); // Pula cabeçalho

    // Lê todos os jogos do arquivo e armazena em uma lista completa
    while (fgets(linha, sizeof(linha), fp))
    {
        linha[strcspn(linha, "\r\n")] = '\0';
        Game *game = new_game();
        lerGame(game, linha);

        Celula *nova = new_celula(game);
        if (primeiro == NULL)
        {
            primeiro = ultimo = nova;
        }
        else
        {
            ultimo->prox = nova;
            ultimo = nova;
        }
    }
    fclose(fp);

    char entrada[100];
    Celula *lista_final = NULL, *final = NULL; // Lista a ser ordenada

    // Lendo IDs de entrada e construindo a lista a ser ordenada
    while (fgets(entrada, sizeof(entrada), stdin) != NULL)
    {
        entrada[strcspn(entrada, "\r\n")] = '\0';
        char *trimmed_entrada = trim(entrada);

        if (strcmp(trimmed_entrada, "FIM") == 0)
        {
            break;
        }

        int id = atoi(trimmed_entrada);

        // Busca pelo ID na lista completa
        for (Celula *i = primeiro; i != NULL; i = i->prox)
        {
            if (i->game->id == id)
            {
                Celula *nova = new_celula(i->game);
                if (lista_final == NULL)
                {
                    lista_final = final = nova;
                }
                else
                {
                    final->prox = nova;
                    final = nova;
                }
                break;
            }
        }
    }

    // Medir tempo de execução do quicksort
    clock_t inicio = clock();
    quicksort(&lista_final);
    clock_t fim = clock();

    double tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    // Imprime jogos ordenados
    for (Celula *i = lista_final; i != NULL; i = i->prox)
    {
        imprimirGame(i->game);
    }

    criarLog("1526815", tempoExecucao);

    Celula *atual = lista_final;
    while (atual != NULL)
    {
        Celula *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    atual = primeiro;
    while (atual != NULL)
    {
        Celula *proximo = atual->prox;
        freeGame(atual->game); // Libera Game* e seus campos
        free(atual);
        atual = proximo;
    }

    return 0;
}