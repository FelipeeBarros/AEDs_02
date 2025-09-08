#include <stdio.h>
#include <stdbool.h>

bool ehLetra(char c)
{
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}

bool ehNumero(char c)
{
    return (c >= '0' && c <= '9');
}

bool ehVogalChar(char c)
{
    char lista[] = "AEIOUaeiou";
    for (int i = 0; lista[i] != '\0'; i++)
    {
        if (c == lista[i])
            return true;
    }
    return false;
}

bool apenasVogais(char *s)
{
    if (*s == '\0')
        return false;
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (!ehLetra(s[i]) || !ehVogalChar(s[i]))
            return false;
    }
    return true;
}

bool apenasConsoantes(char *s)
{
    if (*s == '\0')
        return false;
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (!ehLetra(s[i]) || ehVogalChar(s[i]))
            return false;
    }
    return true;
}

bool apenasInteiro(char *s)
{
    if (*s == '\0')
        return false;
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (!ehNumero(s[i]))
            return false;
    }
    return true;
}

bool apenasReal(char *s)
{
    if (*s == '\0')
        return false;
    int separador = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        if (ehNumero(s[i]))
            continue;
        if (s[i] == '.' || s[i] == ',')
            separador++;
        else
            return false;
    }
    return (separador <= 1);
}

bool iguais(char *a, char *b)
{
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0')
    {
        if (a[i] != b[i])
            return false;
        i++;
    }
    return (a[i] == '\0' && b[i] == '\0');
}

int main()
{
    char texto[1000];

    while (fgets(texto, sizeof(texto), stdin))
    {

        for (int i = 0; texto[i] != '\0'; i++)
        {
            if (texto[i] == '\n')
            {
                texto[i] = '\0';
                break;
            }
        }

        if (iguais(texto, "FIM"))
            break;

        printf("%s %s %s %s\n",
               apenasVogais(texto) ? "SIM" : "NAO",
               apenasConsoantes(texto) ? "SIM" : "NAO",
               apenasInteiro(texto) ? "SIM" : "NAO",
               apenasReal(texto) ? "SIM" : "NAO");
    }

    return 0;
}
