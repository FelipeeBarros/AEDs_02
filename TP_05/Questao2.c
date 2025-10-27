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

typedef struct Celula
{
    Game *game;
    struct Celula *prox;
} Celula;

// Variáveis globais para contagem
int comparacao = 0;
int movimentacao = 0;

// Libera a memória de um array de strings
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

// Divide uma string por um separador
char **split(char *string, char *sep)
{
    if (string == NULL || strlen(string) == 0)
        return NULL;

    char *str = strdup(string);
    char *temp = strdup(str);
    int count = 0;

    char *partes = strtok(temp, sep);
    while (partes != NULL)
    {
        count++;
        partes = strtok(NULL, sep);
    }
    free(temp);

    if (count == 0)
    {
        free(str);
        return NULL;
    }

    char **result = (char **)malloc(sizeof(char *) * (count + 1));
    partes = strtok(str, sep);
    int i = 0;
    while (partes != NULL)
    {
        char *trimmed = trim(partes);
        if (trimmed[0] == '\'')
        {
            memmove(trimmed, trimmed + 1, strlen(trimmed));
        }
        if (strlen(trimmed) > 0 && trimmed[strlen(trimmed) - 1] == '\'')
        {
            trimmed[strlen(trimmed) - 1] = '\0';
        }
        result[i++] = strdup(trimmed);
        partes = strtok(NULL, sep);
    }
    result[i] = NULL;
    free(str);
    return result;
}

// split de CSV
char *splitCSV(char **linha)
{
    if (**linha == '\0')
        return strdup("");

    char *start = *linha;
    char *coluna;

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

            int len = strlen(coluna);
            if (len > 0 && coluna[len - 1] == '"')
            {
                coluna[len - 1] = '\0';
            }
        }
    }
    return coluna;
}

// Formata a data para dd/MM/yyyy
char *toDate(char *data)
{
    if (data == NULL || strlen(data) == 0)
        return strdup("01/01/1900");

    char *newData = (char *)malloc(11);
    char mesStr[4] = {0};
    int dia = 1, ano = 1900;

    if (sscanf(data, "%3s %d, %d", mesStr, &dia, &ano) >= 2 || sscanf(data, "%3s %d", mesStr, &ano) >= 2)
    {
        char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        int mesNum = 0;
        int i = 0;
        int found = 0;

        while (i < 12 && !found)
        {
            if (strncmp(mesStr, months[i], 3) == 0)
            {
                mesNum = i + 1;
                found = 1;
            }
            i++;
        }

        if (mesNum > 0)
        {
            sprintf(newData, "%02d/%02d/%d", dia, mesNum, ano);
            return newData;
        }
    }
    strcpy(newData, "01/01/1900");
    return newData;
}

// Construtor de Game
Game *new_game()
{
    Game *g = (Game *)malloc(sizeof(Game));
    g->id = 0;
    g->name = NULL;
    g->releaseDate = NULL;
    g->owners = NULL;
    g->price = 0.0;
    g->languages = NULL;
    g->metacritic = 0;
    g->userScore = 0.0;
    g->achievements = 0;
    g->publishers = NULL;
    g->developers = NULL;
    g->categories = NULL;
    g->genres = NULL;
    g->tags = NULL;
    return g;
}

// Libera toda a memoria
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

// Leitura de Game
void lerGame(Game *g, char *linha)
{
    char *atual = linha;
    char *colunas[14];
    for (int i = 0; i < 14; i++)
    {
        colunas[i] = splitCSV(&atual);
    }

    g->id = atoi(colunas[0]);
    g->name = strdup(colunas[1]);
    g->releaseDate = toDate(colunas[2]);
    g->owners = strdup(colunas[3]);
    g->price = strtof(colunas[4], NULL);
    g->languages = split(colunas[5], "[,]");
    g->metacritic = atoi(colunas[6]);
    g->userScore = strtof(colunas[7], NULL);
    g->achievements = atoi(colunas[8]);
    g->publishers = split(colunas[9], ",");
    g->developers = split(colunas[10], ",");
    g->categories = split(colunas[11], ",");
    g->genres = split(colunas[12], ",");
    g->tags = split(colunas[13], ",");

    for (int i = 0; i < 14; i++)
    {
        free(colunas[i]);
    }
}

// Escrita de Game
void imprimirGame(Game *g)
{
    if (g == NULL)
        return;

    printf("=> %d ## %s ## %s ## %s ## ", g->id, g->name, g->releaseDate, g->owners);

    if (g->price == 0.0)
        printf("0.0");
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

// Ordenação por Seleção
void selecao(Celula *primeiro)
{
    if (primeiro == NULL || primeiro->prox == NULL)
        return;

    Celula *menor;
    Game *temp;

    for (Celula *i = primeiro; i->prox != NULL; i = i->prox)
    {
        menor = i;

        for (Celula *j = i->prox; j != NULL; j = j->prox)
        {
            comparacao++;
            // Compara os nomes dos jogos
            if (strcmp(j->game->name, menor->game->name) < 0)
            {
                menor = j;
            }
        }

        // swap
        if (menor != i)
        {
            temp = i->game;
            i->game = menor->game;
            menor->game = temp;
            movimentacao++;
        }
    }
}

// Função para criar arquivo de log
void criarLog(const char *matricula, double tempoExecucao)
{
    FILE *logFile = fopen("1526815_selecao.txt", "w");
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

    char linha[2048];
    fgets(linha, sizeof(linha), fp); // Pula cabeçalho

    // Lê todos os jogos do arquivo
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

    Celula *lista = NULL, *final = NULL;
    char entrada[100];

    // Processa entrada do usuário e filtra jogos
    while (fgets(entrada, sizeof(entrada), stdin) != NULL)
    {
        entrada[strcspn(entrada, "\r\n")] = '\0';
        if (strcmp(entrada, "FIM") == 0)
        {
            break;
        }

        int id = atoi(entrada);

        // Busca pelo ID na lista completa
        for (Celula *i = primeiro; i != NULL; i = i->prox)
        {
            if (i->game->id == id)
            {
                Celula *nova = new_celula(i->game);
                if (lista == NULL)
                {
                    lista = final = nova;
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

    // Medir tempo de execução da seleção
    clock_t inicio = clock();
    selecao(lista);
    clock_t fim = clock();

    double tempoExecucao = ((double)(fim - inicio)) / CLOCKS_PER_SEC;

    // Imprime jogos ordenados
    for (Celula *i = lista; i != NULL; i = i->prox)
    {
        imprimirGame(i->game);
    }

    // Gerar log
    criarLog("1526815", tempoExecucao);

    // Libera a lista filtrada
    Celula *atual = lista;
    while (atual != NULL)
    {
        Celula *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    // Libera a lista completa
    atual = primeiro;
    while (atual != NULL)
    {
        Celula *proximo = atual->prox;
        freeGame(atual->game);
        free(atual);
        atual = proximo;
    }

    return 0;
}