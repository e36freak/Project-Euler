#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int count_combinations(int coins[], int s, int total) {
  int c;
  if (s < 0) {
    return 0;
  }
  if (total == 0) {
    return 1;
  } else if (total < 0) {
    return 0;
  }
  c = 0;
  for (int i = 0; i * coins[s - 1] <= total; i++) {
    c += count_combinations(coins, s - 1, total - (i * coins[s - 1]));
  }
  return c;
}

int main(void) {
  int coins[] = {1, 2, 5, 10, 20, 50, 100, 200};

  printf("%d\n", count_combinations(coins, 8, 200));
}
