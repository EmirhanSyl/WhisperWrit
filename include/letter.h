#ifndef LETTER_H
#define LETTER_H
#include "person.h"

typedef enum {TEMPLATE, SENT, SEEN} Status;
static const char *const status_names[];

typedef struct Letter
{
    int id;
    char subject[100];
    char content[500];
    Status status;
} Letter;

Letter createLetter(int id, char *subject, char *content, Status status);

#endif