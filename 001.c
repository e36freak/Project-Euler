#include <stdio.h>

int main(void) {
  int ans = 0;

  for (int i = 0; i < 1000; i++) {
    if (!(i%3) || !(i%5)) {
      ans += i;
    }
  }
  printf("%d\n", ans);
}
