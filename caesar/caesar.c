#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char rotate(char c, int n);

int main(int argc, string argv[])
{
    // The key that the user should provide
    string keyStr = argv[1];

    // Check if typed no key or more than 1 key
    if (argc == 1 || argc > 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    // Check if the key containes something other than digits
    for (int i = 0, len = strlen(keyStr); i < len ; i++)
    {
        if (!(isdigit(keyStr[i])))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Convert the key to int
    int key = atoi(keyStr);

    // Prompt user for plaintext
    string p = get_string("plaintext:  ");

    // Print each char of the ciphertext one by one
    printf("ciphertext: ");
    for (int i = 0, len = strlen(p) ; i < len ; i++)
    {
        printf("%c", rotate(p[i], key));
    }
    printf("\n");
    return 0;
}

char rotate(char c, int n)
{
    // c: the ascii value of the char
    // (-97) to make it start from zero
    // (%26) to make it rotate
    // (+97) to get the char back to its original ascci value
    if (islower(c))
    {
        return ((c - 97 + n) % 26) + 97;
    }
    else if (isupper(c))
    {
        return ((c - 65 + n) % 26) + 65;
    }
    return c;

}

// Works, but not well designed
// int compute_score(string word)
// {
//     // Make array of the alphabet
//     char alpha[26];
//     int n = 0;
//     for (char c = 'a' ; c <= 'z' ; c++)
//     {
//         alpha [n] = c;
//         n++;
//     }
//     // Convert word to lowercase
//     for (int k = 0 ; k < strlen(word) ; k++)
//     {
//         word[k] = tolower(word[k]);
//     }
//     //Compute Score
//     int score = 0;
//     for (int i = 0 ; i < strlen(word) ; i++)
//     {
//         for (int j = 0 ; j < 26 ; j++)
//         {
//             if (word[i] == alpha[j])
//             {
//                 score = score + POINTS[j];
//             }
//         }

//     }
//     return score;
// }