#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: ");
    string word2 = get_string("Player 2: ");

    // Score both words
    int score1 = compute_score(word1);
    int score2 = compute_score(word2);

    // Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!");
    }
    else if (score1 < score2)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }
}

int compute_score(string word)
{
    int score = 0;
    for (int i = 0, len = strlen(word) ; i < len ; i++)
    {
        if (isupper(word[i]))
        {
            score += POINTS[word[i] - 'A'];
        }
        else if (islower(word[i]))
        {
            score += POINTS[word[i] - 'a'];
        }
    }
    return score;
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
