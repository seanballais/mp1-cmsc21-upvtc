/*
 * DisplayView.h
 *
 * Contains the functions that handles any text display related
 * tasks.
 *
 */

#ifndef DISPLAYVIEW_H
#define DISPLAYVIEW_H

    #include <stdio.h>
    #include <stdlib.h>

    // Project headers
    #include "../utils/UserDefinitions.h"

    void DisplayView_printUserPrivilegeMenu();
    void DisplayView_printHeadUserDecoration(const privilege userPrivilege);
    void DisplayView_printMenu(const privilege userPrivilege);
    void DisplayView_printAdminSubMenu(const privilege userPrivilege,
                                       const tasks userTask);
    void DisplayView_printAdminUpdateStudentSubMenu();
    void DisplayView_printAdminUpdateSubjectSubMenu();

#endif
