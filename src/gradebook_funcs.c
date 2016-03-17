#include "gradebook_funcs.h"

void
printEntry(profile personInfo)
{
    printf("Name: %s\n", personInfo.name);
    printf("Age: %s\n", personInfo.age);
    printf("Student Number: %s\n", personInfo.studentNumber);
    printf("Course and Year: %s %s\n", personInfo.course, personInfo.year);
    printf("---\n");
}

void
getInput(profile *personInfo)
{
    printf("Name: ");
    strcpy(personInfo->name, GetString());

    printf("Age: ");
    strcpy(personInfo->age, GetString());

    printf("Course: ");
    strcpy(personInfo->course, GetString());

    printf("Year: ");
    strcpy(personInfo->year, GetString());

    printf("Student Number: ");
    strcpy(personInfo->studentNumber, GetString());

    printf("Student data entered successfully.\n");
}

void
printMenu(roles role)
{
    printf("GRADING BOOK Menu\n");

    int optionNum = 0;
    if (role == ADMIN) {
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

// Copied from the CS50 Library
char*
GetString(void)
{
    // growable buffer for chars
    string buffer = NULL;

    // capacity of buffer
    unsigned int capacity = 0;

    // number of chars actually in buffer
    unsigned int n = 0;

    // character read or EOF
    int c;

    // iteratively get chars from standard input
    while ((c = fgetc(stdin)) != '\n' && c != EOF)
    {
        // grow buffer if necessary
        if (n + 1 > capacity)
        {
            // determine new capacity: start at CAPACITY then double
            if (capacity == 0)
                capacity = CAPACITY;
            else if (capacity <= (UINT_MAX / 2))
                capacity *= 2;
            else
            {
                free(buffer);
                return NULL;
            }

            // extend buffer's capacity
            string temp = realloc(buffer, capacity * sizeof(char));
            if (temp == NULL)
            {
                free(buffer);
                return NULL;
            }
            buffer = temp;
        }

        // append current character to buffer
        buffer[n++] = c;
    }

    // return NULL if user provided no input
    if (n == 0 && c == EOF)
        return NULL;

    // minimize buffer
    string minimal = malloc((n + 1) * sizeof(char));
    strncpy(minimal, buffer, n);
    free(buffer);

    // terminate string
    minimal[n] = '\0';

    // return string
    return minimal;
}

// Copied from the CS50 Library
int
GetInt(void)
{
    // try to get an int from user
    while (true)
    {
        // get line of text, returning INT_MAX on failure
        string line = GetString();
        if (line == NULL)
            return INT_MAX;

        // return an int if only an int (possibly with
        // leading and/or trailing whitespace) was provided
        int n;
        char c;
        if (sscanf(line, " %d %c", &n, &c) == 1)
        {
            free(line);
            return n;
        }
        else
        {
            free(line);
            printf("Retry: ");
        }
    }
}

// Copied from the CS50 Library
double
GetDouble(void)
{
    // try to get a double from user
    while (true)
    {
        // get line of text, returning DBL_MAX on failure
        string line = GetString();
        if (line == NULL)
            return DBL_MAX;

        // return a double if only a double (possibly with
        // leading and/or trailing whitespace) was provided
        double d; char c;
        if (sscanf(line, " %lf %c", &d, &c) == 1)
        {
            free(line);
            return d;
        }
        else
        {
            free(line);
            printf("Retry: ");
        }
    }
}
