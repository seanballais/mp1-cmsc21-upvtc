/*
 * main.c
 *
 * The main entry point in the program.
 *
 */

#include <stdio.h>
#include <stdlib.h>

// Project headers
#include "../utils/UserDefinitions.h"

// View headers
#include "DisplayView.h"
#include "HandleInputView.h"

// Included libraries
#include "../../lib/cs50/cs50.h"

int
main()
{
    // Initial menu
    system("clear");
    DisplayView_printUserPrivilegeMenu();
    printf("Input: ");

    // Subtract by 1 since we're starting from 0
    privilege userPrivilege = GetInt() - 1;

    // Print the user privilege specific menu
    system("clear");
    DisplayView_printMenu(userPrivilege);
    HandleInputView_inputPrivilegeSubMenu(userPrivilege);

    return 0;
}
