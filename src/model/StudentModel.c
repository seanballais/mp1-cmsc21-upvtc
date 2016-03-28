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

    // Get the index of the subject
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
        for (int i = 0; gradeToken[i] == ' '; i++) { // Remove the spaces
            gradeToken++;
        }

        if (gradeIndex == subjectIndex) {
            char newGrade[256];
            strcpy(newGrade, "");
            sprintf(newGrade, "%f", subjectGrade);

            strcat(gradeList, newGrade);
        } else {
            strcat(gradeList, gradeToken);
        }

        gradeIndex++;
        gradeToken = strtok(NULL, ",");

        if (gradeToken != NULL) {
            strcat(gradeList, ", ");
        }
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

    char tmpSubjects[256];
    strcpy(tmpSubjects, subjects);

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
    string subjectToken = strtok(tmpSubjects, ",");
    while (subjectToken != NULL) {
        if (subjectToken[0] == ' ') { // Remove the first character
            subjectToken++;
        }

        if (loopSubjectIndex != subjectIndex) {
            strcat(subjectList, subjectToken);
            strcat(subjectList, ", ");
        }

        loopSubjectIndex++;
        subjectToken = strtok(NULL, ",");
    }

    // Remove the last comma from the subject list
    char *subjectPos;
    if ((subjectPos = strrchr(subjectList, ',')) != NULL) {
        *subjectPos = '\0';
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

        if (loopGradeIndex != subjectIndex) {
            strcat(gradeList, gradeToken);
            strcat(gradeList, ", ");
        }

        loopGradeIndex++;
        gradeToken = strtok(NULL, ",");
    }

    char *gradePos;
    if ((gradePos = strchr(gradeList, '\n')) != NULL) {
        *gradePos = '\0';
    }

    // Apply the changes
    FileUtil_modifyStudentInfoProperty(4, studentNumber, subjectList, 'r');
    FileUtil_modifyStudentInfoProperty(5, studentNumber, gradeList, 'r');
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
            }

            tokenNumber++;
            token = strtok(NULL, "|");
        }

        if (numberFound) {
            string numberToken = strtok(tmpLine, "|");
            int tokenNumber = 0;
            while (numberToken != NULL) {
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

                    char subjects[256];
                    strcpy(
                        subjects,
                        StudentModel_getStudentSubjects(studentNumber)
                    );
                    string subjectPtr;

                    char grades[256];

                    strcpy(
                        grades,
                        StudentModel_getStudentSubjectsGrade(studentNumber)
                    );

                    string gradePtr;

                    // Display the subjects
                    string subjectToken = strtok_r(subjects, ",", &subjectPtr);
                    string gradeToken = strtok_r(grades, ",", &gradePtr);
                    while (subjectToken != NULL && gradeToken != NULL) {
                        if (subjectToken[0] == ' ') {
                            subjectToken++;
                        }

                        if (gradeToken[0] == ' ') {
                            gradeToken++;
                        }

                        if (strcmp(subjectToken, "") != 0 ||
                            strcmp(gradeToken, "") != 0) {
                            printf("  %s - %.4s\n", subjectToken, gradeToken);
                        }

                        subjectToken = strtok_r(NULL, ",", &subjectPtr);
                        gradeToken = strtok_r(NULL, ",", &gradePtr);
                    }

                    printf("-----\n\n");

                    goto exitPoint;
                }
            }

            tokenNumber++;
            token = strtok(NULL, "|");
        }

    }

    exitPoint:
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

bool
StudentModel_studentPresent(string studentNumber)
{
    /*
     * Check if a student is present.
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
            if (strcmp(token, studentNumber) == 0) { // Located the student number
                return true;
            }

            tokenNumber++;
            token = strtok(NULL, "|");
        }
    }

    fclose(fp);

    return false;
}
