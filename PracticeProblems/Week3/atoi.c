#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int convert(string input);

int main(void)
{
    string input = get_string("Enter a positive integer: ");

    for (int i = 0, n = strlen(input); i < n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }

    // Convert string to int
    printf("%i\n", convert(input));
}

int convert(string input)
{
    if (strlen(input) < 1)
    {
        return 0;
    }

    // take last char convert into int
    // remove last char from string array
    // Call convert() with shorter string

    // Converting char to int using the fact that (int) '0' = 48
    // Ex. (int) '1' = 49 => 49-48 = 1
    int charToInt = (int) input[strlen(input) - 1] - 48;

    // string in C ends with escape character \0
    input[strlen(input) - 1] = '\0';

    return charToInt + 10 * convert(input);
}
