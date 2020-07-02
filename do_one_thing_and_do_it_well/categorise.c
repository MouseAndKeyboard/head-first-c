
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* args[]) {

    if (argc != 6) {
        fprintf(stderr, "Needs 5 arguments!\n");
        return 1;
    }

    char line[80];
    FILE* in;
    if (!(in = fopen("gpsdata.data", "r"))) {
        fprintf(stderr, "Can't open the reading file.\n");
        return 1;
    }
    FILE* f1 = fopen(args[2], "w");
    FILE* f2 = fopen(args[4], "w");
    FILE* f3 = fopen(args[5], "w");

    while(fscanf(in, "%79[^\n]\n", line) == 1) {
        if (strstr(line, args[1]))
            fprintf(f1, "%s\n", line);
        else if (strstr(line, args[3]))
            fprintf(f2, "%s\n", line);
        else
            fprintf(f3, "%s\n", line);
    }

    fclose(f1);
    fclose(f2);
    fclose(f3);
}
