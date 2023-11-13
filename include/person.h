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
    struct Person *(*showContactList)(struct Person *);
    Post *(*getTemplates)(struct Person *);
} Person;

Post *recievedPosts(int id);
Post *sentPosts(int id);
struct Person *showContactList(struct Person *self);
Post *getTemplates(struct Person *self);

Person *createPerson(int id, char *name, char *surname, char *password);

#endif