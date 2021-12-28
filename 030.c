#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void) {
  int powers[10];
  int tmp, r, t;
  int ans = 0;
  for (int i = 0; i < 10; i++) {
    powers[i] = pow(i, 5);
  }

  for (int i = 2; i < 1000000; i++) {
    r = i; t = i;
    tmp = i;
    while (t > 0) {
      r = t % 10; t = t / 10;
      if ((tmp -= powers[r]) < 0) {
        break;
      }
    }
    if (tmp == 0) {
      ans += i;
    }
  }
  printf("%d\n", ans);
}
