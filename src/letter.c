#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/letter.h"

Letter createLetter(int id, char *subject, char *content, Person sender, Person reciever)
{
    Letter letter;
    letter.id = id;
    strcpy(letter.subject, subject);
    strcpy(letter.content, content);
    letter.sender = sender;
    letter.reciever = reciever;

    return letter;
}