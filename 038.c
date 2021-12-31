#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX 9876

int is_pan(int n[], int s) {
  int seen[10];
  int i;
  if (s != 9) {
    return 0;
  }
  for (i = 0; i < 10; i++) {
    seen[i] = 0;
  }
  for (i = 0; i < s; i++) {
    if (n[i] == 0 || seen[n[i]]++) {
      return 0;
    }
  }
  return 1;
}

int arrtoi(int n[], int s) {
  int ret = 0, m = 0;
  for (int i = s - 1; i >= 0; i--) {
    ret += n[i] * (int)pow(10, m++);
  }
  return ret;
}

int main(void) {
  int buf[16];
  int b, i, t, num;
  int d, f;
  int max = 0;

  for (int n = 1; n <= MAX; n++) {
    for (i = 0; i < 16; i++) {
      buf[i] = 0;
    }
    b = 0; i = 0;
    while (b < 9) {
      t = n * ++i;
      while (t > 0) {
        d = (int)pow(10, (int)log10(t));
        f = t / d; t -= (f * d);
        buf[b++] = f;
      }
    }
    if (is_pan(buf, b)) {
      num = arrtoi(buf, b);
      if (num > max) max = num;
    }
  }
  printf("%d\n", max);
}
