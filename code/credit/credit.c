#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


char *convertIntegerToChar(int N)
{
    // converts a given number to a array of digits;
    char *arr;
    char arr1[2];

    int index = 0;
    arr = (char *)malloc(2);

    while (N)
    {
        // truncates last number digit;
        arr1[++index] = N % 10 + '0';
        N /= 10;
    }

    int i;
    for (i = 0; i < index; i++)
    {
        arr[i] = arr1[index - i];
    }
    arr[i] = '\0';

    return (char *)arr;
}

void card_type(char str[], int length)
{
    int mult = 0;
    int sum = 0;
    int i;

// calculates if card is valid;
    for (i = 0; i < length; i++)
    {
        int arrPOS = str[i] - '0'; // int version of str[i];
        if (i % 2 == 0)
        {
            if (2 * str[i] >= 106)
            {
                char *arr = convertIntegerToChar(2 * (arrPOS));
                printf("2 TIMES str - '0' = %i\n", 2 * (arrPOS));
                printf("2 TIMES str[%i] = %i\n", i, (2 * (str[i])));
                printf("%i, %i, %i\n", arr[0] - '0', arr[1] - '0', arr[2] - '0');
                mult += arr[0] - '0' + arr [1] - '0';
            }
            else
            {
                mult += 2 * (arrPOS);
            }
        }
        else
        {
            sum += arrPOS;
        }
    }


    int total = sum + mult;
    printf("Total is: %i\n", total);
    string response;

// card matches;
    if (total % 10 == 0)
    {
        if (((length == 13) || (length == 16)) && ((int)(str[0] == 52)))
        {
            response = ("VISA\n");
        }

        else if ((length == 15) && (((int)str[0] == 51)) && (((int)str[1] == 52) || ((int)str[1] == 55)))
        {
            response = ("AMEX\n");
        }

        else if ((length == 16) && (((int)str[0] == 53) && ((int)str[1] == 49 || (int)str[1] == 50 || (int)str[1] == 51
                                    || (int)str[1] == 52 || (int)str[1] == 53)))
        {
            response = ("MASTERCARD\n");
        }
        else
        {
            response = ("INVALID\n");
        }

    }
    else
    {
        response = ("INVALID\n");
    }

    printf("%s", response);
}

int main(void)
{
// get card number;
    long int card =  378282246310005;//get_long("Number: ");
    char stri[20];
    char *str = stri;
// create string version of card;
    sprintf(str, "%li", card);

// gets card length
    int length = strlen(str);
// validates and authenticate card;
    card_type(str, length);
}