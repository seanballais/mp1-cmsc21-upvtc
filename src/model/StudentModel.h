/*
 * StudentModel.h
 *
 * Handles data manipulation with respect to the student data.
 *
 */

#ifndef STUDENTMODEL_H
#define STUDENTMODEL_H

    #include <stdio.h>
    #include <string.h>

    // Project headers
    #include "../utils/DataTypeDefinitions.h"
    #include "FileHandler.h"

    void StudentModel_addStudent(string name,
                                 string course,
                                 int year,
                                 string studentNumber,
                                 string subjects,
                                 string grades);
    void StudentModel_addStudentSubject(string studentNumber,
                                        string subject);
    void StudentModel_modifyStudentName(string studentNumber,
                                        string name);
    void StudentModel_modifyStudentCourse(string studentNumber,
                                          string course);
    void StudentModel_modifyStudentYear(string studentNumber,
                                        int year);
    void StudentModel_modifyStudentNumber(string studentNumber,
                                          string newStudentNumber);
    void StudentModel_modifyStudentSubjectGrade(string studentNumber,
                                                string subjectName,
                                                double subjectGrade);
    string StudentModel_getStudentSubjects(string studentNumber);
    string StudentModel_getStudentSubjectsGrade(string studentNumber);
    void StudentModel_removeStudentSubject(string studentNumber,
                                           string subjectName);
    void StudentModel_removeStudent(string studentNumber);
    void StudentModel_displayStudentInfo(string studentNumber);
    void StudentModel_displayAllStudentInfo();

#endif
