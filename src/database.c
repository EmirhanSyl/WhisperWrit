#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/person.h"
#include "../include/letter.h"


static Letter letters[100];
static Person users[100];


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

int loadPersons(){
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
            printf("Value: %s\n", value);
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
    
   
}