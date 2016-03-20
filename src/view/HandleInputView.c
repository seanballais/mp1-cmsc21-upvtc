/*
 * DisplayView.c
 *
 * Contains the functions that handles any text display related
 * tasks.
 *
 */

#include "HandleInputView.h"

void
HandleInputView_inputPrivilegeSubMenu(const privilege userPrivilege)
{
    /*
     * Handles the input in the immediate submenu.
     */

    inputPoint:
    printf("Input: ");
    int userOption = GetInt();

    switch(userPrivilege) {
        case ADMIN:
            if (userOption == 1) { // Add option
                DisplayView_printAdminSubMenu(userOption - 1);
            } else if (userOption == 2) { // Delete option
                DisplayView_printAdminSubMenu(userOption - 1);
            } else if (userOption == 3) { // Update option
                DisplayView_printAdminSubMenu(userOption - 1);

                // Handle the [sub] submenu
                printf("Input: ");
                int updateOption = 0;
                do {
                    updateOption = GetInt();
                    if (updateOption == 1) {
                        DisplayView_printAdminUpdateStudentSubMenu();
                    } else if (updateOption == 2) {
                        DisplayView_printAdminUpdateSubjectSubMenu();
                    }
                } while (updateOption < 1 || updateOption > 2);
            } else if (userOption == 4) {
                // Display student Information
            } else if (userOption == 5) {
                exit(0);
            } else {
                printf("Unknown option %d.\n", userOption);
                goto inputPoint;
            }

            break;
        case TEACHER:
            if (userOption == 1) {
                // Display the Update submenu for the teacher
            } else if (userOption == 2) {
                // Display the Display Submenu
            } else if (userOption == 3) {
                exit(0);
            } else {
                printf("Unknown option %d.\n", userOption);
                goto inputPoint;
            }

            break;
        case STUDENT:
            if (userOption == 1) {
                // Display the Display submenu
            } else if (userOption == 2) {
                exit(0);
            } else {
                printf("Unknown option %d.\n", userOption);
                goto inputPoint;
            }

            break;
        default:
            break;
    }

    return;
}

int
HandleInputView_inputAdminAdd()
{
    /*
     * Handle the adding the students or subjects.
     */

    int opt = 0;
    do {
        printf("Input: ");
        opt = GetInt();

        if (opt < 1 || opt > 3) {
            printf("Input must not be greater than 3 or less than 1!\n");
        }
    } while (opt < 1 || opt > 3);

    system("clear");
    if (opt == 1) { // Add students
        char name[256];
        strcpy(name, "");
        char course[256];
        strcpy(course, "");
        int year = 0;
        char studentNumber[256];
        strcpy(studentNumber, "");

        bool addStudents = true;
        while (addStudents) {
            printf("Student Information\n");
            printf("Name: ");
            strcpy(name, GetString());

            printf("Course: ");
            strcpy(course, GetString());

            printf("Year: ");
            year = GetInt();

            printf("Student Number: ");
            strcpy(studentNumber, GetString());

            char subjects[256];
            strcpy(subjects, "");
            char grades[256];
            strcpy(grades, "");
            printf("Add subjects and initial grade\n");
            int opt = 1;
            do {
                printf("Subject Name: ");
                char subjectName[256];
                strcpy(subjectName, GetString());

                printf("Grade: ");
                char grade[256];
                strcpy(grade, GetString());

                // Add them to the subject and grade string
                strcat(subjects, subjectName);
                strcat(grades, grade);

                printf("Add another subject? (1 for yes, 2 for no) ");
                opt = GetInt();

                if (opt == 1) {
                    strcat(subjects, ", ");
                    strcat(grades, ", ");
                }
            } while (opt == 1);

            Controller_addStudent(
                name,
                course,
                year,
                studentNumber,
                subjects,
                grades
            );
            printf("Added student %s.\n", name);

            printf("Add more students? (1 for yes, 2 for no) ");
            int studOpt = GetInt();

            if (studOpt != 1) {
                addStudents = false;
            }

            system("clear");
        }
    } else if (opt == 2) { // Add subjects
        char subjectName[256];
        strcpy(subjectName, "");
        char subjectCriteria[256];
        strcpy(subjectCriteria, "");
        char subjectRange[256];
        strcpy(subjectRange, "");

        bool addSubjects = true;
        while (addSubjects) {
            printf("Subject Information\n");
            printf("Subject name: ");
            strcpy(subjectName, GetString());

            // Now the criteria
            printf("Subject Criteria:\n");
            strcpy(subjectCriteria, "");
            int criteria = 100;
            char tmpCriteriaName[256];
            strcpy(tmpCriteriaName, "");
            int tmpCriteriaRate = 0;
            while (criteria > 0) {
                printf("Criteria name: ");
                strcpy(tmpCriteriaName, GetString());

                do {
                    printf("Percentage left: %d%c\n", criteria, 37);
                    printf("Criteria percentage: ");
                    tmpCriteriaRate = GetInt();

                    if (tmpCriteriaRate > criteria) {
                        printf("Rate must be less than %d%c.\n", criteria, 37);
                    }
                } while (tmpCriteriaRate > criteria);

                if (criteria < 100) {
                    strcat(subjectCriteria, ", ");
                }

                criteria = criteria - tmpCriteriaRate;

                strcat(subjectCriteria, tmpCriteriaName);
                strcat(subjectCriteria, ", ");
                char tmpRate[256];
                strcpy(tmpRate, "");
                sprintf(tmpRate, "%d", tmpCriteriaRate);
                strcat(subjectCriteria, tmpRate);
            }

            // Now the range
            strcpy(subjectRange, "");
            printf("Subject Range\n");
            double gradeRange[10] = {
                1.00,
                1.25,
                1.50,
                1.75,
                2.00,
                2.25,
                2.50,
                2.75,
                3.00,
                4.00
            };
            for (int ctr = 0; ctr < 10; ctr++) {
                printf("Minimum grade to get %.2f: ", gradeRange[ctr]);
                char minGrade[256];
                strcpy(minGrade, GetString());

                if (ctr > 0) {
                    strcat(subjectRange, ", ");
                }

                strcat(subjectRange, minGrade);
            }

            Controller_addSubject(
                subjectName,
                subjectCriteria,
                subjectRange
            );

            printf("Add another subject? (1 for yes, 2 for no) ");
            int subjectOpt = GetInt();

            if (subjectOpt != 1) {
                addSubjects = false;
            }

            system("clear");
        }
    } else if (opt == 3) {
        return 3;
    }

    return 0;
}

int
HandleInputView_inputAdminDelete()
{
    /*
     * Handle the deleting of the students or subjects.
     */

    int opt = 0;
    do {
        printf("Input: ");
        opt = GetInt();

        if (opt < 1 || opt > 3) {
            printf("Input must not be greater than 3 or less than 1!\n");
        }
    } while (opt < 1 || opt > 3);

    system("clear");

    if (opt == 1) {
        bool deleteStudent = true;
        while (deleteStudent) {
            printf("Deleting student\n");
            printf("Student Number: ");
            char studentNumber[256];
            strcpy(studentNumber, GetString());

            Controller_removeStudent(studentNumber);

            printf("Delete another student? (1 for yes, 2 for no) ");
            int deleteOpt = GetInt();

            if (deleteOpt != 1) {
                deleteStudent = false;
            }
        }
    } else if (opt == 2) {
        bool deleteSubject = true;
        while (deleteSubject) {
            printf("Deleting subject\n");
            printf("Subject Name: ");
            char subjectName[256];
            strcpy(subjectName, GetString());

            Controller_removeSubject(subjectName);

            printf("Delete another subject? (1 for yes, 2 for no) ");
            int deleteOpt = GetInt();

            if (deleteOpt != 1) {
                deleteSubject = false;
            }
        }
    } else if (opt == 3) {
        return 3;
    }

    return 0;
}
