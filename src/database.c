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

int binaryInsertAnyStruct(void *insertElement, int size, char *fileName)
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

    fclose(file);
    return 0;
}

int binaryReadAnyStruct(void *arr, int size, char *fileName)
{
    FILE *file = fopen(fileName, "rb");

    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    int i = 0;
    while (fread(&arr[i], sizeof(Person), 1, file) != 0)
    {
        i++;
    }

    fclose(file);

    return 0;
}

int binaryInsertPerson(Person person){
    FILE *file = fopen("../Database/person.bin", "ab");

    if (file == NULL)
    {
        printf("Error while opening the file!");
        return 1;
    }

    size_t elements_written = fwrite(&person, sizeof(Person), 1, file);
    if (elements_written != 1)
    {
        perror("Error writing to file");
        fclose(file);
        return 1;
    }

    fclose(file);
}

Person *binaryReadPerson()
{
    Person *people = calloc(10, sizeof(Person));
    // Open the binary file for reading
    FILE *file = fopen("../Database/person.bin", "rb");

    if (file == NULL)
    {
        perror("Error opening file");
        return NULL;
    }

    // Read the struct from the file
    int i = 0;
    while (fread(&people[i], sizeof(Person), 1, file) != 0)
    {
        i++;
    }
    
    // Close the file
    fclose(file);

    return people;
}



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
            person->showContactList = showContactList;
            person->getTemplates = getTemplates;
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
    letterCount = 0;
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
            if (strcmp(value, status_names[TEMPLATE]) == 0)
            {
                letter->status = TEMPLATE;
            }
            else if (strcmp(value, status_names[SENT]) == 0)
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
    fclose(file);
    printf("Letters Loaded\n");
    return 0;
}

int deleteLetter(int id)
{
    FILE *file = fopen("../Database/letter.txt", "r");
    FILE *temp = fopen("../Database/temp.txt", "w");

    if (file == NULL || temp == NULL)
    {
        printf("Error while opening the file!");
        return 1;
    }

    Letter *letter;
    char chunk[512];
    int lineNum = 0;
    bool skipLetter = false;
    letterCount = 0;
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
            if (atoi(value) == id)
            {
                skipLetter = true;
                lineNum++;
                break;
            }
            
            letter = (Letter *)malloc(sizeof(Letter));
            letter->id = atoi(value);
            fprintf(temp, "ID:%d\n", letter->id);
            lineNum++;
            break;
        case 1:
            if (skipLetter)
            {
                lineNum++;
                break;
            }

            strcpy(letter->subject, value);
            fprintf(temp, "Subject:%s\n", letter->subject);
            lineNum++;
            break;
        case 2:
            if (skipLetter)
            {
                lineNum++;
                break;
            }

            strcpy(letter->content, value);
            fprintf(temp, "Content:%s\n", letter->content);
            lineNum++;
            break;
        case 3:
            if (skipLetter)
            {
                skipLetter = false;
                lineNum = 0;
                break;
            }
            if (strcmp(value, status_names[TEMPLATE]) == 0)
            {
                letter->status = TEMPLATE;
            }
            else if (strcmp(value, status_names[SENT]) == 0)
            {
                letter->status = SENT;
            }
            else
            {
                letter->status = SEEN;
            }
            fprintf(temp, "Status:%s\n", status_names[letter->status]);
            letters[letterCount] = *letter;
            lineNum = 0;
            letterCount++;
            break;
        default:
            break;
        }
    }

    fclose(file);
    fclose(temp);

    remove("../Database/letter.txt");
    rename("../Database/temp.txt", "../Database/letter.txt");


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
    Person *findPersonById(int id);
    Letter findLetterById(int id);

    Person templatePerson = {.id = -1, .mail = "template"};
    Post *post;
    char chunk[512];
    int lineNum = 0;
    postCount = 0;
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
            post->sender = *findPersonById(atoi(value));
            lineNum++;
            break;
        case 2:
            post->reciever = (findPersonById(atoi(value)) == NULL) ? templatePerson : *findPersonById(atoi(value));
            lineNum++;
            break;
        case 3:
            post->letter = findLetterById(atoi(value));
            lineNum++;
            break;
        case 4:
            if (strcmp(value, mode_names[NORMAL]) == 0)
            {
                post->mode = NORMAL;
            }
            else if (strcmp(value, mode_names[WHISPER]) == 0)
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

    fclose(file);
    printf("Posts Loaded\n");
    return 0;
}

int deletePost(int id)
{
    FILE *file = fopen("../Database/post.txt", "r");
    FILE *temp = fopen("../Database/temp.txt", "w");

    if (file == NULL || temp == NULL)
    {
        printf("Error while opening the file!");
        return 1;
    }

    Person *findPersonById(int id);
    Letter findLetterById(int id);

    Person templatePerson = {.id = -1, .mail = "template"};

    Post *post;
    char chunk[512];
    int lineNum = 0;
    bool skipPost = false;
    letterCount = 0;
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
            if (atoi(value) == id)
            {
                skipPost = true;
                lineNum++;
                break;
            }

            post = (Post *)malloc(sizeof(Post));
            post->id = atoi(value);
            fprintf(temp, "ID:%d\n", post->id);
            lineNum++;
            break;
        case 1:
            if (skipPost)
            {
                lineNum++;
                break;
            }

            post->sender = *findPersonById(atoi(value));
            fprintf(temp, "Sender ID:%s\n", value);
            lineNum++;
            break;
        case 2:
            if (skipPost)
            {
                lineNum++;
                break;
            }

            post->reciever = (findPersonById(atoi(value)) == NULL) ? templatePerson : *findPersonById(atoi(value));
            fprintf(temp, "Reciever ID:%s\n", value);
            lineNum++;
            break;
        case 3:
            if (skipPost)
            {
                lineNum++;
                break;
            }

            post->letter = findLetterById(atoi(value));
            fprintf(temp, "Letter ID:%s\n", value);
            lineNum++;
            break;
        case 4:
            if (skipPost)
            {
                skipPost = false;
                lineNum = 0;
                break;
            }
            if (strcmp(value, mode_names[NORMAL]) == 0)
            {
                post->mode = NORMAL;
            }
            else if (strcmp(value, mode_names[WHISPER]) == 0)
            {
                post->mode = WHISPER;
            }
            else
            {
                post->mode = NORMAL;
            }
            fprintf(temp, "Mode:%s\n", value);
            posts[postCount] = *post;
            lineNum = 0;
            postCount++;
            break;
        default:
            break;
        }
    }

    fclose(file);
    fclose(temp);

    remove("../Database/post.txt");
    rename("../Database/temp.txt", "../Database/post.txt");

    return 0;
}

Person *findPersonById(int id)
{
    for (int i = 0; i < userCount; i++)
    {
        if (users[i].id == id)
        {
            return &users[i];
        }
    }
    Person *nullP = NULL;
    return nullP;
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

int loadAllData()
{
    loadPersons();
    loadLetters();
    loadPosts();
    return 0;
}