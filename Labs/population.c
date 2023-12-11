#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int startSize;
    do
    {
        startSize = get_int("Start size of the population: ");
    }
    while (startSize < 9);

    // TODO: Prompt for end size
    int endSize;
    do
    {
        endSize = get_int("End size of the population: ");
    }
    while (endSize < startSize);

    // TODO: Calculate number of years until we reach threshold
    int currentSize = startSize;
    int years = 0;
    while (currentSize < endSize)
    {
        currentSize = currentSize + (currentSize / 3) - (currentSize / 4);
        years++;
    }

    // TODO: Print number of years
    printf("Years: %i \n", years);
}
