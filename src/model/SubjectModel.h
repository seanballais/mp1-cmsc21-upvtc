/*
 * StudentModel.h
 *
 * Handles data manipulation with respect to the subject.
 *
 */

#ifndef SUBJECTMODEL_H
#define SUBJECTMODEL_H

    #include <stdio.h>
    #include <string.h>

    // Project headers
    #include "../utils/DataTypeDefinitions.h"
    #include "FileHandler.h"

    void SubjectModel_addSubject(string subjectName,
                                 string subjectCriteria,
                                 string subjectRange);
    void SubjectModel_modifySubject(string subjectName,
                                    string subjectCriteria,
                                    string subjectRange);
    void SubjectModel_removeSubject(string subjectName);
    string SubjectModel_getSubjectCriteria(string subjectName);
    string SubjectModel_getSubjectRange(string subjectName);

#endif
