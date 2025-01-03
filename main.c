#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funzione per leggere una stringa dalla tastiera
char *getBinariesNumbers()
{
    char *str = NULL;
    int c;
    size_t size = 0;
    size_t capacity = 1;

    // Alloca memoria iniziale
    str = (char *)malloc(capacity * sizeof(char));
    if (str == NULL)
    {
        fprintf(stderr, "Errore di allocazione della memoria\n");
        exit(EXIT_FAILURE);
    }

    // Leggi caratteri fino a quando non viene premuto Invio
    while ((c = getchar()) != '\n' && c != EOF)
    {
        // Se necessario, aumenta la capacità
        if (size + 1 >= capacity)
        {
            // Raddoppiamo la capacità di memoria
            str = (char *)realloc(str, (capacity *= 2) * sizeof(char));
            if (str == NULL)
            {
                fprintf(stderr, "Errore di riallocazione della memoria\n");
                exit(EXIT_FAILURE);
            }
        }
        str[size++] = c;
    }
    // Aggiungiamo il terminatore di stringa
    str[size] = '\0';
    return str;
}

// Funzione per sommare due numeri binari
char *addBinary(const char *a, const char *b)
{
    int lenA = strlen(a);
    int lenB = strlen(b);
    int maxLen = lenA > lenB ? lenA : lenB;
    char *result = (char *)malloc(maxLen + 2); // +1 per il carry, +1 per il terminatore di stringa
    if (result == NULL)
    {
        fprintf(stderr, "Errore di allocazione della memoria\n");
        exit(EXIT_FAILURE);
    }

    int carry = 0, i = lenA - 1, j = lenB - 1, k = maxLen;
    result[k + 1] = '\0'; // Terminatore di stringa

    while (i >= 0 || j >= 0 || carry)
    {
        int sum = carry;
        if (i >= 0)
            sum += a[i--] - '0';
        if (j >= 0)
            sum += b[j--] - '0';
        result[k--] = (sum % 2) + '0';
        carry = sum / 2;
    }

    return result + k + 1; // Restituisce il puntatore alla posizione corretta
}

int main()
{
    printf("Benvenuto nel software di calcolo binario!\n");

    printf("Inserisci il primo numero binario: ");
    char *firstNum = getBinariesNumbers();
    printf("Inserisci il secondo numero binario: ");
    char *secondNum = getBinariesNumbers();

    // Somma dei numeri binari
    char *result = addBinary(firstNum, secondNum);
    printf("La somma binaria è: %s\n", result);

    // Libera la memoria allocata
    free(firstNum);
    free(secondNum);
    free(result - (strlen(result) - strlen(firstNum) - strlen(secondNum)));

    return 0;
}
