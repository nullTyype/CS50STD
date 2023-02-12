#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* convertIntegerToChar(int N){
    char* arr;
    char arr1[2];

    int index = 0;
    arr = (char*)malloc(2);

    while (N){
        arr1[++index] = N % 10 + '0';
        N /= 10;
    }

    int i;
    for (i = 0; i < index; i++){
        arr[i] = arr1[index - i];
    }
    arr[i] = '\0';

    return (char*)arr;
}

int main (void)
{
    // get card number
    long int card = 4003600000000014;
    char stri[20];
    char *str = stri;
    // create string version of card
    sprintf(str, "%li", card);

    // gets card length
    int length = strlen(str);

    int mult = 0;
    int sum = 0;
    int i;

    for (i = 0; i < length; i++){
        int arrPOS = str[i] - '0';
        if (i % 2 == 0){
            if (2*str[i] >= 106){
                char* arr = convertIntegerToChar(2 * (arrPOS));
                // printf("2 TIMES str - '0' = %i\n", 2 * (arrPOS));
                // printf("2 TIMES str[%i] = %i\n", i, (2*(str[i])));
                // printf("%i, %i, %i\n", arr[0] - '0', arr[1] - '0', arr[2] - '0');
                mult += arr[0] - '0' + arr [1] - '0';
            }
            else {
                mult += 2*(arrPOS);
            }
        }
        else {
            sum += arrPOS;
        }
    }



    int total = sum + mult;
    printf("TOTAL: %i\n", total);
    if (total % 10 == 0){
        printf("VALID\n");
    }
    else {
        printf("INVALID\n");
    }

}