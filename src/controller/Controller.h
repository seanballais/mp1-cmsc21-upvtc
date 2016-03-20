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
    #include "../model/StudentModel.h"
    #include "../model/SubjectModel.h"

    void Controller_addStudent(string name.
                               string course,
                               int year,
                               string studentNumber,
                               string subjects,
                               string grades);
    void Controller_addSubject(string subjectName,
                               string subjectCriteria,
                               string subjectRange);
    void Controller_removeStudent(string studentNumber);
    void Controller_removeSubject(string subjectName);
    void Controller_updateStudentInfo(string name.
                                      string course,
                                      int year,
                                      string studentNumber,
                                      string newStudentNumber);
    void Controller_addStudentSubject(string studentNumber,
                                      string subject);
    void Controller_removeStudentSubject(string studentNumber,
                                         string subjectName);
    void Controller_updateStudentSubjectGrade(string studentNumber,
                                              string subjectName,
                                              double subjectGrade);
    void Controller_updateSubjectName(string subjectName,
                                      string newSubjectName);
    void Controller_updateSubjectCriteria(string subjectName,
                                          string subjectCriteria);
    void Controller_updateSubjectRange(string subjectName,
                                       string subjectRange);
    void Controller_listSubjects();
    void Controller_displayStudentInfo(string studentNumber);
    void Controller_displayAllStudentInfo();

#endif
