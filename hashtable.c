#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

// Δημιουργεί τον hashtable
hashT *createHashTable(int size)
{
    hashT *new_table;

    if (size<1) return NULL; /* invalid size for table */

    /* Attempt to allocate memory for the table structure */
    if ((new_table = malloc(sizeof(nodeT))) == NULL)
    {
        return NULL;
    }

    /* Attempt to allocate memory for the table itself */
    if ((new_table->table = malloc(sizeof(nodeT *) * size)) == NULL)
    {
        return NULL;
    }

    /* Initialize the elements of the table */
    int i;
    for(i=0; i<size; i++)
    {
        //new_table->table[i] = NULL;
        new_table->table[i] = malloc(sizeof(nodeT));
        new_table->table[i]->next = NULL;
    }


    /* Set the table's size */
    new_table->size = size;
    new_table->num_entries = 0;

    return new_table;
}


unsigned long hash(hashT *hashtable, char *str)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % hashtable->size;
}

//Αναζητά στον hashtable για μια λέξη str. Αν βρεθεί ή λέξη επιστρέφει
//το σοιχείο της λίστας, αλλιώς NULL
nodeT *lookupNodeInTable(hashT *hashtable, char *word)
{
    nodeT *list;
    nodeT *listNode;

    unsigned int hashval = hash(hashtable, word);

    list = hashtable->table[hashval];
    listNode = lookupNode(list, word);

    return listNode;
}



// Πρσοσθέτει λέξη στον hashtable
void addNodeInTable(hashT *hashtable, char *word, int score)
{
    nodeT *list;

    unsigned int hashval = hash(hashtable, word);

    list = hashtable->table[hashval];

    hashtable->num_entries += addUpdateNode(list, word, score);

}

//Αποδεσμέυει τη μνήμη του πίνακα και όλων των στοιχειων των λιστών
void freeTable(hashT *hashtable)
{
    int i;
    nodeT *list;

    if (hashtable==NULL) return;

    /* Free the memory for every item in the table, including the
     * strings themselves.
     */
    for(i=0; i<hashtable->size; i++)
    {
        list = hashtable->table[i];
        freeList(list);

    }

    /* Free the table itself */
    free(hashtable->table);
    free(hashtable);
}

// Εκτυπώνει τα στοιχεία του hashtable σύμφωνα με τις οδηγίες
void printHashTable(hashT *hashtable)
{

    nodeT *list;
    int i;

    for(i=0; i<hashtable->size; i++)
    {
        list = hashtable->table[i];
        if(list->next!=NULL)
        {
            printf("%4d:", i);
            printList(list);
        }
        else
        {
            continue;
        }

        printf("\n");
    }

}

// Βρίσκει αναδρομικά σε έναν πίνακα με κόμβους λέξεων τη λέξη
// με το μεγαλύτερο μέσο σκορ και επιστρέφει τον κόμβο
nodeT searchNodeInTableWithBestScoreRecursive(nodeT* scoresTable, int size)
{
    if (size == 1)
    {
        return scoresTable[0];
    }
    else
    {
        return findMaxNode(scoresTable[0], searchNodeInTableWithBestScoreRecursive(scoresTable+1, size-1));
    }
}
