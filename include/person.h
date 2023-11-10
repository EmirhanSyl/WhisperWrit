#ifndef PERSON_H
#define PERSON_H

typedef struct Post Post;
typedef struct Person
{
    int id;
    char firstName[30];
    char lastName[30];
    char mail[50];
    char password[30];
    Person *(*showContentList)(struct Person *);
} Person;

Post *recievedPosts(int id);
Post *sentPosts(int id);
Person *showContentList(struct Person *self);

Person *createPerson(int id, char *name, char *surname, char *password);

#endif