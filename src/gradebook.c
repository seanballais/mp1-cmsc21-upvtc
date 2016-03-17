#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

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
            system("clear");
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

        system("clear");

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
                system("clear");
                if (opt == 2 || opt == 3) {
                    displayNodes(head);
                    printf("Enter student number: ");
                    strcpy(studentNumber, GetString());
                }

                if (opt == 1) {
                    printf("Options\n");
                    printf("    1) Add Student\n");
                    printf("    2) Add Subjects\n");
                    printf("    3) Add Grade Range\n");
                    printf("Input: ");

                    int addOpt = GetInt();
                    if (addOpt == 1) {
                        addNode(head);
                        saveDataToFile(fp, head);
                    } else if (addOpt == 2) {
                        FILE *f = fopen("subjects.txt", "w");
                        fclose(f);
                        FILE *fp = fopen("subjects.txt", "a");
                        printf("Number of subjects to add: ");
                        int numSubjects = GetInt();
                        char subjectCriteria[numSubjects][5][2][20];
                        for (int h = 0; h < numSubjects; h++) {
                            for (int i = 0; i < 5; i++) {
                                for (int j = 0; j < 2; j++) {
                                    strcpy(subjectCriteria[h][i][j], "None");
                                }
                            }
                        }

                        for (int n = 0; n < numSubjects; n++) {
                            char subjectName[15];
                            printf("Subject: ");
                            strcpy(subjectName, GetString());

                            // Add the criteria
                            for (int i = 0; i < 5; i++) {
                                printf("Criteria Name: ");
                                strcpy(subjectCriteria[n][i][0], GetString());

                                printf("Percentage (1 - 100): ");
                                strcpy(subjectCriteria[n][i][1], GetString());

                                printf("Add another criteria? (1 for yes. 2 for no) ");
                                int criteriaOpt = GetInt();
                                if (criteriaOpt == 2) {
                                    break;
                                }
                            }

                            // Saving the stuff in the criteria
                            fprintf(fp,
                                    "%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s\n",
                                    subjectName,
                                    subjectCriteria[n][0][0],
                                    subjectCriteria[n][0][1],
                                    subjectCriteria[n][1][0],
                                    subjectCriteria[n][1][1],
                                    subjectCriteria[n][2][0],
                                    subjectCriteria[n][2][1],
                                    subjectCriteria[n][3][0],
                                    subjectCriteria[n][3][1],
                                    subjectCriteria[n][4][0],
                                    subjectCriteria[n][4][1]
                                );
                        }

                        fclose(fp);
                    } else if (addOpt == 3) {
                        FILE *fp = fopen("graderange.txt", "w");

                        printf("Number of subjects to add a range: ");
                        int numSubjects = GetInt();

                        for (int i = 0; i < numSubjects; i++) {
                            printf("Subject name: ");
                            char subjectName[10];
                            strcpy(subjectName, GetString());
                            char range[10][4];
                            double grades[10] = {
                                1.0,
                                1.25,
                                1.5,
                                1.75,
                                2.0,
                                2.25,
                                2.5,
                                2.75,
                                3.0,
                                4.0
                            };
                            for (int ctr = 0; ctr < 10; ctr++) {
                                printf("Minimum grade to get %.2lf: ", grades[ctr]);
                                strcpy(range[ctr], GetString());
                            }

                            fprintf(fp,
                                "%s|%s|%s|%s|%s|%s|%s|%s|%s|%s|%s\n",
                                subjectName,
                                range[0],
                                range[1],
                                range[2],
                                range[3],
                                range[4],
                                range[5],
                                range[6],
                                range[7],
                                range[8],
                                range[9]);

                            printf("Press any key to continue...");
                            getchar();
                        }

                        fclose(fp);
                    } else {
                        return 0;
                    }
                } else if (opt == 2) {
                    updateNode(head, studentNumber, ADMIN);
                    saveDataToFile(fp, head);
                } else if (opt == 3) {
                    deleteNode(head, studentNumber);
                    saveDataToFile(fp, head);
                } else if (opt == 4) {
                    displayNodes(head);
                    printf("Press any key to continue...");
                    getchar();
                } else if (opt == 5) {
                    opt = -1;
                }

                break;
            case TEACHER:
                system("clear");
                if (opt == 1) {
                    displayNodes(head);

                    printf("Enter student number: ");
                    strcpy(studentNumber, GetString());

                    char subjectName[10];
                    printf("Enter subject name: ");
                    strcpy(subjectName, GetString());

                    // Loop through the criteria of the subject
                    FILE *fp = fopen("subjects.txt", "r");
                    char line[897];
                    double grade = 0.00;
                    int startIndex = 0;
                    while (fgets(line, sizeof(line), fp)) { // Read the line
                        // Tokenize the string now and place the info in an array
                        char *token = strtok(line, "|");
                        char info[11][256];
                        int index = 0;
                        int skipFlag = 0;
                        while (token != NULL) {
                            strcpy(info[index], token);

                            if (index > 0 && strcmp(info[index], "None") == 0) {
                                break;
                            }

                            if (index == 0 && strcmp(subjectName, info[index]) == 0) { // Found the subject
                                skipFlag = 1;
                                startIndex = 1;
                                goto skipPoint;
                            }

                            if (startIndex % 2 != 0) { // Found the number
                                int percentage = 0;
                                sscanf(info[index], "%d", &percentage);

                                int criteriaGrade = GetInt();
                                grade += (double) criteriaGrade * ((double) percentage / 100);
                            } else {
                                printf("%s: ", info[index]);
                                index++;
                            }

                            skipPoint:

                            token = strtok(NULL, "|");
                            index++;
                            startIndex++;
                        }

                        if (skipFlag == 1) {
                            break;
                        }
                    }

                    printf("Grade: %.2lf\n", grade);

                    fclose(fp);

                    // Loop through criteria file again to look for the grade thingy
                    FILE *gradeFile = fopen("graderange.txt", "r");
                    char lineGrade[897];
                    double gradeRange[10] = {
                        1.0,
                        1.25,
                        1.5,
                        1.75,
                        2.0,
                        2.25,
                        2.5,
                        2.75,
                        3.0,
                        4.0
                    };

                    int gradeMin[10];

                    while (fgets(lineGrade, sizeof(lineGrade), fp)) { // Read the line
                        // Tokenize the string now and place the info in an array
                        char *token = strtok(lineGrade, "|");
                        char info[200][256];
                        int index = 0;
                        int skipFlag = 0;
                        while (token != NULL) {
                            strcpy(info[index], token);

                            if (index == 0 && strcmp(subjectName, info[index]) == 0) { // Found the subject
                                skipFlag = 1;
                            } else if (index > 0) {
                                printf("info: %s", info[index]);
                                sscanf(info[index], "%d", &gradeMin[index - 1]);
                                printf("gradeMin: %d", gradeMin[index - 1]);
                            }

                            token = strtok(NULL, "|");
                            index++;
                        }

                        if (skipFlag == 1) {
                            break;
                        }
                    }

                    for (int ctr = 0; ctr < 10; ctr++) {
                        if (grade >= gradeMin[ctr]) {
                            grade = gradeRange[ctr];
                            break;
                        }
                    }

                    if (grade > 5) {
                        grade = 5.0;
                    }

                    fclose(gradeFile);

                    struct node *current = head;
                    int index = 0;
                    while (current->next != NULL) {
                        if (strcmp(current->next->val.studentNumber, studentNumber) == 0 &&
                            strcmp(current->next->val.subjects[index][0], subjectName) == 0) {
                            sprintf(current->next->val.subjects[index][1], "%lf", grade);
                        }

                        current = current->next;
                        index++;
                    }

                    saveDataToFile(fp, head);
                } else if (opt == 2) {
                    displayNodes(head);

                    printf("Press any key to continue...");
                    getchar();
                } else if (opt == 3) {
                    opt = -1;
                }

                break;
            case STUDENT:
                system("clear");
                if (opt == 1) {
                    printf("Enter student number: ");
                    char* studentNumber = GetString();
                    displayNode(head, studentNumber);

                    printf("Press any key to continue...");
                    getchar();
                } else if (opt == 2) {
                    opt = -1;
                }

                break;
        }
    }

    system("clear");
    return 0;
}
