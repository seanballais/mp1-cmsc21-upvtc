/*
 * Controller.h
 *
 * Links the model to the view and vice versa.
 *
 */

void
Controller_addStudent(string name.
                      string course,
                      int year,
                      string studentNumber,
                      string subjects,
                      string grades)
{
    /*
     * Add a student.
     */

    StudentModel_addStudent(string name,
                            string course,
                            int year,
                            string studentNumber,
                            string subjects,
                            string grades);

    return;
}

void
Controller_addSubject(string subjectName,
                      string subjectCriteria,
                      string subjectRange)
{
    /*
     * Add a subject.
     */

    SubjectModel_addSubject(subjectName, subjectCriteria, subjectRange);
}

void
Controller_removeStudent(string studentNumber)
{
    /*
     * Remove a student.
     */

    StudentModel_removeStudent(studentNumber);

    return;
}

void
Controller_removeSubject(string subjectName)
{
    /*
     * Remove a subject.
     */

    SubjectModel_removeSubject(subjectName);

    return;
}

void
Controller_updateStudentInfo(string name.
                             string course,
                             int year,
                             string studentNumber,
                             string newStudentNumber)
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
Controller_addStudentSubject(string studentNumber,
                             string subject)
{
    /*
     * Add a subject to a student.
     */

    StudentModel_addStudentSubject(studentNumber, subject);

    return;
}

void
Controller_removeStudentSubject(string studentNumber,
                                string subjectName)
{
    /*
     * Remove a subject from a student.
     */

    StudentModel_removeStudentSubject(studentNumber, subjectName);

    return;
}

void
Controller_updateStudentSubjectGrade(string studentNumber,
                                     string subjectName,
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
Controller_updateSubjectCriteria(string subjectName,
                                 string subjectCriteria)
{
    /*
     * Update a subject's criteria.
     */

    string subjectRange = SubjectModel_getSubjectRange(subjectName);

    SubjectModel_modifySubject(subjectName,
                               subjectCriteria,
                               subjectRange);

    return;
}

void
Controller_updateSubjectRange(string subjectName,
                              string subjectRange)
{
    /*
     * Update a subject's criteria.
     */

    string subjectRange = SubjectModel_getSubjectRange(subjectName);

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
Controller_displayStudentInfo(string studentNumber)
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
