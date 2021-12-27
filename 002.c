#include <stdio.h>

int main(void) {
  int a = 1, b = 2, ans = 2;
  int n = 0;

  while (n <= 4000000) {
    n = a + b;
    if (!(n%2)) {
      ans += n;
    }
    a = b; b = n;
  }
  printf("%d\n", ans);
}
