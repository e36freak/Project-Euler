#include <stdio.h>
#include <math.h>

int main(void) {
  long long num = 600851475143;

  for (int i = 3; i < sqrt(num); i += 2) {
    while (!(num % i)) {
      num /= i;
    }
  }
  printf("%lld\n", num);
}
