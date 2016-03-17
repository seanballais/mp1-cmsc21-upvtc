#include "linked_list.h"
#include "gradebook_funcs.h"

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
    strcpy(current->next->val.age, str[1]);
    strcpy(current->next->val.course, str[2]);
    strcpy(current->next->val.year, str[3]);
    strcpy(current->next->val.studentNumber, str[4]);

    int gradePart = 0; // 0 for name, 1 for grade
    for (int subjCtr = 0; subjCtr < 25; subjCtr++) {
        if (subjCtr % 2 == 0) {
            gradePart = 0;
        } else {
            gradePart = 1;
        }
        strcpy(current->next->val.subjects[subjCtr][gradePart], str[subjCtr + 5]);
    }

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
updateNode(struct node *head, char studentNumber[], int privilege)
{
    struct node *current = head;
    while (current->next != NULL) {
        if (strcmp(current->next->val.studentNumber, studentNumber) == 0) {
            printf("Update student information.\n");
            getInput(&current->next->val);
            printf("Updated...\n");
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
        printf("Data: %s\n", current->val.subjects[1][0]);
        if (current != NULL && strcmp(current->val.studentNumber, "") != 0) {
            printEntry(current->val);
        }

        current = current->next;
    }
}

void
displayNode(struct node *head, char studentNumber[])
{
    struct node *current = head;
    while (current != NULL) {
        if (current != NULL && strcmp(current->val.studentNumber, studentNumber) == 0) {
            printf("---\n");
            printEntry(current->val);
            return;
        }

        current = current->next;
    }

    printf("Unknown student number. Exiting...\n");
    return;
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
