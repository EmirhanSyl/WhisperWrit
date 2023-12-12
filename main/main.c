#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "../src/person.c"
#include "../src/letter.c"
#include "../src/post.c"
#define ANSI_COLOR_BLUE "\x1b[34m"
#define ANSI_COLOR_RESET "\x1b[0m"
#define PRINT_BLUE(str) printf(ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET, str)

void writePostInfo(Post post)
{
    printf("\n---------------------------\n");
    printf("Letter ID: %d\n", post.id);
    printf("From: %s\n", post.sender.mail);
    printf("To: %s\n", post.reciever.mail);
    printf("Subject: %s\n", post.letter.subject);
    printf("Status: %s\n", status_names[post.letter.status]);
    printf("Type: %s\n", mode_names[post.mode]);
    printf("---------------------------\n");
}

void readPost(Post post, int seen)
{
    printf("\n---------------------------\n");
    printf("Letter ID: %d\n", post.id);
    printf("From: %s\n", post.sender.mail);
    printf("To: %s\n", post.reciever.mail);
    printf("Subject: %s\n", post.letter.subject);
    printf("Message: %s\n", post.letter.content);
    printf("Type: %s\n", mode_names[post.mode]);
    printf("---------------------------\n");

    if (seen){ markAsSeen(post); }
}

int main()
{
    //clearDatabase();
    loadAllData();
    printf("%d\n", postCount);
    printf("%d\n", letterCount);

    Person *account;
    int option;
    int isLoggedIn = 0;

    while (1)
    {
        PRINT_BLUE("Welcome!\n");
        if (isLoggedIn)
        {
            printf("\nWelcome, %s\n", account->firstName);
            printf("1- Create Letter\n");
            printf("2- Show Recieved Letters\n");
            printf("3- Show Sent Letters\n");
            printf("4- Show Template Letters\n");
            printf("5- Show Contact List\n");
            printf("6- Logout\n");
        }
        else
        {
            printf("1- Login\n");
            printf("2- Register\n");
            printf("3- Exit\n");
        }

        fflush(stdin);
        printf("Select an option: ");
        scanf("%d", &option);

        if (isLoggedIn)
        {
            Post *recieved;
            Person *contacts;
            Letter *createdLetter;
            Letter *createdPost;
            int recievedPostCount = 0;
            int secondOption = 0;
            int modeNum = 0;
            char subject[100];
            char message[500];
            char recieverMail[50];
            switch (option)
            {
            case 1:
                // Implement create letter
                printf("Subject: ");
                fflush(stdin);
                gets(subject);

                printf("Message: ");
                fflush(stdin);
                gets(message);

                printf("Letter Wrote! Do you want to send it now? (0 - no & 1 - yes): ");
                scanf("%d ", &option);
                fflush(stdin);
                if (option)
                {
                    biggestLetterId++;
                    createdLetter = createLetter(biggestLetterId, subject, message, SENT);
                    fflush(stdin);
                    printf("Reciever Mail: ");
                    scanf("%s", recieverMail);
                    printf("Whisper Mode: (0-Off & 1-On): ");
                    scanf("%d", &option);

                    postLetter(account, recieverMail, *createdLetter, option);
                }
                else
                {
                    createdLetter = createLetter(letterCount, subject, message, TEMPLATE);
                    printf("Letter saved as template. You can sand it later. \n");
                    postLetter(account, "null", *createdLetter, 0);
                }

                break;
            case 2:
                // Implement Show Recieved Letters
                recieved = recievedPosts(account->id);
                while (recieved[recievedPostCount].id != -1)
                {
                    writePostInfo(recieved[recievedPostCount]);
                    recievedPostCount++;
                }

                if (recievedPostCount == 0)
                {
                    printf("No recieved Message\n");
                    break;
                }

                printf("Choose a letter to read (%d - %d): ", 0, recievedPostCount);
                scanf("%d", &option);

                if (option >= 0 && option < recievedPostCount)
                {
                    readPost(recieved[option], 1);
                }
                else
                {
                    printf("Invalid option. Please select %d - %d.\n", 0, recievedPostCount);
                }

                break;
            case 3:
                // Implement Show Sent Letters
                recieved = sentPosts(account->id);
                while (recieved[recievedPostCount].id != -1)
                {
                    writePostInfo(recieved[recievedPostCount]);
                    recievedPostCount++;
                }

                if (recievedPostCount == 0)
                {
                    printf("No recieved Message!\n");
                    break;
                }

                printf("Choose a letter to read (%d - %d): ", 0, recievedPostCount);
                scanf("%d", &option);
                if (option >= 0 && option < recievedPostCount)
                {
                    readPost(recieved[option], 0);
                }
                else
                {
                    printf("Invalid option. Please select %d - %d.\n", 0, recievedPostCount);
                }
                break;
            case 4:
                // Implement Show Template Letters
                recieved = getTemplates(account);
                while (recieved[recievedPostCount].id != -1)
                {
                    readPost(recieved[recievedPostCount], 0);
                    recievedPostCount++;
                }

                if (recievedPostCount == 0)
                {
                    printf("No Template Message!\n");
                    break;
                }

                printf("Choose a letter to edit (%d - %d): ", 0, recievedPostCount);
                scanf("%d", &option);
                if (option >= 0 && option < recievedPostCount)
                {
                    printf("Do you want to edit your letter or destroy it forever? (0-Delete & 1-Edit): ");
                    scanf("%d", &secondOption);
                    if (!secondOption)
                    {
                        // Delete Post
                        binaryDeleteAnyStruct(findLetterIndex(recieved[option].letter.id), (void *)letters, &letterCount, sizeof(Letter), LETTER_BIN);
                        binaryDeleteAnyStruct(findPostIndex(recieved[option].id), (void *)posts, &postCount, sizeof(Post), POST_BIN);

                        printf("Letter DESTROYED Successfully!\n");
                        break;
                    }

                    // Update Post
                    printf("Enter New Subject: ");
                    fflush(stdin);
                    gets(subject);

                    printf("Enter New Message: ");
                    fflush(stdin);
                    gets(message);

                    fflush(stdin);
                    printf("Reciever Mail: ");
                    scanf("%s", recieverMail);
                    printf("Whisper Mode: (0-Off & 1-On): ");
                    scanf("%d", &modeNum);

                    editPost(recieved[option], subject, message, recieverMail, modeNum);
                    readPost(posts[postCount - 1], 0);
                    loadAllData();
                }
                else
                {
                    printf("Invalid option. Please select %d - %d.\n", 0, recievedPostCount);
                }
                break;
            case 5:
                // Implement Show Contact List
                printf("\n---------------------------\n");
                printf("CONTACTS:\n");
                contacts = showContactList(account);
                int z = 0;
                while (contacts[z].id != -1)
                {
                    printf("%s\n", contacts[z].mail);
                    z++;
                }
                printf("---------------------------\n");
                printf("Contact Count Calculated:%d\n", z);
                break;
            case 6:
                isLoggedIn = 0;
                break;
            default:
                printf("Invalid option. Please select [1 - 6].\n");
                break;
            }
        }
        else
        {
            char firstName[30];
            char lastName[30];
            char mail[50];
            char password[30];
            switch (option)
            {
            case 1:

                printf("Enter your mail: ");
                scanf("%s", mail);

                printf("Enter your password: ");
                scanf("%s", password);

                printf("Logging in...\n");
                account = login(mail, password);
                if (account != NULL)
                {
                    printf("Successfuly logged in!\n");
                    isLoggedIn = 1;
                    break;
                }
                else
                {
                    printf("User not found! Please try again.\n");
                    continue;
                }

                break;
            case 2:
                printf("Enter your first name: ");
                scanf("%s", firstName);

                printf("Enter your last name: ");
                scanf("%s", lastName);

                printf("Enter your password: ");
                scanf("%s", password);

                strcpy(mail, firstName);
                strcat(mail, lastName);
                strcat(mail, "@w.w");

                char *information[] = {firstName, lastName, password, mail};
                biggestUserId++;
                account = createPerson(biggestUserId, information);
                printf("Account created succesfully!\n");
                isLoggedIn = 1;
                break;
            case 3:
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Invalid option. Please select 1, 2, or 3.\n");
                break;
            }
        }
    }

    return 0;
}