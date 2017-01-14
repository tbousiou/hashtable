
#ifndef HASHTABLE_H_INCLUDED
#define HASHTABLE_H_INCLUDED
#include "list.h"

typedef struct
{
    int size;       // Το μέγεθος του hastable
    int num_entries; // To πλήθος των στοιχείων
    nodeT **table; // Η διεύθυνση του πίνακα
} hashT;


hashT *createHashTable(int size);

unsigned long hash(hashT *hashtable, char *str);

nodeT *lookupNodeInTable(hashT *hashtable, char *word);

void addNodeInTable(hashT *hashtable, char *word, int score);

void freeTable(hashT *hashtable);

void printHashTable(hashT *hashtable);

nodeT searchNodeInTableWithBestScoreRecursive(nodeT* scoresTable, int size);

#endif // HASHTABLE_H_INCLUDED
