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
    Post lastPost;
    lastPost.id = -1;
    recievedPostsArr[count] = lastPost;

    return recievedPostsArr;
}

Post *sentPosts(int id)
{
    Post *sentPosts = (Post *)malloc(100 * sizeof(Post)); // Allocate memory on the heap
    if (sentPosts == NULL)
    {
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < postCount; i++)
    {
        if (posts[i].reciever.id != -1 && posts[i].sender.id == id)
        {
            sentPosts[count] = posts[i];
            count++;
        }
    }

    Post lastPost;
    lastPost.id = -1;
    sentPosts[count] = lastPost;
    return sentPosts;
}

Post *getTemplates(struct Person *self){
    Post *templatePosts = (Post *)malloc(100 * sizeof(Post)); // Allocate memory on the heap
    if (templatePosts == NULL)
    {
        return NULL;
    }

    int count = 0;
    for (int i = 0; i < postCount; i++)
    {
        if (posts[i].reciever.id == -1 && posts[i].sender.id == self->id)
        {
            templatePosts[count] = posts[i];
            count++;
        }
    }

    Post lastPost;
    lastPost.id = -1;
    templatePosts[count] = lastPost;
    return templatePosts;
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

struct Person *showContactList(struct Person *self)
{
    Post *recieved = recievedPosts(self->id);
    Post *sent = sentPosts(self->id);
    Person *contactList = malloc(sizeof(Person) * 50); 
    int contactCount = 0;
    int i = 0;
    while (recieved[i].id != -1)
    {
        bool isExists = false;
        for (int i = 0; i < contactCount; i++)
        {
            if (contactList[i].id == recieved[i].sender.id)
            {
                isExists = true;
            }
        }
        
        if (!isExists)
        {
            contactList[contactCount] = recieved[i].sender;
            contactCount++;
        }
        i++;
    }

    i = 0;
    while (sent[i].id != -1)
    {
        bool isExists = false;
        for (int i = 0; i < contactCount; i++)
        {
            if (contactList[i].id == sent[i].reciever.id)
            {
                isExists = true;
            }
        }

        if (!isExists)
        {
            contactList[contactCount] = sent[i].reciever;
            contactCount++;
        }
        i++;
    }

    Person last = {.id = -1};
    contactList[contactCount] = last;
    return contactList;
}

Person *createPerson(int id, char *informations[])
{
    Person *person = (Person *)malloc(sizeof(Person));
    person->id = id;
    
    char *name = informations[0];
    char *surname = informations[1];
    char *password = informations[2];
    char *mail = informations[3];

    strcpy(person->firstName, name);
    strcpy(person->lastName, surname);

    strcpy(person->mail, mail);
    strcpy(person->password, password);
    person->showContactList = showContactList;
    person->getTemplates = getTemplates;

    insertPerson(*person);
    loadPersons();
    return person;
}

char *createMail(char *name, char *surname){
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

    return mail;
}
