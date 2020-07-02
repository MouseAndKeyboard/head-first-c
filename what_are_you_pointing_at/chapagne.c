
#include <stdio.h>
#include <stdlib.h>

int main() {
    int stock = 180;
    char order_string[3];
    int order;
    while (stock > 0) {
        printf("%i remaining glasses.\n", stock);
        scanf("%2s", order_string);
        order = atoi(order_string);
        stock = stock - order;
        printf("You ordered %i glasses.\n", order);
    }
    puts("We're out of stock");
    return 0;
}
