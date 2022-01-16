#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void) {
  int ans = 0;

  ans = 0;
  for (int x = 0; x < 10; x++) {
    int n = 1;
    while (((long)log10((long)pow(x, n)) == n - 1)) {
      ans++;
      n++;
    }
  }
  printf("%d\n", ans);
}
