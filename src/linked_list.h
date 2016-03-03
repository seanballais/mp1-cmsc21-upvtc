#ifndef LINKED_LIST_H
#define LINKED_LIST_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "slambook_info.h"
    #include "slambook_funcs.h"

    struct node {
        profile val;
        struct node *next;
    };

    void addNode(struct node *head, int *currIndex);
    void addNodeFromArray(struct node *head, char str[][256], int *currIndex);
    void deleteNode(struct node *head, int index);
    void updateNode(struct node *head, int index);
    void displayNodes(struct node *head);
    void freeList(struct node *head);

#endif
