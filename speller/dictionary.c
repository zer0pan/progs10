// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <stdlib.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Number of buckets in hash table
const unsigned int N = 26 * 26;

int nwords = 0;

// Hash table
node *table[N];

// Hashes word to a number
unsigned int hash(const char *word)
{
    int num1 = toupper(word[0]) - 'A';
    int num2 = (word[1] != '\0') ? toupper(word[1]) - 'A' : 0;
    return (26 * num1 + num2) % N; // ensure within range (because there is punctuation too)
}

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int ti = hash(word);
    node *ptr = table[ti];
    while (ptr != NULL)
    {
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // open the file
    FILE *source = fopen(dictionary, "r");
    if (source == NULL)
    {
        printf("file could not be opened\n");
        return false;
    }

    // initialize table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // inserting words from dictionary to hash table
    char word[LENGTH + 1];
    while (fscanf(source, "%s", word) != EOF)
    {
        nwords++;
        int ti = hash(word);

        node *n = malloc(sizeof(node)); // i create a pointer which points to a node
        if (n == NULL)
        {
            printf("Allocation failed\n");
            fclose(source);
            return false;
        }
        strcpy(n->word, word);

        // insert at beginning of list
        n->next = table[ti]; // node's (n) pointer next, points wherever pointer table[ti] points
        table[ti] = n;       // pointer table[ti] now points wherever n points
    }

    fclose(source);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return nwords;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *ptr = table[i];
        while (ptr != NULL)
        {
            node *temp = ptr;
            ptr = ptr->next;
            free(temp);
        }
    }
    return true;
}
