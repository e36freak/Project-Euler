#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define POWER 1000
#define SIZE 512

int main(void) {
  int num[SIZE];
  int t, r, sum;

  for (int d = 0; d < SIZE; d++) {
    num[d] = 0;
  }

  num[0] = 1;
  for (int pow = 1; pow <= POWER; pow++) {
    r = 0;
    for (int d = 0; d < SIZE; d++) {
      t = num[d] * 2 + r;
      r = t / 10;
      t %= 10;
      num[d] = t;
    }
  }
  sum = 0;
  for (int d = 0; d < SIZE; d++) {
    sum += num[d];
  }
  printf("%d\n", sum);
}
