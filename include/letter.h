#ifndef LETTER_H
#define LETTER_H
#include "person.h"

typedef enum {TEMPLATE, SENT} Status;
typedef struct Letter
{
    int id;
    char subject[100];
    char content[500];
    Status status;
    Person sender;
    Person reciever;
} Letter;

Letter createLetter(int id, char *subject, char *content, Person sender, Person reciever);

#endif