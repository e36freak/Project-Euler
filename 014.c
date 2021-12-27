#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int collatz(long n) {
  int steps = 1;
  while (n > 1) {
    if (n % 2) {
      n = (3 * n) + 1;
    } else {
      n /= 2;
    }
    steps++;
  }
  return steps;
}

int main(void) {
  int ans, c, max = 0;
  for (int i = 2; i < 1000000; i++) {
    if ((c = collatz(i)) > max) {
      max = c;
      ans = i;
    }
  }
  printf("%d\n", ans);
}
