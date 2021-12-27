#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int divide(int n) {
  int dec[1024];
  int num[1024];
  int d, i;

  i = 0;
  d = 1;
  while (d) {
    num[i] = d;
    d *= 10;
    dec[i] = d / n;
    d %= n;
    for (int j = 0; j < i; j++) {
      if (num[j] == num[i] && dec[j] == dec[i]) {
        return i - j;
      }
    }
    i++;
  }
  return 0;
}

int main(void) {
  int len, max = 0;
  int ans;

  for (int i = 2; i <= 1000; i++) {
    if ((len = divide(i)) > max) {
      max = len;
      ans = i;
    }
  }

  printf("%d\n", ans);
}
