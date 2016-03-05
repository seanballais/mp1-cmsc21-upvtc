#include <stdio.h>
#include <stdlib.h>

#include "slambook_info.h"
#include "linked_list.h"
#include "slambook_funcs.h"
#include "file_access.h"

int
main(int argc, char **argv)
{
    char throwaway = 'a';
    struct node *head = malloc(sizeof(struct node));
    head->next = NULL;

    FILE *fp = NULL;
    readDataFromFile(fp, head);

    printf("GRADEBOOK!\n");
    printf("Choose role\n");
    printf("    1) ADMIN\n");
    printf("    2) TEACHER\n");
    printf("    3) STUDENT\n");
    printf("Input: ");

    int role = 0;
    scanf("%d", &role);
    scanf("%c", &throwaway);
    if (role < 1 || role > 4) {
        printf("Invalid input.\n");
        return 0;
    }

    // Menu
    int opt = 0;
    while (1) {
        printMenu(role);
        scanf("%d", &opt);
        scanf("%c", &throwaway);
        if ((role == ADMIN && (opt < 1 || opt > 5)) ||
            (role == TEACHER && (opt < 1 || opt > 3)) ||
            (role == STUDENT && (opt < 1 || opt > 2))) {
            printf("Invalid input.\n");
            return 0;
        }

        char studentNumber[10];
        switch (role) {
            case ADMIN:
                if (opt == 2 || opt == 3) {
                    displayNodes(head);
                    printf("Enter student number: ");
                    fgets(studentNumber, sizeof(studentNumber), stdin);
                    _removeNewline(studentNumber);
                }

                if (opt == 1) {
                    addNode(head);
                    saveDataToFile(fp, head);
                } else if (opt == 2) {
                    updateNode(head, studentNumber);
                    saveDataToFile(fp, head);
                } else if (opt == 3) {
                    deleteNode(head, studentNumber);
                    saveDataToFile(fp, head);
                } else if (opt == 4) {
                    displayNodes(head);
                } else if (opt == 5) {
                    freeList(head);
                    return 0;
                }

                break;
            case TEACHER:
                if (opt == 1) {
                    addNode(head);
                    saveDataToFile(fp, head);
                } else if (opt == 2) {
                    displayNodes(head);
                    printf("Enter student number: ");
                    fgets(studentNumber, sizeof(studentNumber), stdin);
                    _removeNewline(studentNumber);
                    saveDataToFile(fp, head);
                    updateNode(head, studentNumber);
                } else if (opt == 3) {
                    displayNodes(head);
                } else if (opt == 4) {
                    freeList(head);
                    return 0;
                }

                break;
            case STUDENT:
                if (opt == 1) {
                    displayNodes(head);
                } else if (opt == 2) {
                    freeList(head);
                    return 0;
                }

                break;
        }
    }

    return 0;
}
