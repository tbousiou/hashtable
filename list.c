#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"


// Πρσθέτει ένα κόμβο στην αρχή της λίστας
int addNode(nodeT *head, char *word, int score)
{

    //create new node
    nodeT *newNode = (nodeT*)malloc(sizeof(nodeT));

    if(newNode == NULL)
    {
        fprintf(stderr, "Unable to allocate memory for new node\n");
        exit(-1);
    }

    newNode->word = word;
    newNode->score = score;
    newNode->count = 1;
    newNode->next = NULL;  // Change 1

    //check for first insertion
    if(head->next == NULL)
    {
        head->next = newNode;
    }

    else // put node in beginning of list
    {
        newNode->next = head->next;
        head->next = newNode;

    }
    return 0;
}


// Αναζητά ένα κόμβο στη λίστα βάση της λέξης
// Επιστρέφει τον δείκτη στον κόμβο αν βρεθεί ή
// ή NULL αν δε βρεθεί
nodeT *lookupNode(nodeT *head, char *word)
{
    nodeT *current = head;
    while (current->next != NULL)
    {
        if (strcmp(word, current->next->word) == 0)
            return current->next;
        current = current->next;
    }
    return NULL;
}



// Eισάγει τη λέξη στη λίστα αν αυτή δεν υπάρχει ήδη
// ή ανανεώνει τις εμφανίσεις και το σκορ της, αν ήδη υπάρχει.
// Επιστρέφει 1 αν προσθέσει λέξη, 0 αν ενημερώσει λέξη
int addUpdateNode(nodeT *head, char *word, int score)
{
    nodeT *tempNode;
    tempNode = lookupNode(head, word);
    if(tempNode==NULL)
    {
        addNode(head, word, score);
        return 1;
    }
    else
    {
        tempNode->score += score;
        tempNode->count++;
        return 0;

    }
}


// Εκτυπώνει τα στοιχεία της λίστας
void printList(nodeT *head)
{
    nodeT *current = head->next;
    while (current != NULL)
    {
        printf(" [ \"%s\" %d %.2f ]", current->word, current->count, (double)current->score);

        current = current->next;
        // Εκτύπωσε το κόμμα όταν δεν είναι το τελευταίο στοιχείο
        if (current!=NULL)
        {
            printf(",");
        }
    }

}

// Καταστρέφει τη λίστα
void freeList(nodeT *head)
{
    nodeT *current = head->next;
    nodeT *next;

    while(current != NULL)
    {

        next = current->next;
        free(current);
        current = next;
    }
    free(head);


}

// Δεδομένης μιας λέξης, βρίσκει, αφαιρεί, κι επιστρέφει (χωρίς να καταστρέψει)
// τον κόμβο της λίστας που αντιστοιχεί σε αυτή τη λέξη, εφόσον υπάρχει.
nodeT* removeNode(nodeT *head, char *word)
{
    nodeT *current = head;
    nodeT *prev = NULL;
    while (current->next != NULL)
    {
        if (strcmp(word, current->next->word) == 0)
        {
            printf("remove node with %s", current->next->word);
            prev = current;
            current = current->next;
            break;
        }
        prev = current;
        current = current->next;
    }


    if (current != NULL)
    {
        if (prev == NULL)
        {
            /* παράκαμψη πρώτου κόμβου της λίστας */
            head = current->next;
        }
        else
        {
            /* παράκαμψη κόμβου με προηγούμενο κόμβο */
            prev->next = current->next;
        }


    }
    return current;

}

// Επιστρέφει τον μέγιστο μεταξύ δυο πραγματικών
double findMax(double a, double b)
{
    if (a>=b) return a;
    return b;

}

// Συγκρίνει δύο κόμβους με λέξεις και επιστρέφει αυτόν με το
// μεγαλύτερο μέσο σκορ λέξης
// Χρησιμοποίείται στην searchNodeInTableWithBestScoreRecursive του hashtable
nodeT findMaxNode(nodeT a, nodeT b)
{
    double av_score1 = (double) a.score / a.count;
    double av_score2 = (double) b.score / b.count;
    //nodeT emtpyNode;
    //emtpyNode.word = NULL;

    if (findMax(av_score1, av_score2) == av_score1) return a;
    return b;

}

// Ίδιο με το προηγούμενο αλλά με pointers
// Συγκρίνει δύο κόμβους με λέξεις και επιστρέφει τον ΔΕΙΚΤΗ αυτόν με το
// μεγαλύτερο μέσο σκορ λέξης
nodeT *findMaxNodeP(nodeT *a, nodeT *b)
{
    double av_score1 = (double) a->score / a->count;
    double av_score2 = (double) b->score / b->count;
    //nodeT emtpyNode;
    //emtpyNode.word = NULL;

    if (findMax(av_score1, av_score2) == av_score1) return a;
    return b;

}


// Βρίσκει αναδρμικά σε μια λίστα τον κόμβο με το μεγαλύτερο μέσο σκορ
// Επιστρέφει τον δείκτη στον κόμβο
nodeT *searchNodeInListWithBestScoreRecursive(nodeT *head)
{
    nodeT *current = head;
    //double current_score, search_score;
    if (current->next==NULL)   // ΑΔΕΙΑ ΛΙΣΤΑ
    {
        return NULL;
    }
    else if (current->next->next==NULL)     // ΛΙΣΤΑ ΜΕ ΕΝΑ ΣΤΟΙΧΕΙΟ
    {
        return current->next;
    }
    else
    {
        findMaxNodeP(current->next, searchNodeInListWithBestScoreRecursive(current->next));

    }
}
