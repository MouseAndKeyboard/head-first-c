
#include <stdio.h>


enum response_type {DUMP, SECOND_CHANCE, MARRIAGE};
typedef struct {
    char *name;
    enum response_type type;
} response;

void dump(char *n) {
    printf("Dear %s,\n", n);
    puts("Unfortunately your last date contacted us to");
    puts("say that they will not be seeing you again");
}

void second_chance(char *n) {
    printf("Dear %s,\n", n);
    puts("Good news: your last date has asked us to");
    puts("arrange another meeting. Please call ASAP");
}

void marriage(char *n) {
    printf("Dear %s,\n", n);
    puts("Congratulations! Your last date has contacted");
    puts("us with a proposal of marriage");
}

int main() {
    response r[] = { {"Mike", DUMP}, {"Luis", SECOND_CHANCE}, {"Matt", SECOND_CHANCE}, {"William", MARRIAGE} };

    int i;
    for (i=0; i<4; i++) {
        switch (r[i].type) {
            case DUMP:
                dump(r[i].name);
                break;
            case SECOND_CHANCE:
                second_chance(r[i].name);
                break;
            case MARRIAGE:
                marriage(r[i].name);
                break;
        }

       

    }
    return 0;
}
