/*
 * Controller.c
 *
 * Links the model to the view and vice versa.
 *
 */

#include "Controller.h"

void
Controller_addStudent(char name[],
                      char course[],
                      int year,
                      char studentNumber[],
                      char subjects[],
                      char grades[])
{
    /*
     * Add a student.
     */

    StudentModel_addStudent(name,
                            course,
                            year,
                            studentNumber,
                            subjects,
                            grades);

    return;
}

void
Controller_addSubject(char subjectName[],
                      char subjectCriteria[],
                      char subjectRange[])
{
    /*
     * Add a subject.
     */

    SubjectModel_addSubject(subjectName, subjectCriteria, subjectRange);
}

void
Controller_removeStudent(char studentNumber[])
{
    /*
     * Remove a student.
     */

    StudentModel_removeStudent(studentNumber);

    return;
}

void
Controller_removeSubject(char subjectName[])
{
    /*
     * Remove a subject.
     */

    SubjectModel_removeSubject(subjectName);

    return;
}

void
Controller_updateStudentInfo(char name[],
                             char course[],
                             int year,
                             char studentNumber[],
                             char newStudentNumber[])
{
    /*
     * Update student information.
     */

    StudentModel_modifyStudentName(studentNumber, name);
    StudentModel_modifyStudentCourse(studentNumber, course);
    StudentModel_modifyStudentYear(studentNumber, year);
    StudentModel_modifyStudentNumber(studentNumber, newStudentNumber);

    return;
}

void
Controller_addStudentSubject(char studentNumber[],
                             char subject[])
{
    /*
     * Add a subject to a student.
     */

    StudentModel_addStudentSubject(studentNumber, subject);

    return;
}

void
Controller_removeStudentSubject(char studentNumber[],
                                char subjectName[])
{
    /*
     * Remove a subject from a student.
     */

    StudentModel_removeStudentSubject(studentNumber, subjectName);

    return;
}

void
Controller_updateStudentSubjectGrade(char studentNumber[],
                                     char subjectName[],
                                     double subjectGrade)
{
    /*
     * Update student subject grade.
     */

    StudentModel_modifyStudentSubjectGrade(studentNumber,
                                           subjectName,
                                           subjectGrade);

    return;
}

void
Controller_updateSubjectCriteria(char subjectName[],
                                 char subjectCriteria[])
{
    /*
     * Update a subject's criteria.
     */

    char subjectRange[256];
    strcpy(subjectRange, SubjectModel_getSubjectRange(subjectName));

    SubjectModel_modifySubject(subjectName,
                               subjectCriteria,
                               subjectRange);

    return;
}

void
Controller_updateSubjectRange(char subjectName[],
                              char subjectRange[])
{
    /*
     * Update a subject's criteria.
     */

    char subjectCriteria[256];
    strcpy(subjectCriteria, SubjectModel_getSubjectCriteria(subjectName));

    SubjectModel_modifySubject(subjectName,
                               subjectCriteria,
                               subjectRange);

    return;
}

void
Controller_listSubjects()
{
    /*
     * List all subjects.
     */

    SubjectModel_listSubjects();

    return;
}

void
Controller_displayStudentInfo(char studentNumber[])
{
    /*
     * Display the info of a student.
     */

    StudentModel_displayStudentInfo(studentNumber);
}

void
Controller_displayAllStudentInfo()
{
    /*
     * Display all student info.
     */

    StudentModel_displayAllStudentInfo();

    return;
}
