/*
 * DisplayView.c
 *
 * Contains the functions that handles any text display related
 * tasks.
 *
 */

#include "DisplayView.h"

void
DisplayView_printUserPrivilegeMenu()
{
    /*
     * Prints a menu that displays the available user roles.
     */

     printf("GRADING BOOK USER ROLE\n");
     printf("  1) ADMIN\n");
     printf("  2) TEACHER\n");
     printf("  3) STUDENT\n");

     return;
}

void
DisplayView_printHeadUserDecoration(const privilege userPrivilege)
{
    /*
     * Prints the user privilege on the side of the
     * program header.
     */

    if (userPrivilege == ADMIN) {
        printf(" - ADMIN\n");
    } else if (userPrivilege == TEACHER) {
        printf(" - TEACHER\n");
    } else if (userPrivilege == STUDENT) {
        printf(" - STUDENT\n");
    }
}

void
DisplayView_printMenu(const privilege userPrivilege)
{
    /*
     * Prints a menu that displays the tasks that are available
     * to a user privilege.
     */

    printf("GRADING BOOK MENU");
    DisplayView_printHeadUserDecoration(userPrivilege);

    // Display submenus depending on the user privilege
    unsigned int menuNumber = 1;

    if (userPrivilege == ADMIN) {
        printf("  %u) Add\n", menuNumber++);
        printf("  %u) Delete\n", menuNumber++);
    }

    if (userPrivilege != STUDENT) {
        printf("  %u) Update\n", menuNumber++);
    }

    printf("  %u) Display\n", menuNumber++);
    printf("  %u) Exit\n", menuNumber++);

    return;
}

void
DisplayView_printAdminSubMenu(const tasks userTask)
{
    /*
     * Prints a menu that displays the subtasks that are available
     * to a task in an admin menu.
     */

    system("clear");
    printf("GRADING BOOK MENU");
    DisplayView_printHeadUserDecoration(ADMIN);

    switch (userTask) {
        case ADD:
            printf("Add\n");
            printf("  1) Add Students\n");
            printf("  2) Add Subjects\n");
            printf("  3) Exit\n");

            if (HandleInputView_inputAdminAdd() == 3) {
                DisplayView_printMenu(ADMIN);
                HandleInputView_inputPrivilegeSubMenu(ADMIN);
            }

            system("clear");

            DisplayView_printAdminSubMenu(userTask);

            break;
        case DELETE:
            printf("Delete\n");
            printf("  1) Delete Students\n");
            printf("  2) Delete Subjects\n");
            printf("  3) Exit\n");

            if (HandleInputView_inputAdminAdd() == 3) {
                DisplayView_printMenu(ADMIN);
                HandleInputView_inputPrivilegeSubMenu(ADMIN);
            }

            system("clear");

            DisplayView_printAdminSubMenu(userTask);

            break;
        case UPDATE:
            printf("Update\n");
            printf("  1) Update Students\n");
            printf("  2) Update Subjects\n");
            printf("  3) Exit\n");
            break;
        default:
            break;
     }

     return;
}

void
DisplayView_printAdminUpdateStudentSubMenu()
{
    /*
     * Prints the available options for the update student
     * submenu.
     */

    printf("GRADING BOOK MENU - ADMIN\n");
    printf("Update Student\n");
    printf("  1) Update Student Information\n");
    printf("  2) Update Student Subjects\n");
    printf("  3) Update Student Grades\n");
    printf("  4) Exit\n");

    return;
}

void
DisplayView_printAdminUpdateSubjectSubMenu()
{
    /*
     * Prints the available options for the update subjects
     * submenu.
     */

    printf("GRADING BOOK MENU - ADMIN\n");
    printf("Update Subject\n");
    printf("  1) Update Subject Criteria\n");
    printf("  2) Update Subject Grade Range\n");
    printf("  3) Exit\n");

    return;
}
