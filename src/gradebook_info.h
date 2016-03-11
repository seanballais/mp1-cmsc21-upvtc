#ifndef SLAMBOOK_INFO_H
#define SLAMBOOK_INFO_H

    typedef enum { ADMIN = 1, TEACHER, STUDENT } roles;

    typedef struct {
        char name[64];
        char nickname[32];
        char age[10];
        char course[10];
        char year[10];
        char studentNumber[20];
    } profile;

#endif
