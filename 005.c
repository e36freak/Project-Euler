#include <stdio.h>
#include <math.h>

int main(void) {
  long long ans = 20;

  while (1) {
    int bad = 0;
    for (int i = 1; i <= 20; i++) {
      if (ans % i) {
        bad = 1;
        break;
      }
    }
    if (!bad) {
      break;
    }
    ans += 20;
  }
  printf("%lld\n", ans);
}
