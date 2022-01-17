#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10000

int calc_period(int num) {
  int m = 0;
  int d = 1;
  int a0 = sqrt(num);

  if (a0 * a0 == num) {
    return 0;
  }

  int a = a0;
  int p = 0;
  
  do {
    m = d * a - m;
    d = (num - m * m) / d;
    a = (a0 + m) / d;
    p++;
  } while (a != 2 * a0);

  return p;
}

int main(void) {
  int ans = 0;
  for (int i = 2; i <= MAX; i++) {
    if (calc_period(i) % 2) {
      ans++;
    }
  }
  printf("%d\n", ans);
}
