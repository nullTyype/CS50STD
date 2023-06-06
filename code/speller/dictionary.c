// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

unsigned int wordCount = 0;

// TODO: Choose number of buckets in hash table
// N is the table array size;
// define N as an array from 0 to 2525,
// where the first 2 digits is the first letter
// and the 2 last digits the second letter;
const unsigned int N = 2525;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // gets word hash key;
    int hashCode = hash(word);
    // set ptr as table at hash index;
    node *ptr = table[hashCode];

    // search over each node trace until find word or reach NULL;
    while (ptr != NULL)
    {
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }
        else
        {
           ptr = ptr->next;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    int hash[2];
    int length = strlen(word);

    // gets first 2 values and set hash;
    if (length > 1)
    {
        hash[0] = (int)(toupper(word[0]) - 'A');
        hash[1] = (int)(toupper(word[1]) - 'A');
    }
    else
    {
        hash[0] = (int)(toupper(word[0]) - 'A');
    }

    int hashCode = arrToI(hash, length);

    return hashCode;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // define dictionary file;
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Failed to load file.\n");
        return false;
    }

    // temporary char array to store current word;
    char word[LENGTH];

    // while pointes doesn't reach end-of-file,
    // allocates memory for node and copy string to it's word field;
    while (fscanf(file, "%s", word) != EOF)
    {
        // alloc memory for each new created node;
        node *n = malloc(sizeof(node));
        wordCount++;

        // copies word and gets word hash code;
        strcpy(n->word, word);
        int hashCode = hash(n->word);

        // insert n to the begin of the table, making it next point to previous adress table was holding;
        n->next = table[hashCode];
        table[hashCode] = n;
    }

    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    // implicit explained;
    if (wordCount != 0)
    {
        return wordCount;
    }

    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // node declare;
    node *ptr = NULL;
    node *tmp = ptr;

    for (int i = 0; i <= 2525; i++)
    {
        ptr = table[i];
        // free every allocated node;
        while (ptr != NULL)
        {
            ptr = ptr->next;
            free(tmp);
            tmp = ptr;
        }
        free(table[i]);

        if (i == 2525)
        {
            return true;
        }
    }

    return false;
}

// receives an array of integers and returns it's hash code based on it's 2 first digits;
int arrToI(int arr[], int length)
{
    int hashCode = 0;

    if (length > 1)
    {
        for (int i = 0; i < 2; i++)
        {
            // iterates over 2 first digits of array;
            hashCode = hashCode * 100 + arr[i];
        }
    }
    else
    {
        hashCode = arr[0];
    }

    return hashCode;
}
