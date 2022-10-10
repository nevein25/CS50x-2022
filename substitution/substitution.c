#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>




int main(int argc, string argv[])
{
    // Validating the key


    string key = argv[1];
    // If the user did not provide the key or more than one key
    if (argc == 1 || argc > 2)
    {
        printf("Usage: ./csubstitution key\n");
        return 1;
    }

    // If the key does not contain 26 chars
    else if (strlen(key) != 26)
    {
        printf("Key must contain 26 charcters.\n");
        return 1;
    }

    // Check if the key containes something other than digits
    for (int i = 0, len = strlen(key); i < len ; i++)
    {
        if (isdigit(key[i]))
        {
            printf("Key must only contain alphabetic charcters.\n");
            return 1;
        }
    }

    // Check if the key contains repeated chars
    char check;
    for (int j = 0, len = strlen(key); j < len ; j++)
    {
        check = key[j];
        if (check == key[j + 1])
        {
            printf("Key must not contain repeated charcters.\n");
            return 1;
        }
    }

    // Prompt user for plaintext
    string p = get_string("plaintext:  "); //hello, world

    printf("ciphertext: ");

    // Encrypting
    for (int k = 0, len = strlen(p); k < len ; k++)
    {
        if (isupper(p[k]))
        {
            printf("%c", toupper(key [ p[k] - 'A' ]));
        }
        else if (islower(p[k]))
        {
            printf("%c", tolower(key [ p[k] - 'a' ]));
        }
        else
        {
            printf("%c", p[k]);
        }
    }
    printf("\n");
    return 0;
}

