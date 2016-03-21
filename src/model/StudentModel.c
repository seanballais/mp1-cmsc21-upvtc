/*
 * StudentModel.c
 *
 * Handles data manipulation with respect to the student data.
 *
 */

#include "StudentModel.h"

void
StudentModel_addStudent(string name,
                        string course,
                        int year,
                        string studentNumber,
                        string subjects,
                        string grades)
{
    /*
     * Append the student to the database.
     */

    FILE *fp = FileUtil_openFile("StudentInfo.txt", "a");

    fprintf(
        fp,
        "%s|%s|%d|%s|%s|%s\n",
        name,
        course,
        year,
        studentNumber,
        subjects,
        grades
    );

    fclose(fp);

    return;
}

void
StudentModel_addStudentSubject(string studentNumber,
                               string subject)
{
    /*
     * Add a subject to a student.
     */

    // Append to the subject list
    FileUtil_modifyStudentInfoProperty(4, studentNumber, subject, 'a');

    // Append to the subject grade list that can be mapped to the subject list
    FileUtil_modifyStudentInfoProperty(5, studentNumber, "0", 'a');

    return;
}

void
StudentModel_modifyStudent(string name,
                           string course,
                           int year,
                           string studentNumber,
                           string newStudentNumber,
                           string subjects,
                           string grades)
{
    /*
     * Modify the student.
     */

    StudentModel_removeStudent(studentNumber);
    StudentModel_addStudent(
        name,
        course,
        year,
        newStudentNumber,
        subjects,
        grades
    );

    return;
}

void
StudentModel_modifyStudentSubjectGrade(string studentNumber,
                                       string subjectName,
                                       double subjectGrade)
{
    /*
     * Modify the student grade.
     */

    // Get the subject index
    char subjects[256];
    strcpy(subjects, FileUtil_getStudentInfoProperty(4, studentNumber));

    int subjectIndex = 0;
    string token = strtok(subjects, ",");
    while (token != NULL) {
        if (token[0] == ' ') { // Remove the first character
            token++;
        }

        if (strcmp(subjectName, token) == 0) { // Found it!
            break;
        }

        token = strtok(NULL, ",");
        subjectIndex++;
    }

    // Now modify the grades
    char grades[256];
    strcpy(grades, FileUtil_getStudentInfoProperty(5, studentNumber));

    int gradeIndex = 0;
    char gradeList[256];
    strcpy(gradeList, "");
    string gradeToken = strtok(grades, ",");
    while (gradeToken != NULL) {
        if (token[0] == ' ') { // Remove the first character
            token++;
        }

        if (gradeIndex == subjectIndex) {
            char newGrade[256];
            strcpy(newGrade, "");
            sprintf(newGrade, "%f", subjectGrade);

            strcat(gradeList, newGrade);
            strcat(gradeList, ", ");
        }

        strcat(gradeList, gradeToken);
        strcat(gradeList, ", ");

        gradeToken = strtok(NULL, ",");
        gradeIndex++;
    }

    FileUtil_modifyStudentInfoProperty(5, studentNumber, gradeList, 'r');

    return;
}

void
StudentModel_removeStudentSubject(string studentNumber,
                                  string subjectName)
{
    /*
     * Remove a student subject.
     */

    // Get the subject index
    char subjects[256];
    strcpy(subjects, FileUtil_getStudentInfoProperty(4, studentNumber));

    int subjectIndex = 0;
    string token = strtok(subjects, ",");
    while (token != NULL) {
        if (token[0] == ' ') { // Remove the first character
            token++;
        }

        if (strcmp(subjectName, token) == 0) { // Found it!
            break;
        }

        token = strtok(NULL, ",");
        subjectIndex++;
    }

    // Remove the subject from the list
    int loopSubjectIndex = 0;
    char subjectList[256];
    strcpy(subjectList, "");
    string subjectToken = strtok(subjects, ",");
    while (subjectToken != NULL) {
        if (subjectToken[0] == ' ') { // Remove the first character
            subjectToken++;
        }

        if (loopSubjectIndex == subjectIndex) {
            strcat(subjectList, ", ");
        }

        strcat(subjectList, subjectToken);
        strcat(subjectList, ", ");

        subjectToken = strtok(NULL, ",");
        loopSubjectIndex++;
    }

    // Remove the subject from the grade list
    char grades[256];
    strcpy(grades, FileUtil_getStudentInfoProperty(5, studentNumber));

    int loopGradeIndex = 0;
    char gradeList[256];
    strcpy(gradeList, "");
    string gradeToken = strtok(grades, ",");
    while (gradeToken != NULL) {
        if (gradeToken[0] == ' ') { // Remove the first character
            gradeToken++;
        }

        if (loopGradeIndex == subjectIndex) {
            strcat(gradeList, ", ");
        }

        strcat(gradeList, gradeToken);
        strcat(gradeList, ", ");

        gradeToken = strtok(NULL, ",");
        loopGradeIndex++;
    }

    // Apply the changes
    FileUtil_modifyStudentInfoProperty(4, studentNumber, subjects, 'r');
    FileUtil_modifyStudentInfoProperty(5, studentNumber, grades, 'r');
}

string
StudentModel_getStudentSubjects(string studentNumber)
{
    /*
     * Get the student subject.
     */

    FILE *fp = FileUtil_openFile("StudentInfo.txt", "r");

    char line[256];
    strcpy(line, "");
    bool numberFound = false;
    while (fgets(line, 256, fp) != NULL) {
        char tmpLine[256];
        strcpy(tmpLine, line);
        numberFound = false;
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
            }

            tokenNumber++;
            token = strtok(NULL, "|");
        }

        if (numberFound) {
            string numberToken = strtok(tmpLine, "|");
            int tokenNumber = 0;
            while (token != NULL) {
                // Continue looping until the token points to the student number
                if (tokenNumber == 4) { // Located the student number
                    fclose(fp);
                    return numberToken;
                }

                tokenNumber++;
                numberToken = strtok(NULL, "|");
            }
        }
    }

    fclose(fp);
    return "None";
}

string
StudentModel_getStudentSubjectsGrade(string studentNumber)
{
    /*
     * Get the student subject grades.
     */

    FILE *fp = FileUtil_openFile("StudentInfo.txt", "r");

    char line[256];
    strcpy(line, "");
    bool numberFound = false;
    while (fgets(line, 256, fp) != NULL) {
        char tmpLine[256];
        strcpy(tmpLine, line);
        numberFound = false;
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
            string numberToken = strtok(tmpLine, "|");
            int tokenNumber = 0;
            while (token != NULL) {
                // Continue looping until the token points to the student number
                if (tokenNumber == 5) { // Located the student number
                    fclose(fp);
                    return numberToken;
                }

                tokenNumber++;
                numberToken = strtok(NULL, "|");
            }
        }
    }

    fclose(fp);
    return "None";
}

void
StudentModel_removeStudent(string studentNumber)
{
    /*
     * Remove a student.
     */

    FILE *fp = FileUtil_openFile("StudentInfo.txt", "r");

    char fileLines[256];
    strcpy(fileLines, "");
    char line[256];
    strcpy(line, "");
    bool numberFound = false;
    while (fgets(line, 256, fp) != NULL) {
        char tmpLine[256];
        strcpy(tmpLine, line);
        numberFound = false;
        // Tokenize the string
        string token = strtok(line, "|");
        int tokenNumber = 0;
        while (token != NULL) {
            // Continue looping until the token points to the student number
            if (tokenNumber == 3) { // Located the student number
                if (strcmp(studentNumber, token) != 0) {
                    strcat(fileLines, tmpLine);
                }
            }

            tokenNumber++;
            token = strtok(NULL, "|");
        }
    }

    fclose(fp);

    fp = FileUtil_openFile("StudentInfo.txt", "w");
    fprintf(fp, "%s", fileLines);

    fclose(fp);

    return;
}

void
StudentModel_displayStudentInfo(string studentNumber)
{
    /*
     * Display the student info of a student.
     */

    FILE *fp = FileUtil_openFile("StudentInfo.txt", "r");

    char subjects[256];
    strcpy(subjects, "");
    char grades[256];
    strcpy(grades, "");
    char line[256];
    strcpy(line, "");
    bool numberFound = false;
    char tmpLine[256];
    while (fgets(line, 256, fp) != NULL) {
        // Tokenize the string
        strcpy(tmpLine, line);
        string token = strtok(line, "|");
        int tokenNumber = 0;
        while (token != NULL) {
            // Continue looping until the token points to the student number
            if (tokenNumber == 3) { // Located the student number
                if (strcmp(studentNumber, token) == 0) {
                    printf("-----\n");
                    numberFound = true;
                }
            }

            if (numberFound && tokenNumber == 4) {
                // Get the student subjects
                strcpy(subjects, token);
            } else if (numberFound && tokenNumber == 5) {
                // Get the student grades
                strcpy(grades, token);
            }

            tokenNumber++;
            token = strtok(NULL, "|");
        }

        if (numberFound) {
            break;
        }
    }

    if (numberFound) {
        printf("-----\n");

        // Loop to get the basic information
        string infoToken = strtok(tmpLine, "|");
        int tokenIndex = 0;
        while (infoToken != NULL && tokenIndex < 4) {
            if (tokenIndex == 0) {
                printf("Name: %s\n", infoToken);
            }

            if (tokenIndex == 1) {
                printf("Course and Year: %s ", infoToken);
            }

            if (tokenIndex == 2) {
                printf("%s\n", infoToken);
            }

            if (tokenIndex == 3) {
                printf("Student Number: %s\n", infoToken);
            }

            tokenIndex++;
            infoToken = strtok(NULL, "|");
        }

        // Loop through the grades and subjects
        printf("Subjects:\n");

        string subjectToken = strtok(subjects, ",");
        string gradeToken = strtok(grades, ",");
        while (subjectToken != NULL && gradeToken != NULL) {
            printf("  %s - %s\n", subjectToken, gradeToken);

            subjectToken = strtok(NULL, ",");
            gradeToken = strtok(NULL, ",");
        }

        printf("-----\n");
    }

    fclose(fp);
}

void
StudentModel_displayAllStudentInfo()
{
    /*
     * Remove a student.
     */

    FILE *fp = FileUtil_openFile("StudentInfo.txt", "r");

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
            if (tokenNumber == 3) { // Located the student number
                StudentModel_displayStudentInfo(token);
            }

            tokenNumber++;
            token = strtok(NULL, "|");
        }
    }

    fclose(fp);

    return;
}
