
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int scores[] = {43,323,32,554,11,3,112};
int SCORE_LEN = 7;

int compare_scores(const void* score_a, const void* score_b) {
    int a = *(int*)score_a;
    int b = *(int*)score_b;
    return a - b;
}

int compare_scores_desc(const void* score_a, const void* score_b) {
    int a = *(int*)score_a;
    int b = *(int*)score_b;
    return b - a;
}

typedef struct {
    int width;
    int height;
} rectangle;

int compare_areas(const void* rec_a, const void* rec_b) {
    rectangle *a = (rectangle*)rec_a;
    rectangle *b = (rectangle*)rec_b;

    return a->width * a->height - b->width * b->height;
}

int compare_names(const void* n_a, const void* n_b) {
    char** a = (char**)n_a;
    char** b = (char**)n_b;

    return strcmp(*a, *b);
}

int compare_areas_desc(const void* rec_a, const void* rec_b) {
    return -compare_areas(rec_a, rec_b);
}

int compare_names_desc(const void* n_a, const void* n_b) {
    return -compare_names(n_a, n_b);
}

int main() {
    for (int i=0; i < SCORE_LEN; i++)
        printf("%i ", scores[i]);

    printf("\n");

    qsort(scores, SCORE_LEN, sizeof(int), compare_scores);

    for (int i=0; i < SCORE_LEN; i++)
        printf("%i ", scores[i]);

    printf("\n");


    puts("names in order:");
    char *names[] = {"Karen", "Mark", "Brett", "Molly"};
    qsort(names, 4, sizeof(char*), compare_names);
    for (int i=0; i<4; i++) {
        printf("%s\n", names[i]);
    }

    return 0;
}
