#ifndef POST_H
#define POST_H
#include "letter.h"
#include "person.h"

typedef enum {NORMAL, WHISPER} MODE;
static const char *const mode_names[];

typedef struct Post
{
    int id;
    Person sender;
    Person reciever;
    Letter letter;
    MODE mode;
}Post;

Post sendPostman(int id, Person sender, Person reciever, Letter letter, MODE mode);

#endif