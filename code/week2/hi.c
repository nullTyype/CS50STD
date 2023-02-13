#include <cs50.h>
#include <stdio.h>

int main (void)
{
    string array[2];
    array[0] = "HI!";
    array[1] = "BYE!";

    printf("%c%c%c\n", array[0][0], array[0][1], array[0][2]);
    printf("%c%c%c%c\n", array[1][0], array[1][1], array[1][2], array[1][3]);
}