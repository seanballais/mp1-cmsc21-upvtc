/*
 * FileUtil.h
 *
 * Abstracts file functions.
 *
 */

#ifndef FILEUTIL_H
#define FILEUTIL_H

    #include <stdio.h>
    #include <string.h>
    #include <stdbool.h>
    #include <stdlib.h>
    #include <ctype.h>

    // Project headers
    #include "../utils/DataTypeDefinitions.h"

    FILE* FileUtil_openFile(const string filename,
                            const string mode);
    void FileUtil_modifyStudentInfoProperty(const int index,
                                            const string studentNumber,
                                            const string newVal,
                                            const char mode);
    string FileUtil_getStudentInfoProperty(const int index,
                                           const string studentNumber);

#endif
