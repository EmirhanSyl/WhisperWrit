#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/person.h"
#include "database.c"

Post *recievedPosts(int id)
{
    Post *recievedPostsArr = (Post *)malloc(100 * sizeof(Post)); // Allocate memory on the heap

    if (recievedPostsArr == NULL)
    {
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < postCount; i++)
    {
        if (posts[i].reciever.id == id)
        {
            recievedPostsArr[count] = posts[i];
            count++;
        }
    }

    return recievedPostsArr;
}

Post *sentPosts(int id)
{
    Post *recievedPostsArr = (Post *)malloc(100 * sizeof(Post)); // Allocate memory on the heap

    if (recievedPostsArr == NULL)
    {
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < postCount; i++)
    {
        if (posts[i].sender.id == id)
        {
            recievedPostsArr[count] = posts[i];
            count++;
        }
    }

    return recievedPostsArr;
}

void removeSpaces(char *str)
{
    int i, j = 0;
    for (i = 0; str[i]; i++)
    {
        if (str[i] != ' ')
        {
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

Person *createPerson(int id, char *name, char *surname, char *password)
{
    Person *person = (Person *)malloc(sizeof(Person));
    person->id = id;
    strcpy(person->firstName, name);
    strcpy(person->lastName, surname);


    for (int i = 0; i < strlen(name); i++)
    {
        name[i] = tolower(name[i]);
    }
    for (int i = 0; i < strlen(surname); i++)
    {
        surname[i] = tolower(surname[i]);
    }
    removeSpaces(name);
    removeSpaces(surname);
    char *mail = name;
    strcat(mail, surname);
    strcat(mail, "@w.w");

    strcpy(person->mail, mail);
    strcpy(person->password, password);

    insertPerson(*person);
    loadPersons();
    return person;
}
