// k2kanhai, Kanhai, Kerry, 501063750, section 4
// a4tandon, Tandon, Adit 500527157, section 4

#include <stdio.h>
#include <stdlib.h>

typedef struct Node node;

struct Node {
    int value;
    char letter;
    node *next;
};

typedef struct {
    int length;
    node *last;
    node *beginning;
} List;

void init(List *callList);
void add(List *callList, int num);
int check(List *callList, int num);
void print(List *callList);