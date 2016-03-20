/*
 * HandleInputView.h
 *
 * Contains the functions that handles any text input in the view.
 *
 */

#ifndef HANDLEINPUTVIEW_H
#define HANDLEINPUTVIEW_H

    #include <stdio.h>
    #include <stdlib.h>

    // Project headers
    #include "DisplayView.h"
    #include "../utils/UserDefinitions.h"

    // Included libraries
    #include "../../lib/include/cs50.h"

    void HandleInputView_inputPrivilegeSubMenu(const privilege userPrivilege);
    void HandleInputView_inputAdminAddStudents();

#endif
