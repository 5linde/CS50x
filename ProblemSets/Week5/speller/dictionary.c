// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 4051;

// Hash table
node *table[N];

// Size of dictionary
unsigned int dictSize = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int hashIndex = hash(word);
    node *cursor = table[hashIndex];

    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int asciiSum = 0;
    int index = 0;

    // Sum ASCII values of word and use it as hash table buckets
    while (word[index] != '\0')
    {
        asciiSum += toupper(word[index]);
        index++;
    }

    return asciiSum;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Could not load dictionary.\n");
        return false;
    }

    char dictWord[LENGTH + 1];

    while (fscanf(dict, "%s", dictWord) != EOF)
    {
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("Could not allocate memory for node.\n");
            fclose(dict);
            return false;
        }

        strcpy(new_node->word, dictWord);

        // Insert node into hash table
        unsigned int hashIndex = hash(new_node->word);
        new_node->next = table[hashIndex];
        table[hashIndex] = new_node;
        dictSize++;
    }

    fclose(dict);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return dictSize;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
