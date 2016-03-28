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
                system("clear");
                DisplayView_printAdminSubMenu(userOption - 1);
            } else if (userOption == 2) { // Delete option
                system("clear");
                DisplayView_printAdminSubMenu(userOption - 1);
            } else if (userOption == 3) { // Update option
                system("clear");
                DisplayView_printAdminSubMenu(userOption - 1);

                // Handle the [sub] submenu
                printf("Input: ");
                int updateOption = GetInt();
                if (updateOption == 1) {
                    DisplayView_printAdminUpdateStudentSubMenu();
                    if (HandleInputView_inputAdminUpdateStudent() == 4) {
                        system("clear");
                        DisplayView_printAdminUpdateStudentSubMenu(
                            userOption - 1
                        );
                    }
                } else if (updateOption == 2) {
                    DisplayView_printAdminUpdateSubjectSubMenu();
                    if (HandleInputView_inputAdminUpdateSubject() == 4) {
                        system("clear");
                        DisplayView_printAdminUpdateSubjectSubMenu();
                    }
                }

                system("clear");
                DisplayView_printMenu(0); // Admin
                HandleInputView_inputPrivilegeSubMenu(userPrivilege);
            } else if (userOption == 4) {
                system("clear");
                HandleInputView_inputAdminDisplayStudentInfo();
                system("clear");

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
            if (userOption == 1) { // Update
                system("clear");
                DisplayView_printTeacherUpdateSubMenu();

                int opt = 0;
                while (opt < 1 || opt > 3) {
                    printf("Input: ");
                    opt = GetInt();

                    if (opt == 1) { // Update student
                        HandleInputView_inputTeacherUpdateStudentGrade();

                        system("clear");
                        DisplayView_printTeacherUpdateSubMenu();
                        opt = 0;
                    } else if (opt == 2) { // Update subject
                        if (HandleInputView_inputTeacherUpdateSubject() == 3) {
                            system("clear");
                            DisplayView_printTeacherUpdateSubMenu();
                            opt = 0;
                        }
                    } else if (opt == 3) { // Exit from Update
                        system("clear");
                        DisplayView_printMenu(userPrivilege); // Teacher
                        HandleInputView_inputPrivilegeSubMenu(userPrivilege);
                    }
                }
            } else if (userOption == 2) { // Display
                system("clear");
                HandleInputView_inputAdminDisplayStudentInfo();

                system("clear");
                DisplayView_printMenu(userPrivilege); // Teacher
                HandleInputView_inputPrivilegeSubMenu(userPrivilege);
            } else if (userOption == 3) {
                exit(0);
            } else {
                printf("Unknown option %d.\n", userOption);
                goto inputPoint;
            }

            break;
        case STUDENT:
            if (userOption == 1) {
                HandleInputView_inputStudentDisplayStudentInfo();

                system("clear");
                DisplayView_printMenu(userPrivilege); // Teacher
                HandleInputView_inputPrivilegeSubMenu(userPrivilege);
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

                // Add them to the subject and grade string if
                // subject is present
                if (Controller_subjectPresent(subjectName)) {
                    strcat(subjects, subjectName);
                    strcat(grades, grade);
                } else {
                    printf("Unknown subject %s. Add it first.\n", subjectName);
                }

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

            if (!Controller_studentPresent(studentNumber)) {
                printf("Student %s does not exist.\n", studentNumber);
            } else {
                Controller_removeStudent(studentNumber);
            }


            printf("Delete another student? (1 for yes, 2 for no) ");
            int deleteOpt = GetInt();
            bailOutDeleteStudent:

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

            if (!Controller_subjectPresent(subjectName)) {
                printf("Student %s does not exist.\n", subjectName);
            } else {
                Controller_removeSubject(subjectName);
            }


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

            if (!Controller_studentPresent(studentNumber)) {
                printf("Student %s does not exist.\n", studentNumber);
                printf("Press enter to continue...");
                getchar();
                goto bailOutUpdateStudent;
            }

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
            bailOutUpdateStudent:

            if (studOpt != 1) {
                updateStudents = false;
            }

            system("clear");
        }
    } else if (opt == 2) { // Update student subjects
        char studentNumber[256];
        strcpy(studentNumber, "");

        printf("Update Student Subjects\n");
        printf("Student Number: ");
        strcpy(studentNumber, GetString());
        bool updateSubjects = true;

        if (!Controller_studentPresent(studentNumber)) {
            printf("Student %s does not exist.\n", studentNumber);
            printf("Press Enter to continue...");
            getchar();
            updateSubjects = false;
        }

        while (updateSubjects) {
            int opt = 1;
            printf("Add (1) or Remove (2) subjects? ");
            opt = GetInt();
            if (opt == 1) {
                char subject[256];
                strcpy(subject, "");

                printf("Subject to add: ");
                strcpy(subject, GetString());

                if (Controller_subjectPresent(subject)) {
                    Controller_addStudentSubject(studentNumber, subject);
                } else {
                    printf("Subject %s is unknown.\n", subject);
                }

            } else if (opt == 2) {
                char subject[256];
                strcpy(subject, "");

                printf("Subject to remove: ");
                strcpy(subject, GetString());

                if (Controller_subjectPresent(subject)) {
                    Controller_removeStudentSubject(studentNumber, subject);
                } else {
                    printf("Subject %s is unknown.\n", subject);
                }
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

        if (!Controller_studentPresent(studentNumber)) {
            printf("Student %s does not exist.\n", studentNumber);
            goto bailOut;
        }
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

            if (!Controller_subjectPresent(subject)) {
                printf("Subject %s is unknown.\n", subject);
                goto bailOut;
            }

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
                } else if (index == 1) {
                    // Get the percentage and convert the rate
                    grade += rate * ((float) atof(criteriaToken) / 100.0);
                }

                index = index ^ 1;
                criteriaToken = strtok(NULL, ",");
            }

            // Convert to denominations
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
            string rangeToken = strtok(subjectRange, ",");
            int rangeIndex = 0;
            while (rangeToken != NULL) {
                if (rangeToken[0] == ' ') {
                    rangeToken++;
                }

                if (grade >= atof(rangeToken)) {
                    grade = gradeRange[rangeIndex];
                    break;
                }

                rangeToken = strtok(NULL, ",");
                rangeIndex++;

                if (rangeIndex == 10) {
                    grade = 5.00;
                }
            }

            Controller_updateStudentSubjectGrade(studentNumber,
                                                 subject,
                                                 grade);

            bailOut:

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

            if (!Controller_subjectPresent(subjectName)) {
                printf("Subject %s is unknown.\n", subjectName);
                goto bailOut2;
            }

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

            bailOut2:

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

            if (!Controller_subjectPresent(subjectName)) {
                printf("Subject %s is unknown.\n", subjectName);
                goto bailOut3;
            }

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

            bailOut3:

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
        printf("Display all Student info.\n");
        Controller_displayAllStudentInfo();

        printf("Press Enter key to continue...");
        getchar();
    } else if (opt == 2) { // Specify student to display output
        printf("Display Student Info.\n");
        printf("Student Number: ");

        char studentNumber[256];
        strcpy(studentNumber, GetString());
        if(Controller_studentPresent(studentNumber)) {
            Controller_displayStudentInfo(studentNumber);
        } else {
            printf("Student %s does not exist.\n", studentNumber);
        }

        printf("Press Enter key to continue...");
        getchar();
    }
}

void
HandleInputView_inputTeacherUpdateStudentGrade()
{
    /*
     * Handle the teacher updating the student grade.
     */

     char studentNumber[256];
     strcpy(studentNumber, "");
     char subjects[256];
     strcpy(subjects, "");

     printf("Update student subject grades\n");
     printf("Student Number: ");
     strcpy(studentNumber, GetString());

     bool updateSubjectGrades = true;
     if(Controller_studentPresent(studentNumber)) {
         Controller_displayStudentInfo(studentNumber);
     } else {
         printf("Student %s does not exist.\n", studentNumber);
         goto bailOutUpdate;
     }

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

         if (!Controller_subjectPresent(subject)) {
             printf("Subject %s is unknown.\n", subject);
             goto bailOutUpdate;
         }

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
             } else if (index == 1) {
                 // Get the percentage and convert the rate
                 grade += rate * ((float) atof(criteriaToken) / 100.0);
             }

             index = index ^ 1;
             criteriaToken = strtok(NULL, ",");
         }

         // Convert to denominations
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
         string rangeToken = strtok(subjectRange, ",");
         int rangeIndex = 0;
         while (rangeToken != NULL) {
             if (rangeToken[0] == ' ') {
                 rangeToken++;
             }

             if (grade >= atof(rangeToken)) {
                 grade = gradeRange[rangeIndex];
                 break;
             }

             rangeToken = strtok(NULL, ",");
             rangeIndex++;

             if (rangeIndex == 10) {
                 grade = 5.00;
             }
         }

         Controller_updateStudentSubjectGrade(studentNumber,
                                              subject,
                                              grade);

        bailOutUpdate:

         printf("Update more grades of subject? (1 for yes, 2 for no) ");
         int opt = GetInt();

         if (opt != 1) {
             updateSubjectGrades = false;
         }
     }
}

int
HandleInputView_inputTeacherUpdateSubject()
{
    /*
     * Handle the subject modification.
     */

    printf("Update Subject\n");
    printf("  1) Update Subject Criteria\n");
    printf("  2) Update Subject Grade Range\n");
    printf("  3) Exit\n");

    return HandleInputView_inputAdminUpdateSubject();
}

void
HandleInputView_inputStudentDisplayStudentInfo()
{
    /*
     * Handle the student display information.
     */

    printf("Display Student Info.\n");
    printf("Student Number: ");

    char studentNumber[256];
    strcpy(studentNumber, GetString());

    if (Controller_studentPresent(studentNumber)) {
        Controller_displayStudentInfo(studentNumber);
    } else {
        printf("Student %s does not exist.\n", studentNumber);
    }

    printf("Press Enter key to continue...");
    getchar();
}
