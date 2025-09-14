#include <stdio.h>
#include <stdbool.h>

// Verifica se caractere é letra
bool ehLetra(char c) {
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

// Verifica se caractere é número
bool ehNumero(char c) {
    return (c >= '0' && c <= '9');
}

// Verifica se caractere é vogal
bool ehVogalChar(char c) {
    char lista[] = "AEIOUaeiou";
    int i = 0;
    while (lista[i] != '\0') {
        if (c == lista[i]) return true;
        i++;
    }
    return false;
}

// Apenas vogais
bool apenasVogaisRec(char *s, int i) {
    if (s[i] == '\0') return (i > 0);
    if (!ehLetra(s[i]) || !ehVogalChar(s[i])) return false;
    return apenasVogaisRec(s, i + 1);
}

// Apenas consoantes
bool apenasConsoantesRec(char *s, int i) {
    if (s[i] == '\0') return (i > 0);
    if (!ehLetra(s[i]) || ehVogalChar(s[i])) return false;
    return apenasConsoantesRec(s, i + 1);
}

// Apenas inteiro
bool apenasInteiroRec(char *s, int i) {
    if (s[i] == '\0') return (i > 0);
    if (!ehNumero(s[i])) return false;
    return apenasInteiroRec(s, i + 1);
}

// Apenas real
bool apenasRealRec(char *s, int i, int separador) {
    if (s[i] == '\0') return (i > 0 && separador <= 1);
    if (ehNumero(s[i])) return apenasRealRec(s, i + 1, separador);
    if (s[i] == '.' || s[i] == ',') return apenasRealRec(s, i + 1, separador + 1);
    return false;
}

bool iguaisRec(char *a, char *b, int i) {
    if (a[i] == '\0' && b[i] == '\0') return true;
    if (a[i] != b[i]) return false;
    return iguaisRec(a, b, i + 1);
}

void removerQuebraLinha(char *s, int i) {
    if (s[i] == '\0') return;
    if (s[i] == '\n') {
        s[i] = '\0';
        return;
    }
    removerQuebraLinha(s, i + 1);
}

void processarEntrada() { // Leitura recursiva
    char texto[1000];

    if (fgets(texto, sizeof(texto), stdin) == NULL) return;

    removerQuebraLinha(texto, 0);

    if (iguaisRec(texto, "FIM", 0)) return;

    printf("%s %s %s %s\n",
           apenasVogaisRec(texto, 0) ? "SIM" : "NAO",
           apenasConsoantesRec(texto, 0) ? "SIM" : "NAO",
           apenasInteiroRec(texto, 0) ? "SIM" : "NAO",
           apenasRealRec(texto, 0, 0) ? "SIM" : "NAO");

    processarEntrada(); // Recursão
}

int main() {
    processarEntrada();
    return 0;
}
