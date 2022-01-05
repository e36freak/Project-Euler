#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int same_digits(long a, long b) {
  int digits[10] = {0};
  while (a > 0) {
    digits[a % 10]++;
    a /= 10;
  }
  while (b > 0) {
    digits[b % 10]--;
    b /= 10;
  }
  for (int i = 0; i < 10; i++) {
    if (digits[i] != 0) {
      return 0;
    }
  }
  return 1;
}

int main(void) {
  long x;

  for (x = 1; x < 999999999999; x++) {
    int flag = 0;
    for (int m = 2; m <= 6; m++) {
      if (!same_digits(x, x * m)) {
        flag = 1;
        break;
      }
    }
    if (flag) {
      continue;
    }
    printf("%ld\n", x);
    return 0;
  }
  return 1;
}
