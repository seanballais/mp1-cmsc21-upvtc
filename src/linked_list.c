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

    // Time to convert the grade string to a double we can process next time.
    sscanf(str[5], "%lf", &current->next->val.grade);

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
            printf("Update grade or student information? 1 for grade, 2 for information.\n");
            printf("Input: ");
            int opt = GetInt();
            if (opt == 2) {
                getInput(&current->next->val);
                break;
            } else if (opt == 1) {
                printf("Enter new student grade: ");
                current->next->val.grade = GetDouble();
                break;
            } else {
                printf("Invalid input.\n");
                exit(0);
            }

            printf("Updated...\n");
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
