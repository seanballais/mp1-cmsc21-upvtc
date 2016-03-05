#include "slambook_funcs.h"

void
printEntry(profile personInfo)
{
    printf("Name: %s\n", personInfo.name);
    printf("Nickname: %s\n", personInfo.nickname);
    printf("Age: %s\n", personInfo.age);
    printf("Student Number: %s\n", personInfo.studentNumber);
    printf("Course and Year: %s %s\n", personInfo.course, personInfo.year);
    printf("---\n");
}

void
getInput(profile *personInfo)
{
    printf("New Entry\n");

    printf("Name: ");
    fgets(personInfo->name, sizeof(personInfo->name), stdin);
    _removeNewline(personInfo->name);

    printf("Nickname: ");
    fgets(personInfo->nickname, sizeof(personInfo->nickname), stdin);
    _removeNewline(personInfo->nickname);

    printf("Age: ");
    fgets(personInfo->age, sizeof(personInfo->age), stdin);
    _removeNewline(personInfo->age);

    printf("Course: ");
    fgets(personInfo->course, sizeof(personInfo->course), stdin);
    _removeNewline(personInfo->course);

    printf("Year: ");
    fgets(personInfo->year, sizeof(personInfo->year), stdin);
    _removeNewline(personInfo->year);

    printf("Student Number: ");
    fgets(personInfo->studentNumber, sizeof(personInfo->studentNumber), stdin);
    _removeNewline(personInfo->studentNumber);

    printf("Student data entered successfully.\n");
}

void
_removeNewline(char* input)
{
    char *pos;
    if ((pos = strchr(input, '\n')) != NULL) {
        *pos = '\0';
    }
}

void
printMenu(roles role)
{
    printf("GRADINGBOOK Menu\n");

    int optionNum = 0;
    if (role != STUDENT) {
        optionNum++;
        printf("    %d) Add\n", optionNum);
    }

    if (role == ADMIN || role == TEACHER) {
        optionNum++;
        printf("    %d) Update\n", optionNum);
    }

    if (role == ADMIN) {
        optionNum++;
        printf("    %d) Delete\n", optionNum);
    }

    optionNum++;
    printf("    %d) Display\n", optionNum);

    optionNum++;
    printf("    %d) Exit\n", optionNum);
    printf("Input: ");
}
