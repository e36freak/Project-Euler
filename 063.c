#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void) {
  int ans = 0;
  int low = 0;
  int n = 1;

  while (low < 10) {
    low = (int)ceil(pow(10, ((double)n - 1) / n));
    ans += 10 - low;
    n++;
  }
  printf("%d\n", ans);
}
