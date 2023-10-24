#include <stdio.h>
#include "../src/person.c"
#include "../src/letter.c"
#include "../src/post.c"

int main() {
    //Person p = createPerson(0, "emirhan", "soylu", "es@g.c", "123");
    //Person p2 = createPerson(1, "olivia", "monster", "om@g.c", "321");
    //Letter letter = createLetter(0, "test", "test", TEMPLATE);
    
    loadAllData();
    printf("Mail: %s\n", users[0].mail);
    printf("Mail: %s\n", users[1].mail);
    //Post post = sendPostman(0, users[0], users[1], letters[0], WHISPER);


    printf("Letter Subject: %s\n", letters[0].subject);
    printf("Post Reciever: %s\n", posts[0].reciever.mail);
    
    return 0;
}