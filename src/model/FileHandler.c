/*
 * FileUtil.h
 *
 * Abstracts file functions.
 *
 */

#include "FileHandler.h"

FILE*
FileUtil_openFile(const string filename,
                  const string mode)
{
    /*
     * Opens the file and handles any errors.
     */

    FILE *fp = fopen(filename, mode);
    if (fp == NULL) {
        printf("Error! File %s not found.\n", filename);
        exit(EXIT_FAILURE);
    }

    return fp;
}

void
FileUtil_modifyStudentInfoProperty(const int index,
                                   const string studentNumber,
                                   const string newVal,
                                   const char mode) // 'r' for replace, 'a' for append
{
    /*
     * Modify a student info property
     */

    // Locate the student number
    FILE *fp = FileUtil_openFile("StudentInfo.txt", "r");

    char fileLines[256];
    strcpy(fileLines, "");
    char line[256];
    strcpy(line, "");
    bool numberFound = false;
    bool skipIf = false;
    while (fgets(line, 256, fp) != NULL) {
        // Tokenize the string
        char tmpLine[256];
        strcpy(tmpLine, line);
        char numberLine[256];
        strcpy(numberLine, line);
        string token = strtok(tmpLine, "|");
        int tokenNumber = 0;
        while (token != NULL && !numberFound) {
            // Continue looping until the token points to the student number
            if (tokenNumber == 3) { // Located the student number
                if (strcmp(studentNumber, token) == 0) {
                    numberFound = true;
                    break;
                }
            } else {
                tokenNumber++;
                token = strtok(NULL, "|");
            }
        }

        if (numberFound && !skipIf) {
            // Let's tokenize again
            char lineInfo[256];
            strcpy(lineInfo, "");
            string token = strtok(numberLine, "|\n");
            int tokenNumber = 0;
            while (token != NULL) {
                // Continue looping until the token points to the subjects
                if (tokenNumber == index && mode == 'a') {
                    strcat(token, ", ");
                    strcat(token, newVal);
                } else if (tokenNumber == index && mode == 'r') {
                    strcpy(token, newVal);
                }

                strcat(lineInfo, token);
                strcat(lineInfo, "|");

                tokenNumber++;
                token = strtok(NULL, "|\n");
            }

            char *pos;
            if ((pos = strrchr(lineInfo, '|')) != NULL) {
                *pos = '\0';
            }

            strcat(lineInfo, "\n");

            // Append the line to the string array
            strcat(fileLines, lineInfo);

            skipIf = true;
        } else {
            strcat(fileLines, line);
        }
    }

    fclose(fp);

    fp = FileUtil_openFile("StudentInfo.txt", "w");
    fprintf(fp, "%s", fileLines);

    fclose(fp);
}

string
FileUtil_getStudentInfoProperty(const int index,
                                const string studentNumber)
{
    /*
     * Get a student info property.
     */

    FILE *fp = FileUtil_openFile("StudentInfo.txt", "r");

    char fileLines[256];
    strcpy(fileLines, "");
    char line[256];
    strcpy(line, "");
    bool numberFound = false;
    while (fgets(line, 256, fp) != NULL) {
        // Tokenize the string
        char tmpLine[256];
        strcpy(tmpLine, line);
        string token = strtok(line, "|");
        int tokenNumber = 0;
        while (token != NULL) {
            // Continue looping until the token points to the student number
            if (tokenNumber == 3) { // Located the student number
                if (strcmp(studentNumber, token) == 0) {
                    numberFound = true;
                    break;
                }
            } else {
                tokenNumber++;
                token = strtok(NULL, "|");
            }
        }

        if (numberFound) {
            // Let's tokenize again
            string token = strtok(tmpLine, "|");
            int tokenNumber = 0;
            while (token != NULL) {
                // Continue looping until the token points to the subjects
                if (tokenNumber == index) {
                    fclose(fp);
                    return token;
                }

                tokenNumber++;
                token = strtok(NULL, "|");
            }
        }
    }

    fclose(fp);
    return "None";
}
