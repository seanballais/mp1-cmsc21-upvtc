#ifndef SLAMBOOK_INFO_H
#define SLAMBOOK_INFO_H

    typedef enum { ADMIN = 1, TEACHER, STUDENT } roles;

    typedef struct {
        char name[128];
        char age[3];
        char course[10];
        char year[5];
        char studentNumber[16];
        double grade;
    } profile;

#endif
