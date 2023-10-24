#include <stdio.h>
#include "../src/person.c"
#include "../src/letter.c"
#include "../src/post.c"

int main() {
    //Person p = createPerson(0, "emirhan", "soylu", "es@g.c", "123");
    //Person p2 = createPerson(1, "olivia", "monster", "om@g.c", "321");
    //Letter letter = createLetter(0, "test", "test", TEMPLATE);
    
    //printf("Mail: %s\n", users[0].mail);
    //printf("Mail: %s\n", users[1].mail);
    //Post post = sendPostman(0, users[0], users[1], letters[0], WHISPER);
    //Post recieved = recievedPosts(users[1].id)[0];

    //printf("Letter Subject: %s\n", letters[0].subject);
    //printf("Post Sender: %s\n", recieved.sender.mail);

    loadAllData();
    
    int option;
    int isLoggedIn = 0; // A flag to track if the user is logged in

    while (1)
    {
        printf("Welcome!\n");
        if (isLoggedIn)
        {
            printf("Welcome, $username\n");
            printf("1- Create Letter\n");
            printf("2- Logout\n");
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
            // Handle options after login (e.g., create letter, logout)
            switch (option)
            {
            case 1:
                // Implement create letter
                break;
            case 2:
                isLoggedIn = 0;
                break;
            default:
                printf("Invalid option. Please select 1 or 2.\n");
                break;
            }
        }
        else
        {
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
                Person account = login(mail, password);
                if (account.mail != '\0')
                {
                    printf("Successfuly logged in!\n");
                }else{
                    printf("User not found! Please try again.\n");
                    continue;
                }
                
                break;
            case 2:
                // Implement register
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

    return 0;
}