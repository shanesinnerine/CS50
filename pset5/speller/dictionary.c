// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 1000;

//Counter
int counter[N];

// hash table
node *table[N];
// Returns true if word is in dictionary else false
bool check(const char *word)
{
    //Hash word
    int index = hash(word);

    //Check if linked list exists
    if (counter[index] == 0)
    {
        return false;
    }

    //Index into table
    node *cursor = table[index];

    //Check first element of linked list;
    if (strcasecmp(word, cursor->word) == 0)
    {
        return true;
    }

    //Check all other elements of linked list
    do
    {
        cursor = cursor->next;
        if (strcasecmp(word, cursor->word) == 0)
        {
            return true;
        }
    }
    while (cursor->next != NULL);
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int index = 0;
    int length = strlen(word);
    char temp;
    for (int i = 0; i < length; i++)
    {
        temp = toupper(word[i]);
        index += temp;
    }

    //printf("Index: %i\n", index);
    return (index % N);
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //Create and initialize temp node and counters
    node *temp = malloc(sizeof(node));
    if (!temp)
    {
        printf("insufficient Memory\n");
        return false;
    }
    for (int i = 0; i < N + 1; i++)
    {
        counter[i] = 0;
    }

    temp->next = NULL;

    //Open dictionary and check if success
    FILE *dict = fopen(dictionary, "r");
    if (!dict)
    {
        printf("Invalid File\n");
        return false;
    }

    //Read all words from dictionary one at a time
    while (fscanf(dict, "%s", temp->word) != EOF)
    {
        //Create and initialize new node
        node *n = malloc(sizeof(node));
        if (!n)
        {
            printf("insufficient Memory\n");
            return false;
        }
        n->next = NULL;

        //Copy word to new node
        strcpy(n->word, temp->word);

        //Index word
        int index = hash(n->word);

        //If first word of list: point to word
        if (counter[index] == 0)
        {
            table[index] = n;
            counter[index]++;
        }

        //If nth word of list: Set as first member of list and point to other members
        else if (counter[index] >= 1)
        {
            n->next = table[index];
            table[index] = n;
            counter[index]++;
        }

    }
    free(temp);
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int sum = 0;
    for (int i = 0; i < N + 1; i++)
    {
        sum += counter[i];
    }
    return sum;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *cursor;
    node *temp;
    for (int i = 0; i < N + 1; i++)
    {
        //Set cursor to table[i] if not empty
        if (counter[i] == 0)
        {
            continue;
        }
        cursor = table[i];

        //Traverse linked list
        while (true)
        {
            //Set temp to nth element
            temp = cursor;

            //Check if (n+1)th element exists
            if (cursor->next != NULL)
            {
                //Set cursor to (n+1)th element
                cursor = cursor->next;

                //Free nth element
                free(temp);
            }
            else
            {
                //Free last element of linked list in table[i]
                free(cursor);

                //Move to linked list at table[i+1]
                break;
            }
        }
    }
    return true;
}