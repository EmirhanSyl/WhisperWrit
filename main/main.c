#include <stdio.h>
#include <ctype.h>
#include "../src/person.c"
#include "../src/letter.c"
#include "../src/post.c"

void writePostInfo(Post post)
{
    printf("---------------------------\n");
    printf("Letter ID: %d\n", post.id);
    printf("From: %s\n", post.sender.mail);
    printf("To: %s\n", post.reciever.mail);
    printf("Subject: %s\n", post.letter.subject);
    printf("Status: %s\n", status_names[post.letter.status]);
    printf("Type: %s\n", mode_names[post.mode]);
    printf("---------------------------\n");
}

void readPost(Post post){
    printf("---------------------------\n");
    printf("Letter ID: %d\n", post.id);
    printf("From: %s\n", post.sender.mail);
    printf("To: %s\n", post.reciever.mail);
    printf("Subject: %s\n", post.letter.subject);
    printf("Message: %s\n", post.letter.content);
    printf("Type: %s\n", mode_names[post.mode]);
    printf("---------------------------\n");

    post.letter.status = SEEN;
    // Update Letter Logic
    if (post.mode == WHISPER)
    {
        printf("This letter will be destroyed forever!");
        // Remove Post logic... gcc
    }
    
}

int main()
{
    // Person p = createPerson(0, "emirhan", "soylu", "es@g.c", "123");
    // Person p2 = createPerson(1, "olivia", "monster", "om@g.c", "321");
    // Letter letter = createLetter(0, "test", "test", TEMPLATE);

    // printf("Mail: %s\n", users[0].mail);
    // printf("Mail: %s\n", users[1].mail);
    // Post post = sendPostman(0, users[0], users[1], letters[0], WHISPER);
    // Post recieved = recievedPosts(users[1].id)[0];

    // printf("Letter Subject: %s\n", letters[0].subject);
    // printf("Post Sender: %s\n", recieved.sender.mail);

    loadAllData();

    Person *account;
    int option;
    int isLoggedIn = 0;

    while (1)
    {
        printf("Welcome!\n");
        if (isLoggedIn)
        {
            printf("Welcome, %s %s\n", account->firstName, account->lastName);
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

        printf("Select an option: ");
        scanf("%d", &option);

        if (isLoggedIn)
        {
            Post *recieved;
            int recievedPostCount = 0;
            char subject[100];
            char message[500];
            switch (option)
            {
            case 1:
                // Implement create letter
                printf("Subject: \n");
                scanf("%s", subject);

                printf("Message: \n");
                scanf("%s", subject);

                createLetter(letterCount, subject, message, TEMPLATE);
                break;
            case 2:
                // Implement Show Recieved Letters
                recieved = recievedPosts(account->id);
                while (recieved[recievedPostCount].id != -1)
                {
                    writePostInfo(recieved[recievedPostCount]);
                    recievedPostCount++;
                }
                printf("Choose a letter to read (%d - %d): ", 0, recievedPostCount);
                scanf("%d", &option);
                if (option >= 0 && option <= recievedPostCount)
                {
                    readPost(recieved[option]);
                }else{
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
                printf("Choose a letter to read (%d - %d): ", 0, recievedPostCount);
                scanf("%d", &option);
                if (option >= 0 && option <= recievedPostCount)
                {
                    readPost(recieved[option]);
                }
                else
                {
                    printf("Invalid option. Please select %d - %d.\n", 0, recievedPostCount);
                }
                break;
            case 4:
                // Implement Show Template Letters
                break;
            case 5:
                // Implement Show Contact List
                break;
            case 6:
                isLoggedIn = 0;
                break;
            default:
                printf("Invalid option. Please select 1 or 2.\n");
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

                account = createPerson(userCount, firstName, lastName, password);
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