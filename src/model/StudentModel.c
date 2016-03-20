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
        "|%s|%s|%d|%s|%s|%s|\n",
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

void StudentModel_addStudentSubject(string studentNumber,
                                    string subject)
{
    /*
     * Add a subject to a student.
     */

    // Locate the student number
    FILE *fp = FileUtil_openFile("StudentInfo.txt", "r+");

}

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
void StudentModel_removeStudentSubject(string studentNumber,
                                       string subjectName);
void StudentModel_removeStudent(string studentNumber);
