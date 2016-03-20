/*
 * FileUtil.h
 *
 * Abstracts file functions.
 *
 */

#ifndef FILEUTIL_H
#define FILEUTIL_H

    #include <stdio.h>

    FILE* FileUtil_openFile(const char* filename,
                            const string mode);
    void FileUtil_modifyStudentInfoProperty(const int index,
                                            const string studentNumber,
                                            const string newVal,
                                            const char mode);
    void FileUtil_getStudentInfoProperty(const int index,
                                            const string studentNumber);

#endif
