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
                        string subjects,
                        string grades)
{
    /*
     * Append the student to the database.
     */

    FILE *fp = FileUtil_openFile("StudentInfo.txt", "a");

    fprintf(
        fp,
        "%s|%s|%d|%s|%s|%s\n",
        name,
        course,
        year,
        studentNumber,
        subjects,
        grades
    );

    fclose(fp);

    return;
}

void
StudentModel_addStudentSubject(string studentNumber,
                               string subject)
{
    /*
     * Add a subject to a student.
     */

    // Append to the subject list
    FileUtil_modifyStudentInfoProperty(4, studentNumber, subject, 'a');

    // Append to the subject grade list that can be mapped to the subject list
    FileUtil_modifyStudentInfoProperty(5, studentNumber, "0", 'a');
}

void
StudentModel_modifyStudentName(string studentNumber,
                               string name)
{
    /*
     * Modify student name.
     */

    FileUtil_modifyStudentInfoProperty(0, studentNumber, name, 'r');
}

void
StudentModel_modifyStudentCourse(string studentNumber,
                                 string course)
{
    /*
     * Modify the student course.
     */

    FileUtil_modifyStudentInfoProperty(1, studentNumber, studentNumber, 'r');
}

void
StudentModel_modifyStudentYear(string studentNumber,
                               int year)
{
    /*
     * Modify the student year.
     */
    string strYear = NULL;
    sprintf(strYear, "%d", year);

    FileUtil_modifyStudentInfoProperty(2, studentNumber, strYear, 'r');
}

void
StudentModel_modifyStudentNumber(string studentNumber,
                                 string newStudentNumber)
{
    /*
     * Modify the student number.
     */

    FileUtil_modifyStudentInfoProperty(3, studentNumber, newStudentNumber, 'r');
}

void
StudentModel_modifyStudentSubjectGrade(string studentNumber,
                                       string subjectName,
                                       double subjectGrade)
{

}

void StudentModel_removeStudentSubject(string studentNumber,
                                       string subjectName);
void StudentModel_removeStudent(string studentNumber);
