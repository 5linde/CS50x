#include <cs50.h>
#include <stdio.h>

int main(void)
{
    long number = get_long("Number: ");
    int nrOfDigits = 0, sum = 0, tempDigit = 0, firstDigit = 0, secondDigit = 0;

    while (number != 0)
    {
        tempDigit = number % 10;

        if (number > 10 && number < 100)
        {
            secondDigit = tempDigit;
        }
        else if (number > 0 && number < 10)
        {
            firstDigit = tempDigit;
        }

        if (nrOfDigits % 2 != 0)
        {
            // If tempDigit > 9 add products digits,
            // (same as subtracting 9 from resulting product ex. 12 => 1+2=3 / 12-9=3)
            if (tempDigit * 2 > 9)
            {
                tempDigit = tempDigit * 2 - 9;
            }
            else
            {
                tempDigit *= 2;
            }
        }

        sum = sum + tempDigit;
        number /= 10;
        nrOfDigits++;
    }

    if (sum % 10 != 0)
    {
        printf("INVALID\n");
    }
    else if ((firstDigit == 3 && (secondDigit == 4 || secondDigit == 7)) && nrOfDigits == 15)
    {
        printf("AMEX\n");
    }
    else if ((firstDigit == 5 &&
              (secondDigit == 1 || secondDigit == 2 || secondDigit == 3 || secondDigit == 4 || secondDigit == 5)) &&
             nrOfDigits == 16)
    {
        printf("MASTERCARD\n");
    }
    else if (firstDigit == 4 && (nrOfDigits == 13 || nrOfDigits == 16))
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
