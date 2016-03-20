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
                            const char* mode);

#endif
