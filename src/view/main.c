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

// Included libraries
#include "../../lib/cs50/cs50.h"

int
main()
{
    // Initial menu
    system("clear");
    DisplayView_printUserPrivilegeMenu();
    printf("Input: ");
    privilege userPrivilege = GetInt();

    // Print the user privilege specific menu
    DisplayView_printMenu(userPrivilege);
}
