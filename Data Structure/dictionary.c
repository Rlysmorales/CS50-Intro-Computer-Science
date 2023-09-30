// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

//word_count
int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //iterate through using the loop for node
    node *cursor = table[hash(word)];
    while (cursor != 0)
    {   
        //strcasecmp just compare the strings
        if (strcasecmp(tmp->word, word) == 0) 
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
   
    long hashTotal = 0;
    for (int i = 0; i <= strlen(word); i++)
    {   
        //Where you convert the hash to a number
        hashTotal = (hashTotal + tolower(word[i])) % N;

    }
    return hashTotal;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //Load/open the dictionary
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        //failed to open
        return false;
    }
    //create variable string for word
    char *word[LENGTH + 1];
    if (word == NULL)
    {
        //no variable created fail
        return false;
    }
    //While scanning dictionary and write to hash table until EOF
    while (fscanf(dict, "%s", word) != EOF)
    {
        //Here we are managing the memory resources ;
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {   
            //checking if failed return false
            return false;
        }
        //strcpy allows to copy the word into a noce 
        strcpy(n->word, word); 
        hash_current_value = hash(word);
        if (table[hash_current_value] == NULL) 
        {
            n->next = NULL;
        }
        else 
        {
            //reference next to the first node 
            n->next = table[hash_current_value]; 
        }
        table[hash_current_value] = n; 
        //count the words that are being found on the dictionary
        word_count++; 
    }
    //close the file
    fclose(file);
    free(word);
    return true;
}


// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    //check if word is loaded by being greater than 0
    if (word_count > 0)
    {
        return word_count;
    }
    //return fail
    return 0
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
     for (int i = 0; i <= N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next; 
            free(tmp); 
        }

    }
    return true;
}
