#include <stdio.h>
#include <stdlib.h>

#include "gradebook_info.h"
#include "gradebook_funcs.h"
#include "linked_list.h"
#include "file_access.h"

int
main(int argc, char **argv)
{
    struct node *head = malloc(sizeof(struct node));
    head->next = NULL;

    FILE *fp = NULL;
    readDataFromFile(fp, head);

    // Menu
    int opt = -1;
    int role = -1;
    while (1) {
        if (opt == -1) {
            printf("GRADEBOOK!\n");
            printf("Choose role\n");
            printf("    1) ADMIN\n");
            printf("    2) TEACHER\n");
            printf("    3) STUDENT\n");
            printf("    4) EXIT\n");
            printf("Input: ");

            role = GetInt();
            if (role < 1 || role > 5) {
                printf("Invalid input.\n");
                return 0;
            } else if (role == 4) {
                printf("Exiting...\n");
                freeList(head);
                return 0;
            }
        }

        printMenu(role);
        opt = GetInt();
        if ((role == ADMIN && (opt < 1 || opt > 5)) ||
            (role == TEACHER && (opt < 1 || opt > 4)) ||
            (role == STUDENT && (opt < 1 || opt > 2))) {
            printf("Invalid input.\n");
            return 0;
        }

        char studentNumber[12];
        switch (role) {
            case ADMIN:
                if (opt == 2 || opt == 3) {
                    displayNodes(head);
                    printf("Enter student number: ");
                    strcpy(studentNumber, GetString());
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
                    opt = -1;
                }

                break;
            case TEACHER:
                if (opt == 1) {
                    addNode(head);
                    saveDataToFile(fp, head);
                } else if (opt == 2) {
                    displayNodes(head);

                    printf("Enter student number: ");
                    strcpy(studentNumber, GetString());

                    updateNode(head, studentNumber);
                    saveDataToFile(fp, head);
                } else if (opt == 3) {
                    displayNodes(head);
                } else if (opt == 4) {
                    opt = -1;
                }

                break;
            case STUDENT:
                if (opt == 1) {
                    printf("Enter student number: ");
                    char* studentNumber = GetString();
                    displayNode(head, studentNumber);
                } else if (opt == 2) {
                    opt = -1;
                }

                break;
        }
    }

    return 0;
}
