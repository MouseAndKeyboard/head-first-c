
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

        /* Error checking */
        if (lat < -90 || lat > 90) {
            fprintf(stderr, "Latitude %f is outside legal range (-90,90).\n", lat);
            return 2;
        }
        if (lon < -180 || lon > 180) {
            fprintf(stderr, "Longitude %f is outside legal range (-180,180).\n", lon);
            return 2;
        }

        printf("{latitude: %f, longitude: %f, info: '%s'}", lat, lon, info);
       
    }
    puts("\n]");
    return 0;
}
