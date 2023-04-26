#include <../../cs50.h>
#include <stdio.h>

void draw(int height);

int main(void)
{
    // do
    // {
    int height;
    // Get pyramid height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    draw(height);
    // }
    // while (true);
}

void draw(int height)
{
    int j = 1;
    int k = height - 1;
    string hash = "########";
    // height constructor;
    for (int i = 0; i < height; i++)
    {
        printf("%*s%.*s  %.*s\n", k, "", j, hash, j, hash); // Put k spaces before # string, after building the text structure;
        j++;
        k--;
    }
}