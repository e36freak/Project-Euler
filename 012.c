#include <stdio.h>
#include <math.h>

int count_factors(int n) {
  int ret = 0;
  int s = (int)sqrt(n);

  for (int i = 1; i <= s; i++) {
    if (!(n % i)) {
      ret += 2;
    }
  }
  return ret;
}

int main(void) {
  int t = 0;
  int triangle = 0;
  while (1) {
    triangle += (++t);
    if (count_factors(triangle) > 500) {
      printf("%d\n", triangle);
      return 0;
    }
  }
}
