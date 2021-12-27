#include <stdio.h>
#include <math.h>

int rev(int n) {
  int ret = 0;
  while (n > 0) {
    ret *= 10;
    ret += n % 10;
    n /= 10;
  }
  return ret;
}

int main(void) {
  int ans = 0;
  int n;
  for (int a = 100; a < 1000; a++) {
    for (int b = 100; b < 1000; b++) {
      n = a * b;
      if (n == rev(n) && n > ans) {
        ans = n;
      }
    }
  }

  printf("%d\n", ans);
}
