// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

//number of buckets in hash table
const unsigned int N = 26;
//initialize the number of words in the dictionary
unsigned int number_of_words = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //hash word tobtain a hash value
    int key = hash(word);
    //access linked list at that index in the hash table
    node *n = table[key];
    //traverse linked list, looking for the word
    while (n != NULL)
    {
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }
        n = n->next;
    }


    return false;
}


// Hashes word to a number
unsigned int hash(const char *word)
{
    int x = tolower(word[0]);
    return x - 97;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char my_word[LENGTH + 1];
    // read strings from file one at a time
    while (fscanf(file, "%s", my_word) != EOF)
    {
        // create a new node for each word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, my_word);
        // hash word to obtain a hash value
        int key = hash(my_word);
        n->next = table[key];
        // insert node into hash table at that location
        table[key] = n;
        number_of_words++;
    }
    // close the dictionary
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (number_of_words > 0)
    {
        return number_of_words;
    }
    else
    {
        return 0;
    }

}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *cursor;
    node *tmp;
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
