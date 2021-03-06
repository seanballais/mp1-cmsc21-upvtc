/*
 * StudentModel.h
 *
 * Handles data manipulation with respect to the subject.
 *
 */

#include "SubjectModel.h"

void
SubjectModel_addSubject(string subjectName,
                        string subjectCriteria,
                        string subjectRange)
{
    /*
     * Add a subject to the file.
     */

     FILE *fp = FileUtil_openFile("SubjectInfo.txt", "a");

     fprintf(
         fp,
         "%s|%s|%s\n",
         subjectName,
         subjectCriteria,
         subjectRange
     );

     fclose(fp);

     return;
}

void
SubjectModel_modifySubject(string subjectName,
                           string subjectCriteria,
                           string subjectRange)
{
    /*
     * Modify a subject from the list.
     */

    FILE *fp = FileUtil_openFile("SubjectInfo.txt", "r");

    char fileLines[256];
    strcpy(fileLines, "");
    char line[256];
    strcpy(line, "");
    while (fgets(line, 256, fp) != NULL) {
        char tmpLine[256];
        strcpy(tmpLine, line);
        // Tokenize the string
        string token = strtok(tmpLine, "|");
        int tokenNumber = 0;
        while (token != NULL) {
            // Continue looping until the token points to the student number
            if (tokenNumber == 0) { // Located the subject
                if (strcmp(subjectName, token) == 0) { // Replace the line
                    sprintf(
                        line,
                        "%s|%s|%s\n",
                        subjectName,
                        subjectCriteria,
                        subjectRange
                    );

                    break;
                }
            }

            tokenNumber++;
            token = strtok(NULL, "|");
        }

        strcat(fileLines, line);
    }

    fclose(fp);

    fp = FileUtil_openFile("SubjectInfo.txt", "w");
    fprintf(fp, "%s", fileLines);

    fclose(fp);

    return;
}

void
SubjectModel_removeSubject(string subjectName)
{
    /*
     * Remove a subject from the list.
     */

    FILE *fp = FileUtil_openFile("SubjectInfo.txt", "r");

    char fileLines[256];
    strcpy(fileLines, "");
    char line[256];
    strcpy(line, "");
    bool subjectFound = false;
    while (fgets(line, 256, fp) != NULL) {
        char tmpLine[256];
        strcpy(tmpLine, line);
        subjectFound = false;
        // Tokenize the string
        string token = strtok(line, "|");
        int tokenNumber = 0;
        while (token != NULL) {
            // Continue looping until the token points to the subject name
            if (tokenNumber == 0) { // Located the subject name
                if (strcmp(subjectName, token) == 0) {
                    subjectFound = true;
                    break;
                }
            }

            tokenNumber++;
            token = strtok(NULL, "|");

        }

        if (!subjectFound) {
            strcat(fileLines, tmpLine);
        }
    }

    fclose(fp);

    fp = FileUtil_openFile("SubjectInfo.txt", "w");
    fprintf(fp, "%s", fileLines);

    fclose(fp);

    return;
}

string
SubjectModel_getSubjectCriteria(string subjectName)
{
    /*
     * Get a subject criteria.
     */

    FILE *fp = FileUtil_openFile("SubjectInfo.txt", "r");

    char fileLines[256];
    strcpy(fileLines, "");
    char line[256];
    strcpy(line, "");
    bool subjectFound = false;
    while (fgets(line, 256, fp) != NULL) {
        // Tokenize the string
        char tmpLine[256];
        strcpy(tmpLine, line);
        string token = strtok(line, "|");
        int tokenNumber = 0;
        while (token != NULL) {
            // Continue looping until the token points to the student number
            if (tokenNumber == 0) { // Located the student number
                if (strcmp(subjectName, token) == 0) {
                    subjectFound = true;
                    break;
                }
            }

            tokenNumber++;
            token = strtok(NULL, "|");
        }

        if (subjectFound) {
            // Let's tokenize again
            string token = strtok(tmpLine, "|");
            int tokenNumber = 0;
            while (token != NULL) {
                // Continue looping until the token points to the subjects
                if (tokenNumber == 1) {
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

string
SubjectModel_getSubjectRange(string subjectName)
{
    /*
     * Get a subject range.
     */

    FILE *fp = FileUtil_openFile("SubjectInfo.txt", "r");

    char fileLines[256];
    strcpy(fileLines, "");
    char line[256];
    strcpy(line, "");
    bool subjectFound = false;
    while (fgets(line, 256, fp) != NULL) {
        // Tokenize the string
        char tmpLine[256];
        strcpy(tmpLine, line);
        string token = strtok(line, "|");
        int tokenNumber = 0;
        while (token != NULL) {
            // Continue looping until the token points to the student number
            if (tokenNumber == 0) { // Located the student number
                if (strcmp(subjectName, token) == 0) {
                    subjectFound = true;
                    break;
                }
            }

            tokenNumber++;
            token = strtok(NULL, "|");
        }

        if (subjectFound) {
            // Let's tokenize again
            string token = strtok(tmpLine, "|");
            int tokenNumber = 0;
            while (token != NULL) {
                // Continue looping until the token points to the subjects
                if (tokenNumber == 2) {
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

void
SubjectModel_listSubjects()
{
    /*
     * Get a subject range.
     */

    printf("GRADINGBOOK AVAILABLE SUBJECTS\n");

    FILE *fp = FileUtil_openFile("SubjectInfo.txt", "r");

    char fileLines[256];
    strcpy(fileLines, "");
    char line[256];
    strcpy(line, "");
    while (fgets(line, 256, fp) != NULL) {
        // Tokenize the string
        string token = strtok(line, "|");
        int tokenNumber = 0;
        while (token != NULL) {
            // Continue looping until the token points to the student number
            if (tokenNumber == 0) { // Located the subject
                printf(" - %s\n", token);
                break;
            }

            tokenNumber++;
            token = strtok(NULL, "|");
        }
    }

    fclose(fp);
}

bool
SubjectModel_subjectPresent(string subjectName)
{
    /*
     * Check if a subject is present.
     */

    FILE *fp = FileUtil_openFile("SubjectInfo.txt", "r");

    char fileLines[256];
    strcpy(fileLines, "");
    char line[256];
    strcpy(line, "");
    while (fgets(line, 256, fp) != NULL) {
        // Tokenize the string
        string token = strtok(line, "|");
        int tokenNumber = 0;
        while (token != NULL) {
            // Continue looping until the token points to the student number
            if (strcmp(token, subjectName) == 0) { // Located the subject
                return true;
            }

            tokenNumber++;
            token = strtok(NULL, "|");
        }
    }

    fclose(fp);

    return false;
}
