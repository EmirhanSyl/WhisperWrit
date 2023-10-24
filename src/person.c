#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
