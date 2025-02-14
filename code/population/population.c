#include <cs50.h>
#include <stdio.h>
#include <math.h>

int numberOfYears(int startSize, int endSize);

int main(void)
{
    // TODO: Prompt for start size
    int startSize;
    do
    {
        startSize = get_int("Start size: ");
    }
    while (startSize < 9);

    // TODO: Prompt for end size
    int endSize;
    do
    {
        endSize = get_int("End size: ");
    }
    while (endSize < startSize);

    // TODO: Calculate number of years until we reach threshold
    int years = numberOfYears(startSize, endSize);

    // TODO: Print number of years
    printf("Years: %i\n", years);
}

int numberOfYears(int startSize, int endSize)
{
    float pop = startSize;
    int y = 0;
    for (; pop + pop / 12 <= endSize; y++)
    {
        pop += pop / 12;
        printf("Current population: %f\n", pop);
    }

    return y;
}