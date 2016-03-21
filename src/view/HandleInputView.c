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
                int updateOption = GetInt();
                if (updateOption == 1) {
                    DisplayView_printAdminUpdateStudentSubMenu();
                    if (HandleInputView_inputAdminUpdateStudent() == 4) {
                        DisplayView_printAdminSubMenu(userOption - 1);
                    }
                } else if (updateOption == 2) {
                    DisplayView_printAdminUpdateSubjectSubMenu();
                    if (HandleInputView_inputAdminUpdateSubject() == 4) {
                        DisplayView_printAdminSubMenu(userOption - 1);
                    }
                }

                DisplayView_printMenu(0); // Admin
                HandleInputView_inputPrivilegeSubMenu(userPrivilege);
                system("clear");
            } else if (userOption == 4) {
                HandleInputView_inputAdminDisplayStudentInfo();

                DisplayView_printMenu(userPrivilege);
                HandleInputView_inputPrivilegeSubMenu(userPrivilege);
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

        if (opt < 1 || opt > 4) {
            printf("Input must not be greater than 4 or less than 1!\n");
        }
    } while (opt < 1 || opt > 4);

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

            printf("Okay\n");

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

int
HandleInputView_inputAdminUpdateStudent()
{
    /*
     * Handle the update for the student.
     */

    int opt = 0;
    do {
        printf("Input: ");
        opt = GetInt();

        if (opt < 1 || opt > 4) {
            printf("Input must not be greater than 4 or less than 1!\n");
        }
    } while (opt < 1 || opt > 4);

    system("clear");
    if (opt == 1) { // Update students
        char name[256];
        strcpy(name, "");
        char course[256];
        strcpy(course, "");
        int year = 0;
        char studentNumber[256];
        strcpy(studentNumber, "");
        char newStudentNumber[256];
        strcpy(newStudentNumber, "");

        bool updateStudents = true;
        while (updateStudents) {
            printf("Student Information\n");
            printf("Student Number: ");
            strcpy(studentNumber, GetString());

            printf("Updating details\n");
            printf("Name: ");
            strcpy(name, GetString());

            printf("Course: ");
            strcpy(course, GetString());

            printf("Year: ");
            year = GetInt();

            printf("Student Number: ");
            strcpy(newStudentNumber, GetString());

            char subjects[256];
            strcpy(subjects, "");
            strcpy(subjects, Controller_getStudentSubjects(studentNumber));

            char grades[256];
            strcpy(grades, "");
            strcpy(grades, Controller_getStudentSubjectsGrade(studentNumber));


            Controller_updateStudentInfo(
                name,
                course,
                year,
                studentNumber,
                newStudentNumber,
                subjects,
                grades
            );

            printf("Updated student %s.\n", name);

            printf("Update more students? (1 for yes, 2 for no) ");
            int studOpt = GetInt();

            if (studOpt != 1) {
                updateStudents = false;
            }

            system("clear");
        }
    } else if (opt == 2) {
        char studentNumber[256];
        strcpy(studentNumber, "");

        printf("Update Student Subjects\n");
        printf("Student Number: ");
        strcpy(studentNumber, GetString());

        bool updateSubjects = true;
        while (updateSubjects) {
            int opt = 1;
            printf("Add (1) or Remove (2) subjects? ");
            opt = GetInt();
            if (opt == 1) {
                char subject[256];
                strcpy(subject, "");

                printf("Subject to add: ");
                strcpy(subject, GetString());

                Controller_addStudentSubject(studentNumber, subject);
            } else if (opt == 2) {
                char subject[256];
                strcpy(subject, "");

                printf("Subject to remove: ");
                strcpy(subject, GetString());

                Controller_removeStudentSubject(studentNumber, subject);
            }

            printf("Add or remove more subjects? (1 for yes, 2 for no) ");
            opt = GetInt();

            if (opt != 1) {
                updateSubjects = false;
            }
        }
    } else if (opt == 3) { // Update a subject grade
        char studentNumber[256];
        strcpy(studentNumber, "");
        char subjects[256];
        strcpy(subjects, "");

        printf("Update student subject grades\n");
        printf("Student Number: ");
        strcpy(studentNumber, GetString());

        bool updateSubjectGrades = true;
        while (updateSubjectGrades) {
            // Print the subjects
            printf("Subjects of %s\n", studentNumber);
            strcpy(subjects, Controller_getStudentSubjects(studentNumber));
            string token = strtok(subjects, ",");
            while (token != NULL) {
                if (token[0] == ' ') {
                    token++;
                }

                printf("  - %s\n", token);

                token = strtok(NULL, ",");
            }

            // Selection
            char subject[256];
            strcpy(subject, "");
            printf("Subject to update the grade: ");
            strcpy(subject, GetString());

            // Now get the grade
            char subjectCriteria[256];
            strcpy(subjectCriteria, Controller_getSubjectCriteria(subject));
            char subjectRange[256];
            strcpy(subjectRange, Controller_getSubjectRange(subject));

            // Calculate grade from criteria
            printf("Input grade\n");
            double rate = 0;
            double grade = 0.0;
            string criteriaToken = strtok(subjectCriteria, ",");
            int index = 0;
            while (criteriaToken != NULL) {
                if (criteriaToken[0] == ' ') {
                    criteriaToken++;
                }

                if (index == 0) {
                    // Print criteria name
                    printf("%s: ", criteriaToken);
                    rate = GetDouble();

                    index = 1;
                } else if (index == 1) {
                    // Get the percentage and convert the rate
                    grade += rate * (atof(token) / 100);

                    index = 0;
                }

                criteriaToken = strtok(NULL, ",");
            }

            // Convert to denominations
            string rangeToken = strtok(subjectRange, ",");
            while (rangeToken != NULL) {
                if (rangeToken[0] == ' ') {
                    rangeToken++;
                }

                if (grade >= atof(rangeToken)) {
                    grade = atof(rangeToken);
                    break;
                }

                rangeToken = strtok(NULL, ",");
            }

            Controller_updateStudentSubjectGrade(studentNumber,
                                                 subject,
                                                 grade);

            printf("Update more grades of subject? (1 for yes, 2 for no) ");
            opt = GetInt();

            if (opt != 1) {
                updateSubjectGrades = false;
            }
        }
    } else if (opt == 4) {
        return 4;
    }

    return 0;
}

int
HandleInputView_inputAdminUpdateSubject()
{
    /*
     * Handle the update for the subjects.
     */

    int opt = 0;
    do {
        printf("Input: ");
        opt = GetInt();

        if (opt < 1 || opt > 3) {
            printf("Input must not be greater than 3 or less than 1!\n");
        }
    } while (opt < 1 || opt > 3);

    if (opt == 1) { // Update subject criteria
        printf("Update Subject Criteria\n");

        bool updateSubjectCriteria = true;
        while (updateSubjectCriteria) {
            char subjectName[256];
            strcpy(subjectName, "");

            printf("Subject name: ");
            strcpy(subjectName, GetString());

            char criteria[256];
            strcpy(criteria, "");

            printf("Criteria\n");
            int criteriaRate = 100;
            char criteriaName[256];
            strcpy(criteriaName, "");
            int criteriaInput = 0;
            while (criteriaRate > 0) {
                printf("Criteria name: ");
                strcpy(criteriaName, GetString());

                do {
                    printf("Percentage left: %d%c\n", criteriaRate, 37);
                    printf("Criteria percentage: ");
                    criteriaInput = GetInt();

                    if (criteriaInput > criteriaRate) {
                        printf(
                            "Rate must be less than %d%c.\n",
                            criteriaRate,
                            37
                        );
                    }
                } while (criteriaInput > criteriaRate);

                if (criteriaRate < 100) {
                    strcat(criteria, ", ");
                }

                criteriaRate = criteriaRate - criteriaInput;

                strcat(criteria, criteriaName);
                strcat(criteria, ", ");
                char tmpRate[256];
                strcpy(tmpRate, "");
                sprintf(tmpRate, "%d", criteriaInput);
                strcat(criteria, tmpRate);
            }

            Controller_updateSubjectCriteria(subjectName, criteria);

            printf("Update another subject? (1 for yes, 2 for no) ");
            opt = GetInt();

            if (opt != 1) {
                updateSubjectCriteria = false;
            }
        }
    } else if (opt == 2) { // Update subject rating
        printf("Update Subject Range\n");

        bool updateSubjectRange = true;
        while (updateSubjectRange) {
            printf("Subject name: ");

            char subjectName[256];
            strcpy(subjectName, GetString());

            char subjectRange[256];
            strcpy(subjectRange, "");
            printf("New subject Range for %s\n", subjectName);
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

            Controller_updateSubjectRange(subjectName, subjectRange);

            printf("Update another subject's range? (1 for yes, 2 for no) ");
            opt = GetInt();

            if (opt != 1) {
                updateSubjectRange = false;
            }
        }
    } else if (opt == 3) {
        return 3;
    }

    return 0;
}

void
HandleInputView_inputAdminDisplayStudentInfo()
{
    /*
     * Handle Display of input.
     */

    printf("Display all student info (1) or specify student (2)? ");
    int opt = GetInt();

    if (opt == 1) { // Display all student info
        printf("Display all student info.\n");
        Controller_displayAllStudentInfo();

        printf("Press Enter key to continue...");
        getchar();
    } else if (opt == 2) { // Specify student to display output
        printf("Display Student Info.\n");
        printf("Student Number: ");

        char studentNumber[256];
        strcpy(studentNumber, GetString());

        Controller_displayStudentInfo(studentNumber);
    }
}
