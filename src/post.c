#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/post.h"

static const char *const mode_names[] = {
    [NORMAL] = "NORMAL",
    [WHISPER] = "WHISPER"};

Post sendPostman(int id, Person sender, Person reciever, Letter letter,  MODE mode){
    Post post;
    post.id = id;
    post.sender = sender;
    post.reciever = reciever;
    post.letter = letter;
    post.mode = mode;

    posts[postCount] = post;
    binaryInsertAnyStruct((void *)&post, sizeof(Post), POST_BIN, &postCount);
    return post;
}

int markAsSeen(Post post){
    if (post.mode == WHISPER)
    {
        printf("This letter will be destroyed forever!\n");
        binaryDeleteAnyStruct(findLetterIndex(post.letter.id), (void *)letters, &letterCount, sizeof(Letter), LETTER_BIN);
        binaryDeleteAnyStruct(findPostIndex(post.id), (void *)posts, &postCount, sizeof(Post), POST_BIN);
    }
    else
    {
        // Update Letter Logic
        int letterIndex = findLetterIndex(post.letter.id);
        int postIndex = findPostIndex(post.id);

        letters[letterIndex].status = SEEN;
        binaryUpdateStruct(letterIndex, letters, &letterCount, sizeof(Letter), LETTER_BIN);

        posts[postIndex].letter.status = SEEN;
        binaryUpdateStruct(postIndex, posts, &postCount, sizeof(Post), POST_BIN);
    }
    return 0;
}

int postLetter(Person *sender, char *recieverMail, Letter createdLetter, int whisperMode)
{
    MODE mode = (whisperMode) ? WHISPER : NORMAL;
    Person reciever;

    if (strcmp(recieverMail, "null") == 0)
    {
        reciever.id = -1;
        strcpy(reciever.mail, "Template");
        biggestPostId++;
        sendPostman(biggestPostId, *sender, reciever, createdLetter, mode);
        return 0;
    }

    bool isUserExists = false;
    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].mail, recieverMail) == 0)
        {
            reciever = users[i];
            isUserExists = true;
        }
    }
    if (!isUserExists)
    {
        printf("Given mail is not exists!");
        return 1;
    }

    biggestPostId++;
    sendPostman(biggestPostId, *sender, reciever, createdLetter, mode);
    return 0;
}

int editPost(Post post, char *newSubject, char *newMessage, char *recieverMail, int newMode)
{
    MODE mode = (newMode) ? WHISPER : NORMAL;
    printf("Mode: %d\n", mode);
    Person reciever;
    Person sender = post.sender;
    int postID = post.id;
    int letterID = post.letter.id;

    bool isUserExists = false;
    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].mail, recieverMail) == 0)
        {
            reciever = users[i];
            isUserExists = true;
        }
    }
    if (!isUserExists)
    {
        printf("Given mail is not exists!");
        return 1;
    }

    int letterIndex = findLetterIndex(letterID);
    strcpy(letters[letterIndex].subject, newSubject);
    strcpy(letters[letterIndex].content, newMessage);
    letters[letterIndex].status = SENT;
    binaryUpdateStruct(letterIndex, letters, &letterCount, sizeof(Letter), LETTER_BIN);

    int postIndex = findPostIndex(postID);
    posts[postIndex].sender = sender;
    posts[postIndex].reciever = reciever;
    posts[postIndex].letter = letters[letterCount - 1];
    posts[postIndex].mode = mode;
    binaryUpdateStruct(postIndex, posts, &postCount, sizeof(Post), POST_BIN);
    return 0;
}