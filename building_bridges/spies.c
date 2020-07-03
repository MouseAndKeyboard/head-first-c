
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char *message;
    struct node *no;
    struct node *yes;
} node;

node* create(char *message) {
    node *n = malloc(sizeof(node));
    n->message = strdup(message);
    n->no = NULL;
    n->yes = NULL;
    return n;
}

void release(node *root) {
    if (root) {
        if (root->no)
            release(root->no);
        if (root->yes)
            release(root->yes);
        if (root->message)
            free(root->message);
        free(root);
    }
}

int yes_no(char* query) {
    printf("%s? (y/n): ", query);
    char answer[3];
    fgets(answer, 3, stdin);
    return answer[0] == 'y';
}

int main() {

    char question[80];
    char suspect[20];
    node *start_node = create("Does the suspect have a mustache");
    start_node->no = create("Loretta Barnsworth");
    start_node->yes = create("Vinny the Spoon");

    node *current;
    do {
        current = start_node;

        while(1) {
            if (yes_no(current->message)) {
                if (current->yes) {
                    current = current->yes;
                } else {
                    printf("SUSPECT IDENTIFIED!\n");
                    break;
                }
            } else if (current->no) {
                current = current->no;
            } else {

                printf("Who's the suspect? ");
                fgets(suspect, 20, stdin);
                node *yes_node = create(suspect);
                current->yes = yes_node;

                node *no_node = create(current->message);
                current->no = no_node;

                printf("Give me a question which is TRUE for %s but FALSE for %s: ", suspect, current->message);
                fgets(question, 79, stdin);
                free(current->message);
                current->message = strdup(question);

                break;
            }
        }

    } while (yes_no("Run again"));

    release(start_node);

    return 0;
}
