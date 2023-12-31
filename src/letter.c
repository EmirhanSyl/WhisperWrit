#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/letter.h"

static const char *const status_names[] = {
    [TEMPLATE] = "TEMPLATE",
    [SENT] = "SENT",
    [SEEN] = "SEEN"};

Letter *createLetter(int id, char *subject, char *content, Status status)
{
    Letter *letter = malloc(sizeof(Letter));
    letter->id = id;
    strcpy(letter->subject, subject);
    strcpy(letter->content, content);
    letter->status = status;

    letters[letterCount] = *letter;
    binaryInsertAnyStruct((void *)letter, sizeof(Letter), LETTER_BIN, &letterCount);
    return letter;
}

