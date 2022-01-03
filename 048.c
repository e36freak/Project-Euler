#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void) {
  long long ans = 0;
  long long num;
  for (int n = 1; n <= 1000; n++) {
    num = n;
    for (int m = 1; m < n; m++) {
      num = (num * n) % 10000000000;
    }
    ans += num;
    ans %= 10000000000;
  }

  printf("%010lld\n", ans);
}
