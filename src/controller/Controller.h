/*
 * Controller.h
 *
 * Links the model to the view and vice versa.
 *
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H

    #include <stdio.h>

    // Project headers
    #include "../utils/DataTypeDefinitions.h"
    #include "../model/StudentModel.h"
    #include "../model/SubjectModel.h"

    void Controller_addStudent(char name[],
                               char course[],
                               int year,
                               char studentNumber[],
                               char subjects[],
                               char grades[]);
    void Controller_addSubject(char subjectName[],
                               char subjectCriteria[],
                               char subjectRange[]);
    void Controller_removeStudent(char studentNumber[]);
    void Controller_removeSubject(char subjectName[]);
    void Controller_updateStudentInfo(char name[],
                                      char course[],
                                      int year,
                                      char studentNumber[],
                                      char newStudentNumber[]);
    void Controller_addStudentSubject(char studentNumber[],
                                      char subject[]);
    void Controller_removeStudentSubject(char studentNumber[],
                                         char subjectName[]);
    void Controller_updateStudentSubjectGrade(char studentNumber[],
                                              char subjectName[],
                                              double subjectGrade);
    void Controller_updateSubjectName(char subjectName[],
                                      char newSubjectName[]);
    void Controller_updateSubjectCriteria(char subjectName[],
                                          char subjectCriteria[]);
    void Controller_updateSubjectRange(char subjectName[],
                                       char subjectRange[]);
    void Controller_listSubjects();
    void Controller_displayStudentInfo(char studentNumber[]);
    void Controller_displayAllStudentInfo();

#endif