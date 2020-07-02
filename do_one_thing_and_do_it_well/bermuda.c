#include <stdio.h>

int main() {
    float lat;
    float lon;
    char info[80];

    while (scanf("%f,%f,%79[^\n]", &lat, &lon, info) == 3) {
        if (lat < 35 && lat > 25 && lon > -76 && lon < -64)
            printf("%f,%f,%s", lat, lon, info);
    }

    return 0;
}
