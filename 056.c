#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "bignum.h"

int digit_sum(const char num[]) {
  int sum = 0;
  for (int i = 0; i < SIZE; i++) {
    sum += num[i];
  }
  return sum;
}

int main(void) {
  char num[SIZE], tmp[SIZE];
  int ans = 0, sum;

  for (int a = 1; a < 100; a++) {
    bn_itoa(num, a);
    for (int b = 1; b < 100; b++) {
      bn_multint(tmp, num, a);
      sum = digit_sum(tmp);
      if (sum > ans) {
        ans = sum;
      }
      bn_copy(num, tmp);
    }
  }
  printf("%d\n", ans);
}
