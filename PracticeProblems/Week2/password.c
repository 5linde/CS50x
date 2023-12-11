// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    bool isUpperCase = false;
    bool isLowerCase = false;
    bool isNumber = false;
    bool isSymbol = false;

    for (int i = 0, n = strlen(password); i < n; i++)
    {
        if (password[i] >= 'A' && password[i] <= 'Z')
        {
            isUpperCase = true;
        }
        else if (password[i] >= 'a' && password[i] <= 'z')
        {
            isLowerCase = true;
        }
        else if (password[i] >= '0' && password[i] <= '9')
        {
            isNumber = true;
        }
        else if ((int) password[i] >= 33 && (int) password[i] <= 47)
        {
            isSymbol = true;
        }
    }

    if (isUpperCase && isLowerCase && isNumber && isSymbol)
    {
        return true;
    }
    else
    {
        return false;
    }
}
