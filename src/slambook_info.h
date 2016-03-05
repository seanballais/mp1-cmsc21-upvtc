#ifndef SLAMBOOK_INFO_H
#define SLAMBOOK_INFO_H

    typedef enum { ADMIN = 1, TEACHER, STUDENT } roles;

    typedef struct {
        char name[64];
        char nickname[32];
        char age[32];
        char course[10];
        char year[2];
        char studentNumber[12];
    } profile;

#endif
