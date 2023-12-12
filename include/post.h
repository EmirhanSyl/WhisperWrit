#ifndef POST_H
#define POST_H
#include "letter.h"
#include "person.h"

typedef enum {NORMAL, WHISPER} MODE;
static const char *const mode_names[];

typedef struct Person Person;
typedef struct Post
{
    int id;
    Person sender;
    Person reciever;
    Letter letter;
    MODE mode;
}Post;

Post sendPostman(int id, Person sender, Person reciever, Letter letter, MODE mode);
int markAsSeen(Post post);
int postLetter(Person *sender, char *recieverMail, Letter createdLetter, int whisperMode);

#endif