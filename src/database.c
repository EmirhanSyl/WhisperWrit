#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/person.h"
#include "../include/letter.h"
#include "../include/post.h"

#define PERSON_BIN "../Database/person.bin"
#define LETTER_BIN "../Database/letter.bin"
#define POST_BIN "../Database/post.bin"

Letter letters[100];
int letterCount;
int biggestLetterId;
Person users[100];
int userCount;
int biggestUserId;
Post posts[500];
int postCount;
int biggestPostId;

int binaryInsertAnyStruct(void *insertElement, int size, char *fileName, int *arrSize)
{
    FILE *file = fopen(fileName, "ab");

    if (file == NULL)
    {
        printf("Error while opening the file!");
        return 1;
    }

    size_t elements_written = fwrite(insertElement, size, 1, file);
    if (elements_written != 1)
    {
        perror("Error writing to file");
        fclose(file);
        return 1;
    }
    *arrSize = *arrSize + 1;

    fclose(file);
    return 0;
}

int binaryReadAnyStruct(void *arr, int size, char *fileName, int *arrSize)
{
    FILE *file = fopen(fileName, "rb");

    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    int i = 0;
    while (fread((char *)arr + i * size, size, 1, file) != 0)
    {
        i++;
    }
    *arrSize = i;

    fclose(file);

    return 0;
}

int binaryDeleteAnyStruct(int deleteElementIndex, void *arr, int *arrSize, int size, char *fileName)
{
    FILE *file = fopen(fileName, "wb");

    if (file == NULL)
    {
        printf("Error while opening the file!");
        return 1;
    }

    for (int i = 0; i < *arrSize; i++)
    {
        if (i == deleteElementIndex)
        {
            continue;
        }

        fwrite((char *)arr + i * size, size, 1, file);
    }

    // Shift elements to overwrite the struct at the specified index
    for (int i = deleteElementIndex; i < (*arrSize) - 1; i++)
    {
        memcpy((char *)arr + i * size, (char *)arr + (i + 1) * size, size);
    }

    *arrSize = *arrSize - 1;

    fclose(file);
    return 0;
}

int binaryUpdateStruct(int updateElementIndex, void *arr, int *arrSize, int size, char *fileName)
{
    memcpy((char *)arr + ((*arrSize) * size), (char *)arr + updateElementIndex * size, size);
    if (binaryInsertAnyStruct((char *)arr + updateElementIndex * size, size, fileName, arrSize) != 0)
    {
        return 1; // Insert operation failed
    }

    if (binaryDeleteAnyStruct(updateElementIndex, arr, arrSize, size, fileName) != 0)
    {
        return 2; // Delete operation failed
    }

    return 0;
}

int loadAllData()
{
    binaryReadAnyStruct((void *)users, sizeof(Person), PERSON_BIN, &userCount);
    binaryReadAnyStruct((void *)letters, sizeof(Letter), LETTER_BIN, &letterCount);
    binaryReadAnyStruct((void *)posts, sizeof(Post), POST_BIN, &postCount);

    biggestUserId = users[0].id;
    for (int i = 0; i < userCount; i++)
    {
        biggestUserId = (users[i].id > biggestUserId) ? users[i].id : biggestUserId;
    }
    biggestLetterId = letters[0].id;
    for (int i = 0; i < letterCount; i++)
    {
        biggestLetterId = (letters[i].id > biggestLetterId) ? letters[i].id : biggestLetterId;
    }
    biggestPostId = posts[0].id;
    for (int i = 0; i < postCount; i++)
    {
        biggestPostId = (posts[i].id > biggestPostId) ? posts[i].id : biggestPostId;
    }

    return 0;
}

Person *login(char *mail, char *psw)
{

    for (int i = 0; i < userCount; i++)
    {
        if (strcmp(users[i].mail, mail) == 0 && strcmp(users[i].password, psw) == 0)
        {
            return &users[i];
        }
    }
    Person *nullP = NULL;
    return nullP;
}

int clearBinaryFile(char *fileName){
    FILE *file = fopen(fileName, "wb");

    if (file == NULL)
    {
        perror("Error opening file");
        return -1;
    }

    fclose(file);
}

int clearDatabase(){
    clearBinaryFile(LETTER_BIN);
    clearBinaryFile(POST_BIN);
    //clearBinaryFile(PERSON_BIN);
}

int findLetterIndex(int id)
{
    for (int i = 0; i < letterCount; i++)
    {
        if (id == letters[i].id)
        {
            return i;
        }
    }
    return -1;
}

int findPostIndex(int id)
{
    for (int i = 0; i < postCount; i++)
    {
        if (id == posts[i].id)
        {
            return i;
        }
    }
    return -1;
}

int findPersonIndex(int id)
{
    for (int i = 0; i < userCount; i++)
    {
        if (id == users[i].id)
        {
            return i;
        }
    }
    return -1;
}