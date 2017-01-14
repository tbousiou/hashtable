#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED
// Υλοποίηση απλής συνδεδεμένής λίστας
// Η κεαφαλή είναι ένας dummy node, και το πρώτο στοιχείο της λίστας βρίσκεται
// στο head->next

typedef struct node
{
    char *word;
    int count;
    int score;
    struct node *next;
} nodeT;

int addNode(nodeT *head, char *word, int score);

nodeT *lookupNode(nodeT *head, char *word);

int addUpdateNode(nodeT *head, char *word, int score);

void printList(nodeT *head);

void freeList(nodeT *head);

nodeT* removeNode(nodeT *head, char *word);

double findMax(double a, double b);

nodeT findMaxNode(nodeT a, nodeT b);

nodeT *findMaxNodeP(nodeT *a, nodeT *b);

nodeT *searchNodeInListWithBestScoreRecursive(nodeT *head);


#endif // LIST_H_INCLUDED
