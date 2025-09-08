#include <stdio.h>

int somaRecursiva(int valor) {
    return (valor == 0) ? 0 : (valor % 10 + somaRecursiva(valor / 10));
}

int somaIterativa(int valor) {
    int soma = 0;
    while (valor > 0) {
        soma += valor % 10;
        valor /= 10;
    }
    return soma;
}

int main() {
    int numero;

    while (scanf("%d", &numero) == 1) {
        printf("%d\n", somaRecursiva(numero));
    }

    return 0;
}
