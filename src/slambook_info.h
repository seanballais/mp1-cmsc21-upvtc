#ifndef SLAMBOOK_INFO_H
#define SLAMBOOK_INFO_H

    typedef enum { ADMIN = 1, TEACHER, STUDENT } roles;

    typedef struct {
        char name[64];
        char nickname[32];
        char age[32];
        char course[7];
        char year[1];
        char studentNumber[10];
    } profile;

#endif
