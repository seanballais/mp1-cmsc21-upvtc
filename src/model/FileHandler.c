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
    while (fgets(line, 256, fp) != NULL) {
        // Tokenize the string
        char tmpLine[256];
        strcpy(tmpLine, line);

        char numberLine[256];
        strcpy(numberLine, line);

        int tokenNumber = 0;
        string token = strtok(tmpLine, "|");
        while (token != NULL) {
            // Continue looping until the token points to the student number
            if (tokenNumber == 3) { // Located the student number
                if (strcmp(studentNumber, token) == 0) { // Modify line
                    char lineInfo[256];
                    strcpy(lineInfo, "");

                    char tmpInfo[256];
                    strcpy(tmpInfo, "");

                    int tokenNumberIndex = 0;
                    string numberToken = strtok(numberLine, "|");
                    while (numberToken != NULL) {
                        char *newLinePos;
                        if ((newLinePos = strrchr(numberToken, '\n')) != NULL) {
                            *newLinePos = '\0';
                        }

                        // Continue looping until the token points to the subjects
                        if (tokenNumberIndex == index && mode == 'a') {
                            strcpy(tmpInfo, numberToken);
                            strcat(tmpInfo, ", ");
                            strcat(tmpInfo, newVal);

                            strcat(lineInfo, tmpInfo);
                            strcat(lineInfo, "|");
                        } else if (tokenNumberIndex == index && mode == 'r') {
                            strcpy(tmpInfo, newVal);

                            strcat(lineInfo, tmpInfo);
                            strcat(lineInfo, "|");
                        } else {
                            strcat(lineInfo, numberToken);
                            strcat(lineInfo, "|");
                        }

                        tokenNumberIndex++;
                        numberToken = strtok(NULL, "|");
                    }

                    char *pos;
                    if ((pos = strrchr(lineInfo, '|')) != NULL) {
                        *pos = '\0';
                    }

                    // Replace the line with the modified line
                    strcpy(line, lineInfo);
                    strcat(line, "\n");
                }
            }

            tokenNumber++;
            token = strtok(NULL, "|");
        }

        strcat(fileLines, line);
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
                    // Let's tokenize again
                    string subToken = strtok(tmpLine, "|");
                    int tokenNumber = 0;
                    while (subToken != NULL) {
                        // Continue looping until the token points to the subjects
                        if (tokenNumber == index) {
                            fclose(fp);
                            return subToken;
                        }

                        tokenNumber++;
                        subToken = strtok(NULL, "|");
                    }

                    break;
                }
            }

            tokenNumber++;
            token = strtok(NULL, "|");
        }
    }

    fclose(fp);
    return "None";
}
