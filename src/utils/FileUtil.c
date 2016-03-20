/*
 * FileUtil.h
 *
 * Abstracts file functions.
 *
 */

#include "FileUtil.h"

FILE*
FileUtil_openFile(const char* filename,
         const char* mode)
{
    /*
     * Opens the file and handles any errors.
     */

    FILE *fp = fopen(filename, mode);
    if (fp == NULL) {
        printf("Error! File %s not found.\n", filename);
        exit(EXIT_FAILURE);
    }

    return fp;
}
