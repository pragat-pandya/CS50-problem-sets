// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
#define N 26

// declaring some global variables
int no_of_words_loaded = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
    return tolower(word[0]) - 'a';
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    for (int i = 0; i < N; i++)
    {
        hashtable[i] = NULL;
    }

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // malloc space for a new node on each instance of a new word.
        node *new_node = malloc(sizeof(node));

        // If malloc fails unload the dictionary and return false.
        if (!new_node)
        {
            unload();
            return false;
        }

        // else copy the word into the word field of the node
        else
        {
            strcpy(new_node -> word, word);
            // if a word loaded successfully then increment the num_of_words_loaded
            ++no_of_words_loaded;
        }

        // passing our word to the hash function
        int bucket = hash(word);

        // if it's the first entery in the bucket or more preciesly the bucket contains a NULL pointer
        if (!hashtable[bucket])
        {
            // then bucket points to the newly created node
            hashtable[bucket] = new_node;
            // and the next field of this newly created node points to NULL
            new_node -> next = NULL;
        }

        else
        {
            // else new_node's next field will point to whatever thebucket is pointing to
            new_node -> next = hashtable[bucket];
            // and bucket will now points to the newly created node
            hashtable[bucket] = new_node;
        }

    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return no_of_words_loaded;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // intializing a pointer to such struct node to null to iterate over the link list
    node *cursor = NULL;

    // cursor will then point to where ever the corresponding bucket is pointing to
    cursor = hashtable[hash(word)];

    while (cursor != NULL)
    {
        // if strcasecmp returns 0
        if (!(strcasecmp(cursor -> word, word)))
        {
            // then return true in notion of the word has been found in our hashtable
            return true;
        }
        cursor = cursor -> next;
    }

    // else return false
    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // iterating over the each bucket of the hashtable
    for (int i = 0; i < N; i++)
    {
        // initializing mr_unload to point to *Nth bucket i.e., a pointer to structure node
        node *mr_unload = hashtable[i];

        // repeating till mr_unload becomes a NULL pointer or in other words we reach the last node if that bucket
        while(mr_unload != NULL)
        {
            // temporary pointer to a node
            node *tmp;

            // making it point to where ever the mr_unload is pointing to
            tmp = mr_unload;

            // traversing mr_unload to the next field of the next node in the link list
            mr_unload=mr_unload -> next;

            //freeing the memory pointed by tmp.
            free(tmp);
        }

        //cleaning the hashtable
        hashtable[i] = NULL;
    }

    // return true on succeding
    return true;
}
