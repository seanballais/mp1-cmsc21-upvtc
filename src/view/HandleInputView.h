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
    #include <stdbool.h>
    #include <string.h>

    // Project headers
    #include "DisplayView.h"
    #include "../utils/UserDefinitions.h"
    #include "../utils/DataTypeDefinitions.h"
    #include "../controller/Controller.h"

    // Included libraries
    #include "../../lib/include/cs50.h"

    void HandleInputView_inputPrivilegeSubMenu(const privilege userPrivilege);

    int HandleInputView_inputAdminAdd();
    int HandleInputView_inputAdminDelete();
    int HandleInputView_inputAdminUpdateStudent();
    int HandleInputView_inputAdminUpdateSubject();
    void HandleInputView_inputAdminDisplayStudentInfo();

    void HandleInputView_inputTeacherUpdateStudentGrade();
    int HandleInputView_inputTeacherUpdateSubject();

    void HandleInputView_inputStudentDisplayStudentInfo();

#endif
