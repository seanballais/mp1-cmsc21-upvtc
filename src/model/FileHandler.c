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

    string fileLines = NULL;
    string line = NULL;
    bool numberFound = false;
    while (fgets(line, 256, fp) != NULL) {
        // Tokenize the string
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
            string lineInfo = NULL;
            string token = strtok(line, "|");
            int tokenNumber = 0;
            while (token != NULL) {
                // Continue looping until the token points to the subjects
                if (tokenNumber == index) {
                    if (mode == 'a') {
                        strcat(token, " ");
                        strcat(token, newVal);
                        strcat(token, ",");
                    } else if (mode == 'r') {
                        strcpy(token, newVal);
                    }
                } else if (tokenNumber == 1 && mode == 'a') {
                    strcpy(lineInfo, token);

                    tokenNumber++;
                    token = strtok(NULL, "|");

                    continue;
                }

                strcat(lineInfo, "|");
                strcat(lineInfo, token);

                tokenNumber++;
                token = strtok(NULL, "|");
            }

            strcat(lineInfo, "\n");

            // Append the line to the string array
            strcat(fileLines, lineInfo);
        } else {
            strcat(fileLines, line);
        }
    }

    fclose(fp);

    fp = FileUtil_openFile("StudentInfo.txt", "w");
    fprintf(fp, "%s", fileLines);

    fclose(fp);
}

void
FileUtil_getStudentInfoProperty(const int index,
                                const string studentNumber)
{
    /*
     * Get a student info property.
     */

     FILE *fp = FileUtil_openFile("StudentInfo.txt", "r");

     string fileLines = NULL;
     string line = NULL;
     bool numberFound = false;
     while (fgets(line, 256, fp) != NULL) {
         // Tokenize the string
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
             string token = strtok(line, "|");
             int tokenNumber = 0;
             while (token != NULL) {
                 // Continue looping until the token points to the subjects
                 if (tokenNumber == index) {
                     return token;
                 }

                 tokenNumber++;
                 token = strtok(NULL, "|");
             }
         }
     }

     fclose(fp);
}
