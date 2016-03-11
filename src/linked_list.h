#ifndef LINKED_LIST_H
#define LINKED_LIST_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    #include "gradebook_info.h"
    #include "gradebook_funcs.h"

    struct node {
        profile val;
        struct node *next;
    };

    void addNode(struct node *head);
    void addNodeFromArray(struct node *head, char str[][256]);
    void deleteNode(struct node *head, char studentNumber[]);
    void updateNode(struct node *head, char studentNumber[]);
    void displayNodes(struct node *head);
    void freeList(struct node *head);
    void cleanNode(struct node *head);

#endif
