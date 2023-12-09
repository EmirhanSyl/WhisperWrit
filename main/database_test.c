#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "../src/person.c"
#include "../src/letter.c"
#include "../src/post.c"

int insertPersonTest(){
    Person p = {.id = 8, .firstName = "Sare", .lastName = "dsds", .mail = "fdkşlsfk", .password = "fd", .getTemplates = getTemplates, .showContactList = showContactList};
    Person p2 = {.id = 9, .firstName = "Zahed", .lastName = "ghj", .mail = "khgj", .password = "ghj", .getTemplates = getTemplates, .showContactList = showContactList};
    binaryInsertAnyStruct(&p, sizeof(Person), "../Database/person.bin", &userCount);
    binaryInsertAnyStruct(&p2, sizeof(Person), "../Database/person.bin", &userCount);
}
int readPersonTest()
{
    binaryReadAnyStruct((void*)users, sizeof(Person), "../Database/person.bin", &userCount);

    printf("%s\n", users[0].firstName);
    printf("%s\n", users[1].firstName);
}



int insertLetterTest()
{
    Letter l1 = {.id=0, .subject="Hi", .content="Some Message", .status=TEMPLATE};
    Letter l2 = {.id=1, .subject="Hi again", .content="Some Message", .status=SENT};
    binaryInsertAnyStruct(&l1, sizeof(Letter), "../Database/letter.bin", &letterCount);
    binaryInsertAnyStruct(&l2, sizeof(Letter), "../Database/letter.bin", &letterCount);
}
int readLetterTest()
{
    binaryReadAnyStruct((void *)letters, sizeof(Letter), "../Database/letter.bin", &letterCount);

    printf("%s\n", status_names[letters[0].status]);
    printf("%s\n", status_names[letters[1].status]);
}


int insertPostTest()
{
    Post post1 = {.id = 0, .sender = users[0], .reciever = users[1], .letter = letters[0], .mode = WHISPER};
    Post post2 = {.id = 1, .sender = users[1], .reciever = users[0], .letter = letters[1], .mode = NORMAL};
    binaryInsertAnyStruct(&post1, sizeof(Post), "../Database/post.bin", &postCount);
    binaryInsertAnyStruct(&post2, sizeof(Post), "../Database/post.bin", &postCount);
}
int readPostTest()
{
    binaryReadAnyStruct((void *)posts, sizeof(Post), "../Database/post.bin", &postCount);

    printf("%s\n", posts[0].id);
    printf("%s\n", posts[1].id);
}
int deletePostTest()
{
    printf("%d\n", postCount);
    for (int i = 0; i < postCount; i++)
    {
        if (posts[i].id == 0)
        {
            posts[i].mode = NORMAL;
            binaryUpdateStruct(i, (void *)posts, &postCount, sizeof(Post), "../Database/post.bin");
        }
    }
    printf("%d\n", postCount);
}
updatePostTest(){
    
    for (int i = 0; i < postCount; i++)
    {
        if (posts[i].id == 0)
        {
            printf("%s\n", posts[i].letter.content);
            posts[i].letter = letters[1];
            binaryUpdateStruct(i, (void *)posts, &postCount, sizeof(Post), "../Database/post.bin");
            printf("%s\n", posts[i].letter.content);
        }
    }
}

int main() {
    printf("Hello, World!\n");
    return 0;
}