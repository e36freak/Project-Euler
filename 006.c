#include <stdio.h>
#include <math.h>

int main(void) {
  long long sum = 0, square = 0;
  for (int i = 1; i <= 100; i++) {
    sum += i * i;
  }
  for (int i = 1; i <= 100; i++) {
    square += i;
  }
  square *= square;
  printf("%lld\n", square - sum);
}
