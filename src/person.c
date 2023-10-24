#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/person.h"
#include "database.c"


Person createPerson(int id, char *name, char *surname, char *mail, char *password)
{
    Person person;
    person.id = id;
    strcpy(person.firstName, name);
    strcpy(person.lastName, surname);
    strcpy(person.mail, mail);
    strcpy(person.password, password);

    insertPerson(person);
    loadPersons();
    return person;
}

