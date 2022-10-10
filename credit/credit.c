#include <cs50.h>
#include <stdio.h>

int length(long number);
long firstTwoDigits(long number);

int main(void)
{

    long sum = 0, secPart = 0;
    long n, r;

    // Prompt user for credit card number
    long number = get_long("enter number: ");

    // Get the first two digits of the credit card number
    int fisrtDigits = firstTwoDigits(number);

    // Calculate the length of credit card numbers
    int theLength = length(number);


    // Cut the credit card number into two parts
    while (number != 0)
    {
        // First part
        n = number % 10;
        // Sum the of the first part
        sum = sum + n;
        number = number / 10;

        // Second part
        r = number % 10;
        r = r * 2;
        secPart = secPart * 10 + r;
        number = number / 10;

    }



    // Sum of the second part
    int n2, sum2 = 0;
    while (secPart != 0)
    {
        n2 = secPart % 10;
        sum2 = sum2 + n2;
        secPart = secPart / 10;
    }
    // Sum of the two parts
    int final = sum + sum2;

    if (final % 10 != 0)
    {
        printf("INVALID\n");
    }
    else
    {
        if ((theLength == 15) && ((fisrtDigits == 34) || (fisrtDigits == 37)))
        {
            printf("AMEX\n");
        }
        else if ((theLength == 16) && (fisrtDigits >= 51 && fisrtDigits <= 55))
        {
            printf("MASTERCARD\n");
        }
        else if (((theLength == 13) || (theLength == 16)) && ((fisrtDigits >= 40) && (fisrtDigits <= 49)))
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }

}

int length(long number)
{
    int counter = 0;
    while (number != 0)
    {
        number = number / 10;
        counter++;
    }
    return counter;
}

long firstTwoDigits(long number)
{
    while (number >= 100)
    {
        number = number / 10;
    }
    return number;
}
