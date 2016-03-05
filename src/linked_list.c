#include "linked_list.h"
#include <string.h>

void
addNode(struct node *head)
{
    struct node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = malloc(sizeof(struct node));
    getInput(&current->next->val);
    current->next->next = NULL;
}

void
addNodeFromArray(struct node *head, char str[][256])
{
    struct node *current = head;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = malloc(sizeof(struct node));
    strcpy(current->next->val.name, str[0]);
    strcpy(current->next->val.nickname, str[1]);
    strcpy(current->next->val.age, str[2]);
    strcpy(current->next->val.course, str[3]);
    strcpy(current->next->val.year, str[4]);
    strcpy(current->next->val.studentNumber, str[5]);
    current->next->next = NULL;
}

void
deleteNode(struct node *head, char studentNumber[])
{
    struct node *current = head;
    while (current->next != NULL) {
        if (strcmp(current->next->val.studentNumber, studentNumber) == 0) {
            printf("Deleted student number %s...\n", current->next->val.studentNumber);
            free(current->next);
            current->next = current->next->next;
            break;
        }

        current = current->next;
    }
}

void
updateNode(struct node *head, char studentNumber[])
{
    struct node *current = head;
    while (current->next != NULL) {
        if (strcmp(current->next->val.studentNumber, studentNumber) == 0) {
            getInput(&current->next->val);
            break;
        }

        current = current->next;
    }
}

void
displayNodes(struct node *head)
{
    struct node *current = head;
    while (current != NULL) {
        if (current != NULL && strcmp(current->val.studentNumber, "") != 0) {
            printEntry(current->val);
        }

        current = current->next;
    }
}

void
freeList(struct node *head)
{
    struct node *current = head;
    struct node *tmpNode;
    while (current != NULL) {
        tmpNode = current;
        current = current->next;
        free(tmpNode);
    }
    head = NULL;
}
