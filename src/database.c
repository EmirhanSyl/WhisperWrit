#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/person.h"
#include "../include/letter.h"
#include "../include/post.h"

static Letter letters[100];
static int letterCount;
static Person users[100];
static int userCount;
static Post posts[500];
static int postCount;

int insertPerson(Person person)
{
    FILE *file = fopen("../Database/person.txt", "a");

    if (file == NULL)
    {
        printf("Error while opening the file!");
        return 1;
    }

    fprintf(file, "ID:%d\n", person.id);
    fprintf(file, "First Name:%s\n", person.firstName);
    fprintf(file, "Last Name:%s\n", person.lastName);
    fprintf(file, "Mail:%s\n", person.mail);
    fprintf(file, "Password:%s\n", person.password);

    fclose(file);
    return 0;
}

int loadPersons()
{
    FILE *file = fopen("../Database/person.txt", "r");

    if (file == NULL)
    {
        printf("Error while opening the file!");
        return 1;
    }

    Person *person;
    char chunk[128];
    int lineNum = 0;
    int personCount = 0;
    while (fgets(chunk, sizeof(chunk), file) != NULL)
    {
        char *colon_pos = strchr(chunk, ':');
        char *value;
        if (colon_pos != NULL)
        {
            value = colon_pos + 1;
            size_t newline_pos = strcspn(value, "\n");
            value[newline_pos] = '\0';
        }

        switch (lineNum)
        {
        case 0:
            person = (Person *)malloc(sizeof(Person));
            person->id = atoi(value);
            lineNum++;
            break;
        case 1:
            strcpy(person->firstName, value);
            lineNum++;
            break;
        case 2:
            strcpy(person->lastName, value);
            lineNum++;
            break;
        case 3:
            strcpy(person->mail, value);
            lineNum++;
            break;
        case 4:
            strcpy(person->password, value);
            users[personCount] = *person;
            lineNum = 0;
            personCount++;
            break;
        default:
            break;
        }
    }
    userCount = personCount;
    printf("Persons Loaded\n");
    return 0;
}

int insertLetter(Letter letter)
{
    FILE *file = fopen("../Database/letter.txt", "a");

    if (file == NULL)
    {
        printf("Error while opening the file!");
        return 1;
    }

    fprintf(file, "ID:%d\n", letter.id);
    fprintf(file, "Subject:%s\n", letter.subject);
    fprintf(file, "Content:%s\n", letter.content);
    fprintf(file, "Status:%s\n", status_names[letter.status]);

    fclose(file);
    return 0;
}

int loadLetters()
{
    FILE *file = fopen("../Database/letter.txt", "r");

    if (file == NULL)
    {
        printf("Error while opening the file!");
        return 1;
    }

    Letter *letter;
    char chunk[512];
    int lineNum = 0;
    while (fgets(chunk, sizeof(chunk), file) != NULL)
    {
        char *colon_pos = strchr(chunk, ':');
        char *value;
        if (colon_pos != NULL)
        {
            value = colon_pos + 1;
            size_t newline_pos = strcspn(value, "\n");
            value[newline_pos] = '\0';
        }

        switch (lineNum)
        {
        case 0:
            letter = (Letter *)malloc(sizeof(Letter));
            letter->id = atoi(value);
            lineNum++;
            break;
        case 1:
            strcpy(letter->subject, value);
            lineNum++;
            break;
        case 2:
            strcpy(letter->content, value);
            lineNum++;
            break;
        case 3:
            if (value == status_names[TEMPLATE])
            {
                letter->status = TEMPLATE;
            }
            else if (value == status_names[SENT])
            {
                letter->status = SENT;
            }
            else
            {
                letter->status = SEEN;
            }
            letters[letterCount] = *letter;
            lineNum = 0;
            letterCount++;
            break;
        default:
            break;
        }
    }
    printf("Letters Loaded\n");
    return 0;
}

int insertPostman(Post postman)
{
    FILE *file = fopen("../Database/post.txt", "a");

    if (file == NULL)
    {
        printf("Error while opening the file!");
        return 1;
    }

    fprintf(file, "ID:%d\n", postman.id);
    fprintf(file, "Sender ID:%d\n", postman.sender.id);
    fprintf(file, "Reciever ID:%d\n", postman.reciever.id);
    fprintf(file, "Letter ID:%d\n", postman.letter.id);
    fprintf(file, "Mode:%s\n", mode_names[postman.mode]);

    fclose(file);
    return 0;
}

int loadPosts()
{
    FILE *file = fopen("../Database/post.txt", "r");

    if (file == NULL)
    {
        printf("Error while opening the file!");
        return 1;
    }
    Person findPersonById(int id);
    Letter findLetterById(int id);

    Post *post;
    char chunk[512];
    int lineNum = 0;
    while (fgets(chunk, sizeof(chunk), file) != NULL)
    {
        char *colon_pos = strchr(chunk, ':');
        char *value;
        if (colon_pos != NULL)
        {
            value = colon_pos + 1;
            size_t newline_pos = strcspn(value, "\n");
            value[newline_pos] = '\0';
        }

        switch (lineNum)
        {
        case 0:
            post = (Post *)malloc(sizeof(Post));
            post->id = atoi(value);
            lineNum++;
            break;
        case 1:
            post->sender = findPersonById(atoi(value));
            lineNum++;
            break;
        case 2:
            post->reciever = findPersonById(atoi(value));
            lineNum++;
            break;
        case 3:
            post->letter = findLetterById(atoi(value));
            lineNum++;
            break;
        case 4:
            if (value == mode_names[NORMAL])
            {
                post->mode = NORMAL;
            }
            else if (value == status_names[WHISPER])
            {
                post->mode = WHISPER;
            }
            else
            {
                post->mode = NORMAL;
            }
            posts[postCount] = *post;
            lineNum = 0;
            postCount++;
            break;
        default:
            break;
        }
    }
    printf("Posts Loaded\n");
    return 0;
}

Person findPersonById(int id)
{
    for (int i = 0; i < userCount; i++)
    {
        if (users[i].id == id)
        {
            return users[i];
        }
    }
}

Letter findLetterById(int id)
{
    for (int i = 0; i < letterCount; i++)
    {
        if (letters[i].id == id)
        {
            return letters[i];
        }
    }
}

int loadAllData(){
    loadPersons();
    loadLetters();
    loadPosts();
    return 0;
}