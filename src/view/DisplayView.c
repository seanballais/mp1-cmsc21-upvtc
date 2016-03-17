/*
 * DisplayView.c
 *
 * Contains the functions that handles any text display related
 * tasks.
 *
 */

#include "DisplayView.h"

void
DisplayView_printMenu(const privilege userPrivilege)
{
    /*
     * Prints a menu that displays the tasks that are available
     * to a user privilege.
     */

    printf("GRADING BOOK MENU\n");

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

    printf("GRADING BOOK MENU - ADMIN\n");

    switch (userTask) {
        case ADD:
            printf("Add\n");
            printf("  1) Add Students\n");
            printf("  2) Add Subjects\n");
            break;
        case DELETE:
            printf("Delete\n");
            printf("  1) Delete Students\n");
            printf("  2) Delete Subjects\n");
            break;
        case UPDATE:
            printf("Update\n");
            printf("  1) Update Students\n");
            printf("  2) Update Subjects\n");
            break;
        default:
            break;
     }

     return;
}

void
DisplayView_printAdminUpdateStudentSubMenu();
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

    return;
}

void
DisplayView_printAdminUpdateSubjectSubMenu();
{
    /*
     * Prints the available options for the update subjects
     * submenu.
     */

    printf("GRADING BOOK MENU - ADMIN\n");
    printf("Update Subject\n");
    printf("  1) Update Subject Name\n");
    printf("  2) Update Subject Criteria\n");
    printf("  3) Update Subject Grade Range\n");

    return;
}
