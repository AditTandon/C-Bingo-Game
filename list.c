// k2kanhai, Kanhai, Kerry, 501063750, section 4
// a4tandon, Tandon, Adit 500527157, section 4

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

// Initiates the callList structure and assigns appropriate values
void init(List *callList) {
    callList->length = 0;
    callList->last = NULL;
    callList->beginning = NULL;
}

void add(List *callList, int num) {
    node *newNode;
    node *temp;

    // Allocates space for new node
    newNode = (node *) malloc(sizeof(node));

    // Assigns new value to the value field in the new node
    newNode->value = num;

    // If there is already a value in the list, the last will point to the newest node added
    if (callList->last != NULL) {
        callList->last->next = newNode;
    }
    else {
        // When first node is added to the list, beginning is always set to that node
        callList->beginning = newNode;
    }
    
    // Adds new node to the list
    callList->last = newNode;
    callList->length++;
}

int check(List *callList, int num) {
    int check;
    node *p = callList->beginning;

    // Goes through all nodes in the list structure
    while (p != NULL) {
        check = p->value;
        // Checks if number passed to the function is the same as value in the existing node
        if (num == check) {
            return 1;
        }

        // Goes to next node
        p = p->next;
    }

    return 0;
}

void print(List *callList) {
    int number;
    int i;
    char letter;
    node *p = callList->beginning;

    while (p != NULL) {
        number = p->value;
        // Gets the appropriate letter from the random number that is passed into the function
        if (number <= 15 && number >0 ) {
            letter = 'L';
        }
        
        if (number <= 30 && number >= 16) {
            letter = 'I';
        }

        if (number <=45 && number >=31 ) {
            letter = 'N';
        }

        if ( number <= 60 && number >=46)   {
            letter = 'U';
        }

        if (number <= 75 && number >= 61) {
            letter = 'X';
        }

        p->letter = letter;
        // Prints letter and number together for the callList
        printf("%c%d ", p->letter, p->value);
        p = p->next;
    }
}