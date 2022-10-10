// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>

#include "dictionary.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;
int static numOfWords = 0;
// Hash table
// Every element of that array is a pointer to a node
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{

    // Hash the word
    //node *head = malloc(sizeof(node));
    unsigned int idx = hash(word);
    node *head = table[idx];
    while (head != NULL)
    {
        if (strcasecmp(head->word, word) == 0)
        {
            return true;
        }
        head = head->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function

    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open dictionary file
    FILE *f = fopen(dictionary, "r");
    if (f == NULL)
    {
        printf("Can not open file\n");
        return false;
    }
    // Read strings from the file
    char buffer[LENGTH + 1];
    while (fscanf(f, "%s", buffer) != EOF)
    {
        // Create a new node
        node *newNode = malloc(sizeof(node));
        if (newNode == NULL)
        {
            return false;
        }
        strcpy(newNode->word, buffer);
        // Hash the word
        unsigned int idx = hash(buffer);
        // Isert node into hash table

        if (table[idx] == NULL)
        {
            newNode->next = NULL;
        }
        else
        {
            newNode->next = table[idx];
        }
        table[idx] = newNode;
        numOfWords++;

    }
    fclose(f);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return numOfWords;
}

// Unloads dictionary from memory, returning true if successful, else false

bool unload(void)
{
    // TODO
    node *cursor = table[0];
    node *tmp = cursor;
    for (int i = 0 ; i < N ; i++)
    {
        cursor = table[i];
        tmp = cursor;
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }

    }

    return true;
}
