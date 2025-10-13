#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <ctype.h>

#define MAX_GAMES 1850
#define MAX_STRING 300 
#define MAX_ARRAY 50
#define MAX_LANG 20

// Estrutura do jogo
typedef struct Game {
    int id;
    char name[MAX_STRING];
    char releaseDate[20];
    int estimatedOwners;
    float price;
    char supportedLanguages[MAX_LANG][MAX_STRING];
    int supportedLanguagesCount;
    int metacriticScore;
    float userScore;
    int achievements;
    char publishers[MAX_ARRAY][MAX_STRING];
    int publishersCount;
    char developers[MAX_ARRAY][MAX_STRING];
    int developersCount;
    char categories[MAX_ARRAY][MAX_STRING];
    int categoriesCount;
    char genres[MAX_ARRAY][MAX_STRING];
    int genresCount;
    char tags[MAX_ARRAY][MAX_STRING];
    int tagsCount;
    struct Game *prox;
} Game;

// Cópia de string limitada
void my_strncpy(char *dest, const char *src, size_t n) {
    size_t i;
    for (i = 0; i < n - 1 && src[i] != '\0'; i++) dest[i] = src[i];
    dest[i] = '\0'; 
}

// Remove espaços do início e fim
void trim(char *str) {
    if (str == NULL || strlen(str) == 0) return;
    int start = 0, end = strlen(str) - 1;
    while (start <= end && isspace(str[start])) start++;
    while (end >= start && isspace(str[end])) end--;
    int i;
    for (i = 0; start <= end; i++, start++) str[i] = str[start];
    str[i] = '\0';
}

// Converte string para inteiro
int toInt(char *str) {
    return atoi(str);
}

// Converte string para float, tratando casos especiais
float toFloat(char *str) {
    if (strcmp(str, "Free to Play") == 0) return 0.0f;
    if (strcmp(str, "tbd") == 0) return -1.0f;
    return atof(str);
}

// Converte data de "MMM dd, yyyy" para "dd/MM/yyyy"
void toDate(char *input, char *output) {
    trim(input);

    if (strlen(input) < 11) { 
        my_strncpy(output, "01/01/2025", 20);
        return;
    }

    char mes_str[4], dia_str[3], ano_str[5];
    int i = 0, j = 0;

    // Pega o mês
    while(input[i] != ' ' && j < 3) mes_str[j++] = input[i++];
    mes_str[j] = '\0';
    i++; j = 0;

    // Pega o dia
    while(input[i] != ',' && j < 2) dia_str[j++] = input[i++];
    dia_str[j] = '\0';
    i += 2; // pula ", "
    j = 0;

    // Pega o ano
    while(input[i] != '\0' && j < 4) ano_str[j++] = input[i++];
    ano_str[j] = '\0';

    char mes_num[3];
    if (strcmp(mes_str,"Jan")==0) my_strncpy(mes_num,"01",3);
    else if (strcmp(mes_str,"Feb")==0) my_strncpy(mes_num,"02",3);
    else if (strcmp(mes_str,"Mar")==0) my_strncpy(mes_num,"03",3);
    else if (strcmp(mes_str,"Apr")==0) my_strncpy(mes_num,"04",3);
    else if (strcmp(mes_str,"May")==0) my_strncpy(mes_num,"05",3);
    else if (strcmp(mes_str,"Jun")==0) my_strncpy(mes_num,"06",3);
    else if (strcmp(mes_str,"Jul")==0) my_strncpy(mes_num,"07",3);
    else if (strcmp(mes_str,"Aug")==0) my_strncpy(mes_num,"08",3);
    else if (strcmp(mes_str,"Sep")==0) my_strncpy(mes_num,"09",3);
    else if (strcmp(mes_str,"Oct")==0) my_strncpy(mes_num,"10",3);
    else if (strcmp(mes_str,"Nov")==0) my_strncpy(mes_num,"11",3);
    else if (strcmp(mes_str,"Dec")==0) my_strncpy(mes_num,"12",3);
    else my_strncpy(mes_num,"01",3);

    sprintf(output, "%02d/%s/%s", atoi(dia_str), mes_num, ano_str);
}

// Divide string de array em elementos
int splitArray(char *str, char arr[MAX_ARRAY][MAX_STRING]) {
    int count = 0;
    trim(str);
    if (strlen(str) <= 2) return 0;

    char temp[MAX_STRING];
    int temp_idx = 0;

    for (int i = 0; i < strlen(str); i++) {
        if (str[i]=='['||str[i]==']'||str[i]=='\'') continue; // remove colchetes e aspas
        if (str[i]==',') {
            temp[temp_idx]='\0';
            trim(temp);
            my_strncpy(arr[count++], temp, MAX_STRING);
            temp_idx=0;
            if (i+1<strlen(str) && str[i+1]==' ') i++;
        } else {
            if (temp_idx < MAX_STRING-1) temp[temp_idx++]=str[i];
        }
    }
    temp[temp_idx]='\0';
    trim(temp);
    if (strlen(temp)>0) my_strncpy(arr[count++], temp, MAX_STRING);

    return count;
}

// Lê os dados de uma linha CSV e preenche o struct
void lerGame(Game *g, char *linha) {
    char tokens[14][MAX_STRING];
    int token_idx = 0, char_idx = 0, inQuotes = 0;

    // Separa os campos por vírgula considerando aspas
    for (int i = 0; i < strlen(linha); i++) {
        if (linha[i]=='"') inQuotes = !inQuotes;
        else if (linha[i]==',' && !inQuotes) {
            tokens[token_idx][char_idx]='\0';
            token_idx++;
            char_idx=0;
            if (token_idx>=14) break;
        } else {
            if (char_idx<MAX_STRING-1) tokens[token_idx][char_idx++]=linha[i];
        }
    }
    tokens[token_idx][char_idx]='\0';

    g->id = (token_idx>=0 && strlen(tokens[0])>0)?toInt(tokens[0]):0;
    my_strncpy(g->name,(token_idx>=1)?tokens[1]:"",MAX_STRING);
    toDate((token_idx>=2)?tokens[2]:"", g->releaseDate);
    g->estimatedOwners = (token_idx>=3 && strlen(tokens[3])>0)?toInt(tokens[3]):0;
    g->price = (token_idx>=4)?toFloat(tokens[4]):0.0f;
    g->supportedLanguagesCount = (token_idx>=5)?splitArray(tokens[5], g->supportedLanguages):0;
    g->metacriticScore = (token_idx>=6 && strlen(tokens[6])>0)?toInt(tokens[6]):0;
    g->userScore = (token_idx>=7)?toFloat(tokens[7]):0.0f;
    g->achievements = (token_idx>=8 && strlen(tokens[8])>0)?toInt(tokens[8]):0;
    g->publishersCount = (token_idx>=9)?splitArray(tokens[9], g->publishers):0;
    g->developersCount = (token_idx>=10)?splitArray(tokens[10], g->developers):0;
    g->categoriesCount = (token_idx>=11)?splitArray(tokens[11], g->categories):0;
    g->genresCount = (token_idx>=12)?splitArray(tokens[12], g->genres):0;
    g->tagsCount = (token_idx>=13)?splitArray(tokens[13], g->tags):0;
    g->prox=NULL;
}

// Imprime array
void imprimirArray(char arr[MAX_ARRAY][MAX_STRING], int count) {
    printf("[");
    for (int i = 0; i < count; i++) {
        printf("%s", arr[i]);
        if (i < count-1) printf(", ");
    }
    printf("]");
}

// Imprime todos os dados de um jogo
void imprimir(Game *g) {
    printf("=> %d ## %s ## %s ## %d ## %.2f ## ", 
        g->id, g->name, g->releaseDate, g->estimatedOwners, g->price);
    imprimirArray(g->supportedLanguages, g->supportedLanguagesCount);
    printf(" ## %d ## %.1f ## %d ## ", g->metacriticScore, g->userScore, g->achievements);
    imprimirArray(g->publishers, g->publishersCount);
    printf(" ## ");
    imprimirArray(g->developers, g->developersCount);
    printf(" ## ");
    imprimirArray(g->categories, g->categoriesCount);
    printf(" ## ");
    imprimirArray(g->genres, g->genresCount);
    printf(" ## ");
    imprimirArray(g->tags, g->tagsCount);
    printf(" ##\n");
}

int main() {
    Game *primeiro = NULL;
    Game *ultimo = NULL;
    Game *games[MAX_GAMES];
    int n = 0;

    // Abre o arquivo CSV
    FILE *f = fopen("/tmp/games.csv", "r");
    if (!f) {
        printf("Arquivo nao encontrado\n");
        return 1;
    }

    char linha[MAX_STRING * 4];     
    fgets(linha, sizeof(linha), f); // Pula o cabeçalho

    // Lê todas as linhas do CSV
    while (fgets(linha, sizeof(linha), f)) {
        int len = strlen(linha);
        if (len > 0 && linha[len - 1] == '\n')
            linha[len - 1] = '\0';

        Game *novo = (Game *)malloc(sizeof(Game));
        lerGame(novo, linha);
        games[n++] = novo;

        if (primeiro == NULL) {
            primeiro = ultimo = novo;
        } else {
            ultimo->prox = novo;
            ultimo = novo;
        }
    }

    fclose(f); // Fecha o CSV

    // Lê IDs do usuário e imprime os jogos correspondentes
    char input[MAX_STRING];
    int continuar = 1;

    while (continuar && fgets(input, MAX_STRING, stdin)) {
        int len = strlen(input);
        if (len > 0 && input[len - 1] == '\n')
            input[len - 1] = '\0';

        if (strcmp(input, "FIM") == 0) {
            continuar = 0; 
        } else {
            int id = toInt(input);
            int encontrado = 0;

            for (int i = 0; i < n; i++) {
                if (games[i]->id == id) {
                    imprimir(games[i]);
                    encontrado = 1;
                    i = n;
                }
            }
            if (!encontrado)
                printf("Jogo com ID %d nao encontrado.\n", id);
        }
    }

    // Libera memória alocada
    for (int i = 0; i < n; i++)
        free(games[i]);

    return 0;
}
