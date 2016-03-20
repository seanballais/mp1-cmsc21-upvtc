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
StudentModel_modifyStudentName(string studentNumber,
                               string name)
{
    /*
     * Modify student name.
     */

    FileUtil_modifyStudentInfoProperty(0, studentNumber, name, 'r');

    return;
}

void
StudentModel_modifyStudentCourse(string studentNumber,
                                 string course)
{
    /*
     * Modify the student course.
     */

    FileUtil_modifyStudentInfoProperty(1, studentNumber, studentNumber, 'r');

    return;
}

void
StudentModel_modifyStudentYear(string studentNumber,
                               int year)
{
    /*
     * Modify the student year.
     */
    string strYear = NULL;
    sprintf(strYear, "%d", year);

    FileUtil_modifyStudentInfoProperty(2, studentNumber, strYear, 'r');

    return;
}

void
StudentModel_modifyStudentNumber(string studentNumber,
                                 string newStudentNumber)
{
    /*
     * Modify the student number.
     */

    FileUtil_modifyStudentInfoProperty(3, studentNumber, newStudentNumber, 'r');

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
    string subjects = FileUtil_getStudentInfoProperty(4, studentNumber);

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
    string grades = FileUtil_getStudentInfoProperty(5, studentNumber);

    int gradeIndex = 0;
    string gradeList = NULL;
    string gradeToken = strtok(grades, ",");
    while (gradeToken != NULL) {
        if (token[0] == ' ') { // Remove the first character
            token++;
        }

        if (gradeIndex == subjectIndex) {
            string newGrade = NULL;
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
    string subjects = FileUtil_getStudentInfoProperty(4, studentNumber);

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
    string subjectList = NULL;
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
    string grades = FileUtil_getStudentInfoProperty(5, studentNumber);

    int loopGradeIndex = 0;
    string gradeList = NULL;
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

void
StudentModel_removeStudent(string studentNumber)
{
    /*
     * Remove a student.
     */

    FILE *fp = FileUtil_openFile("StudentInfo.txt", "r");

    string fileLines = NULL;
    string line = NULL;
    bool numberFound = false;
    while (fgets(line, 256, fp) != NULL) {
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

        if (!numberFound) {
            strcat(fileLines, line);
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

    string subjects = NULL;
    string grades = NULL;
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
        string infoToken = strtok(line, "|");
        int tokenIndex = 0;
        while (infoToken != NULL && tokenIndex < 4) {
            if (tokenIndex == 0) {
                printf("Name: %s\n", infoToken);
            } else if (tokenIndex == 1) {
                printf("Course and Year: %s ", infoToken);
            } else if (tokenIndex == 2) {
                printf("%s\n", infoToken);
            } else if (tokenIndex == 3) {
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

    string fileLines = NULL;
    string line = NULL;
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
