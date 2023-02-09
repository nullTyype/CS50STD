#include "../cs50.h"
#include "../cs50.c"
#include <stdio.h>

void draw(int height);

int main(void)
{
    int height;
    // Get pyramid height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    draw(height);
}

void draw(int height)
{
    int j = 1;
    int k = height - 1;
    // height constructor;
    for (int i = 0; i < height; i++)
    {
        printf("%*s%.*s  %.*s\n", k, "", j, "########", j, "########"); // Put k spaces before # string, after building the text structure;
        j++;
        k--;
    }
}