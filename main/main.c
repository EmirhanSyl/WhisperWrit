#include <stdio.h>
#include "../src/person.c"
#include "../src/letter.c"

int main() {
    //Person p = createPerson(0, "emirhan", "soylu", "es@g.c", "123");
    //Person p2 = createPerson(1, "olivia", "monster", "om@g.c", "321");
    //Letter letter = createLetter(0, "test", "test", p, p2);
    
    loadPersons();
    printf("Mail: %s\n", users[0].mail);
    printf("Mail: %s\n", users[1].mail);
    return 0;
}