#include <stdio.h>
#include <math.h>

#define MAX 2000000

struct primes {
  int list[MAX];
  int count;
} primes;

int isprime(long long n) {
  int i, s;
  if (n <= 3) {
    return 1;
  }
  s = (int)sqrt(n);
  for (i = 0; i < primes.count && primes.list[i] <= s; i++) {
    if (!(n % primes.list[i])) {
      return 0;
    }
  }
  primes.list[primes.count++] = n;
  return 1;
}

int main(void) {
  primes.list[0] = 2; primes.list[1] = 3; primes.list[2] = 5;
  primes.count = 3;
  long ans = 2;

  for (int i = 3; i <= MAX; i+=2) {
    if (isprime(i)) {
      ans += i;
    }
  }
  printf("%ld\n", ans);
}
