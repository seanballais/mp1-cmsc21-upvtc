#include "file_access.h"

void
readDataFromFile(FILE *fp, struct node *head)
{
    if (fp != NULL) { // Close the file if it has not been closed yet
        fclose(fp);
    }

    fp = fopen("data.txt", "r");
    if (fp == NULL) {
        return;
    } else {
        char line[897];
        while (fgets(line, sizeof(line), fp)) { // Read the line
            // Tokenize the string now and place the info in an array
            char *token = strtok(line, "|");
            char info[25][256];
            int index = 0;
            while (token != NULL) {
                strcpy(info[index], token);

                token = strtok(NULL, "|");
                index++;
            }

            addNodeFromArray(head, info);
        }

        fclose(fp);
        fp = NULL;
    }
}

void
saveDataToFile(FILE *fp, struct node *head)
{
    if (fp != NULL) { // Close the file if it has not been closed yet
        fclose(fp);
    }

    fp = fopen("data.txt", "w");
    if (fp == NULL) {
        return;
    } else {
        struct node *current = head;
        while (current != NULL) {
            if (current != NULL && strcmp(current->val.studentNumber, "") != 0) {
                fprintf(fp, "%s|%s|%s|%s|%s%s|%s|%s|%s|%s%s|%s|%s|%s|%s%s|%s|%s|%s|%s%s|%s|%s|%s|%s\n",
                        current->val.name,
                        current->val.age,
                        current->val.course,
                        current->val.year,
                        current->val.studentNumber,
                        current->val.subjects[0][0],
                        current->val.subjects[0][1],
                        current->val.subjects[1][0],
                        current->val.subjects[1][1],
                        current->val.subjects[2][0],
                        current->val.subjects[2][1],
                        current->val.subjects[3][0],
                        current->val.subjects[3][1],
                        current->val.subjects[4][0],
                        current->val.subjects[4][1],
                        current->val.subjects[5][0],
                        current->val.subjects[5][1],
                        current->val.subjects[6][0],
                        current->val.subjects[6][1],
                        current->val.subjects[7][0],
                        current->val.subjects[7][1],
                        current->val.subjects[8][0],
                        current->val.subjects[8][1],
                        current->val.subjects[9][0],
                        current->val.subjects[9][1]
                        );
            }

            current = current->next;
        }
    }

    fclose(fp);
    fp = NULL;
}
