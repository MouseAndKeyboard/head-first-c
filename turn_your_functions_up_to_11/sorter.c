
#include <stdio.h>
#include <stdlib.h>

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

int main() {
    for (int i=0; i < SCORE_LEN; i++)
        printf("%i ", scores[i]);

    printf("\n");

    qsort(scores, SCORE_LEN, sizeof(int), compare_scores);

    for (int i=0; i < SCORE_LEN; i++)
        printf("%i ", scores[i]);

    printf("\n");
    return 0;
}
