#include <stdio.h>
#include <stdbool.h>

int obter_comprimento_texto(char *texto)
{
    int comprimento = 0;
    while (texto[comprimento] != '\0')
    {
        comprimento++;
    }
    return comprimento;
}

bool eh_palindromo_recursivo(char *texto, int inicio, int fim)
{
    if (inicio >= fim)
    {
        return true;
    }
    
    if (texto[inicio] != texto[fim])
    {
        return false;
    }
    
    return eh_palindromo_recursivo(texto, inicio + 1, fim - 1);
}

bool verificar_palindromo(char *entrada)
{
    int comprimento = obter_comprimento_texto(entrada);
    if (comprimento == 0)
    {
        return true;
    }
    return eh_palindromo_recursivo(entrada, 0, comprimento - 1);
}

bool eh_condicao_final(char *texto)
{
    return (texto[0] == 'F' && 
            texto[1] == 'I' && 
            texto[2] == 'M' && 
            texto[3] == '\0');
}

void processar_entrada()
{
    char entrada[100];
    
    while (true)
    {
        scanf(" %[^\n]", entrada);
        getchar();
        
        if (eh_condicao_final(entrada))
        {
            break;
        }
        
        if (verificar_palindromo(entrada))
        {
            printf("SIM\n");
        }
        else
        {
            printf("NAO\n");
        }
    }
}

int main()
{
    processar_entrada();
    return 0;
}