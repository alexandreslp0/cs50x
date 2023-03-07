// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
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

// global var to count loaded dict size
int dict_size = 0;

// prototypes
void append_node(node *first_node, node *to_append);
void linked_list_size(node *node);
bool check_linked_list(node *node, const char *word);
void unload_linked_list(node *node);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    unsigned int table_idx = hash(&word[0]);

    if (table[table_idx] != NULL)
    {
        return check_linked_list(table[table_idx], word);
    }
    else
    {
        return false;
    }
}

bool check_linked_list(node *node, const char *word)
{
    //printf("\n%s - %s\n", word, node->word);
    if (strcasecmp(node->word, word) == 0)
    {
        return true;
    }
    else if (node->next != NULL)
    {
        return check_linked_list(node->next, word);
    }
    else
    {
        return false;
    }
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
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return 1;
    }

    node *tmp = malloc(sizeof(node));
    if (tmp == NULL)
    {
        return 1;
    }
    tmp->next = NULL;

    char word[LENGTH + 2];

    while (fgets(word, LENGTH + 2, file))
    {
        word[strlen(word) - 1] = '\0';
        strcpy(tmp->word, word);
        unsigned int table_idx = hash(&tmp->word[0]);
        // check if is the first node in this "bucket"
        if (table[table_idx] == NULL)
        {
            table[table_idx] = tmp;
        }
        // if is not the first node, append
        else
        {
            append_node(table[table_idx], tmp);
        }
        // prepare for another word
        tmp = malloc(sizeof(node));
        if (tmp == NULL)
        {
            free(tmp);
            return 1;
        }
        tmp->next = NULL;
    }
    fclose(file);
    free(tmp);
    return true;
}

void append_node(node *first_node, node *to_append)
{
    if (first_node->next == NULL)
    {
        first_node->next = to_append;
    }
    else
    {
        append_node(first_node->next, to_append);
    }
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            linked_list_size(table[i]);
        }
    }
    return dict_size;
}

// recursively count dict size
void linked_list_size(node *node)
{
    if (node->next == NULL)
    {
        dict_size++;
        return;
    }
    else
    {
        dict_size++;
        linked_list_size(node->next);
    }
    return;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        if (table[i] != NULL)
        {
            unload_linked_list(table[i]);
        }
    }
    return true;
}

void unload_linked_list(node *node)
{
    if (node->next == NULL)
    {
        free(node);
        return;
    }
    else
    {
        unload_linked_list(node->next);
    }
    free(node);
    return;
}