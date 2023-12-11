#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Prompt the user for height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (!(height >= 1 && height <= 8));

    int startPadding = height - 1;
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < startPadding; k++)
        {
            printf(" ");
        }

        for (int j = 0; j < 2 * (i + 2); j++)
        {
            if (j > i && j < i + 3)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        startPadding--;
        printf("\n");
    }
}
