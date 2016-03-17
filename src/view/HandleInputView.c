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
                DisplayView_printAdminSubMenu(userOption);
            } else if (userOption == 2) { // Delete option
                DisplayView_printAdminSubMenu(userOption);
            } else if (userOption == 3) { // Update option
                DisplayView_printAdminSubMenu(userOption);

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
                // Exit the program
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
                // Exit the program
            } else {
                printf("Unknown option %d.\n", userOption);
                goto inputPoint;
            }

            break;
        case STUDENT:
            if (userOption == 1) {
                // Display the Display submenu
            } else if (userOption == 2) {
                // Exit the program
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
