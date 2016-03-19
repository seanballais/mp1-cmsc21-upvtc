/*
 * StudentModel.c
 *
 * Handles data manipulation with respect to the student data.
 *
 */

 #include "StudentModel.h"

void
StudentModel_addStudent(string name,
                        string course,
                        int year,
                        string studentNumber,
                        string subjects[])
{
    /*
     * Add student in the JSON file.
     */

    
}

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
void StudentModel_modifyStudentSubjectName(string studentNumber,
                                           string subjectName,
                                           string newSubjectName);
void StudentModel_modifyStudentSubjectGrade(string studentNumber,
                                            string subjectName,
                                            double subjectGrade);
void StudentModel_removeStudentSubject(string studentNumber,
                                       string subjectName);
void StudentModel_removeStudent(string studentNumber);
