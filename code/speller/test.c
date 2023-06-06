#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

long int arrToI(long int arr[], int length);

int main(void)
{
    char word[] = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";
    int length = strlen(word);
    long int hash[length];
    for (int i = 0; i < length; i++)
    {
        printf("digit is: %d, word[i]: %c\n", (int)(word[i]), word[i]);
        hash[i] = (int)(toupper(word[i]) - 'A');
        printf("patternized letter is: %i\n", (int)(toupper(word[i]) - 'A'));
    }

    long int converted = arrToI(hash, length);
    printf("converted hash: %li\n", converted);
}

// long int it's dumping due to reach it's maximum value;
long int arrToI(long int arr[], int length)
{
    long int converted = 0;
    for (int i = 0; i < length; i++)
    {
        printf("converted is: %li\n", converted);
        converted = converted * 100 + arr[i];
    }

    return converted;
}

// table pointer's debug;
// node *ptr = malloc(sizeof(node));
// ptr = table[hashCode];
// for (int i = 0; ptr != NULL; i++)
// {
//     printf("pointer: %p\n", ptr);
//     ptr = ptr->next;
// }