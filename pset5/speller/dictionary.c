// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 100000;
unsigned int size_dic = 0;
// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // get the index of the word
    unsigned int index = hash(word);
    node *cursor = table[index];

    // search, while there are words, for the word we're looking for
    while (cursor != NULL)
    {

        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }

        cursor = cursor->next;
    }
    // if it was not found return false
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // http://www.cse.yorku.ca/~oz/hash.html
    unsigned long hash = 5381;
    int c;
    while ((c = toupper(*word++)))
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r"); // open the dictonary file
    if (file == NULL)
    {
        return false;
    }

    char insert_word[LENGTH + 1];
    while (fscanf(file, "%s", insert_word) != EOF) // returns EOF when it reaches the end of the file
    {
        node *n = malloc(sizeof(node)); // memory for new nodes
        if (n == NULL)
        {
            unload();
            return false;
        }

        strcpy(n->word, insert_word); // copy the word into the new node
        unsigned int index = hash(insert_word); // determine the linked list we should use

        n->next = table[index];
        table[index] = n;

        // increase the size
        size_dic += 1;
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (size_dic > 0)
    {
        return size_dic;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; ++i)
    {
        node *n = table[i];

        while (n != NULL)
        {
            node *aux = n;
            n = n->next;
            free(aux);
        }

        // if we have freed all the linked lists from before
        if (i == N - 1 && n == NULL)
        {
            return true;
        }
    }
    return false;
}