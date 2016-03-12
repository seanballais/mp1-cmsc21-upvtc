#ifndef SLAMBOOK_FUNCS_H
#define SLAMBOOK_FUNCS_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <stdbool.h>
    #include <limits.h>
    #include <float.h>

    #include "gradebook_info.h"

    #define CAPACITY 128
    typedef char* string;

    void printEntry(profile personInfo);
    void getInput(profile *personInfo);
    void _removeNewline(char* input);
    void printMenu(roles role);
    char* GetString(void);
    int GetInt(void);
    double GetDouble(void);

#endif
