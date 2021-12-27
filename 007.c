#include <stdio.h>
#include <math.h>

int isprime(long long n) {
  int i, s;
  if (n <= 3) {
    return 1;
  }
  if (!(n % 2) || !(n % 3)) {
    return 0;
  }
  s = (int)sqrt(n);
  for (i = 5; i <= s; i += 2) {
    if (!(n % i)) {
      return 0;
    }
  }
  return 1;
}

int main(void) {
  long long n = 3;
  int c = 1;
  while (c < 10001) {
    if (isprime(n++)) {
      c++;
    }
  }
  printf("%lld\n", n - 1);
}
