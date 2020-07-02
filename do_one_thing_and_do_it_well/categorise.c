
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char line[80];
    FILE* in = fopen("gpsdata.data", "r");
    FILE* f1 = fopen("ufos.csv", "w");
    FILE* f2 = fopen("disappearances.csv", "w");
    FILE* f3 = fopen("others.csv", "w");

    while(fscanf(in, "%79[^\n]\n", line) == 1) {
        if (strstr(line, "UFO"))
            fprintf(f1, "%s\n", line);
        else if (strstr(line, "Disappearance"))
            fprintf(f2, "%s\n", line);
        else
            fprintf(f3, "%s\n", line);
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);
}
