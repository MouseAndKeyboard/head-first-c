/*
 * Program to evaluate face values.
 * license and copyright information
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
  char card_name[3];
  puts("Enter the card_name: ");
  scanf("%2s", card_name);
  int val = 0;
  if (card_name[0] == 'K') {
    val = 10;
  } else if (card_name[0] == 'Q') {
    val = 10;
  } else if (card_name[0] == 'J') {
    val = 10;
  } else if (card_name[0] == 'A') {
    val = 11;
  } else {
    val = atoi(card_name);
  }
  printf("The card you selected, %s, has the value: %i\n", card_name, val);

  if ((val > 2) && (val < 7))
    puts("Count has gone up");
  else if (val == 10)
    puts("Count has gone down");

  return 0;
}
