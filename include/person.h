#ifndef PERSON_H
#define PERSON_H

typedef struct Person
{
    int id;
    char firstName[30];
    char lastName[30];
    char mail[50];
    char password[30];
} Person;

Person createPerson(int id, char *name, char *surname, char *mail, char *password);

#endif