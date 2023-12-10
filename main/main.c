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

    if (!seen)
    {
        return;
    }

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
}

int postLetter(Person *sender, char *recieverMail, Letter createdLetter, int whisperMode)
{
    MODE mode = (whisperMode) ? WHISPER : NORMAL;
    Person reciever;

    if (strcmp(recieverMail, "null") == 0)
    {
        reciever.id = -1;
        sendPostman(postCount, *sender, reciever, createdLetter, mode);
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

    sendPostman(biggestPostId, *sender, reciever, createdLetter, mode);
    return 0;
}

int editPost(Post post, char *newSubject, char *newMessage, char *recieverMail, int newMode)
{
    MODE mode = (newMode) ? WHISPER : NORMAL;
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

    readPost(posts[postCount - 1], 0);
    return 0;
}

int main()
{
    // char *information[] = {"emirhan", "soylu", "es@g.c", "123"};
    // Person *p = createPerson(0, information);
    //  Person p2 = createPerson(1, "olivia", "monster", "om@g.c", "321");
    //  Letter letter = createLetter(0, "test", "test", TEMPLATE);

    // printf("Mail: %s\n", users[0].mail);
    // printf("Mail: %s\n", users[1].mail);
    // Post post = sendPostman(0, users[0], users[1], letters[0], WHISPER);
    // Post recieved = recievedPosts(users[1].id)[0];

    // printf("Letter Subject: %s\n", letters[0].subject);
    // printf("Post Sender: %s\n", recieved.sender.mail);

    // deleteLetter(1);
    // deletePost(1);

    // printf("%s\n", posts[1].reciever.firstName);
    printf("%d\n", postCount);

    loadAllData();

    Person *account;
    int option;
    int isLoggedIn = 0;

    while (1)
    {
        PRINT_BLUE("Welcome!\n");
        if (isLoggedIn)
        {
            printf("\nWelcome, %s %s\n", account->firstName, account->lastName);
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

                if (option >= 0 && option <= recievedPostCount)
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
                if (option >= 0 && option <= recievedPostCount)
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
                    printf("No recieved Message!\n");
                    break;
                }

                printf("Choose a letter to edit (%d - %d): ", 0, recievedPostCount);
                scanf("%d", &option);
                if (option >= 0 && option <= recievedPostCount)
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
                    scanf("%d", &option);

                    editPost(recieved[option], subject, message, recieverMail, option);
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
                contacts = account->showContactList(account);
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
                account = createPerson(biggestUserId, information);
                biggestUserId++;
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