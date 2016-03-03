#ifndef FILE_ACCESS_H
#define FILE_ACCESS_H

    #include <stdio.h>

    #include "slambook_info.h"
    #include "linked_list.h"

    void readDataFromFile(FILE *fp, struct node *head);
    void saveDataToFile(FILE *fp, struct node *head);

#endif
