
#include <stdio.h>
#include <stdlib.h>

int main() {
    float lat;
    float lon;
    char info[80];
    int started = 0;
    puts("data=[");
    while(scanf("%f,%f,%79[^\n]", &lat, &lon, info) == 3) {

        if (started)
            printf(",\n");
        else
            started = 1;

        printf("{latitude: %f, longitude: %f, info: '%s'}", lat, lon, info);
       
    }
    puts("\n]");
    return 0;
}
