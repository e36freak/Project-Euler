#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX 10000000

int fact(int n) {
  int ret = 1;
  for (int i = 1; i <= n; i++) {
    ret = ret * i;
  }
  return ret;
}
  
int main(void) {
  int sum, n, d;
  int ans = 0;
  int factorials[10];
  for (int i = 0; i < 10; i++) {
    factorials[i] = fact(i);
  }

  for (int i = 3; i < 2540161; i++) {
    sum = 0; n = i;
    while (n > 0) {
      d = n % 10; n /= 10;
      sum += factorials[d];
    }
    if (sum == i) {
      ans += i;
    }
  }
  printf("%d\n", ans);
}
