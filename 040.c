#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX 1000000

int nth_digit(int num, int n) {
  int d, ret = 1;
  for (int i = 0; i < n; i++) {
    d = (int)pow(10, (int)log10(num));
    ret = num / d;
    num -= ret * d;
  }
  return ret;
}

int main(void) {
  int place = 0;
  int mult = 0;
  int ans = 1;
  int target, p;

  for (int i = 1; i <= MAX; i++) {
    int digits = (int)log10(i) + 1;
    place += digits;

    if (place >= (target = (int)pow(10, mult))) {
      p = digits - (place % target);
      ans *= nth_digit(i, p);
      mult++;
    }
  }
  printf("%d\n", ans);
}
