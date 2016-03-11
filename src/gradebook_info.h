#ifndef SLAMBOOK_INFO_H
#define SLAMBOOK_INFO_H

    typedef enum { ADMIN = 1, TEACHER, STUDENT } roles;

    typedef struct {
        char name[129];
        char nickname[17];
        char age[3];
        char course[11];
        char year[5];
        char studentNumber[17];
    } profile;

#endif
