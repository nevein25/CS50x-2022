#include <cs50.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>

int count_words(string text);
int count_letters(string text);
int count_sentences(string text);
float the_grade(int words, int sentences, int letters);

int main(void)
{
    // Get input text from the user
    string text = get_string("Enter text: ");

    // Number of words
    int words = count_words(text);
    // Number of sentences
    int sentences = count_sentences(text);
    // Number of letters
    int letters = count_letters(text);

    // Count the grade
    int grade  = round(the_grade(words, sentences, letters));

    // Print the grade
    if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }

}

int count_letters(string text)
{
    int counter = 0;
    int i = 0;
    while (text[i] != '\0')
    {
        //if (text[i] != '.' && text[i] != '!' && text[i] != '?' && text[i] != ',' && text[i] != ' ' && text[i] != "'")
        // If the letter is not . or ! or ? or , or ' or space
        if (isalpha(text[i]))
        {
            counter++;
        }
        i++;
    }
    return counter;

}

int count_words(string text)
{
    // Start counting from 1, beavause last word has no space after it.
    int counter = 1;
    int i = 0;
    while (text[i] != '\0')
    {
        if (text[i] == ' ')
        {
            counter++;
        }
        i++;
    }
    return counter;
}

int count_sentences(string text)
{
    int counter = 0;
    int i = 0;
    while (text[i] != '\0')
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            counter++;
        }
        i++;
    }
    return counter;
}

float the_grade(int words, int sentences, int letters)
{
    float S = (sentences  / (float) words) * 100.0;
    float L = (letters / (float) words) * 100.0;
    float index = 0.0588 * L - 0.296 * S - 15.8;
    return index;
}