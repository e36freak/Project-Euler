#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define LMAX 1000

struct primes {
  int list[LMAX];
  int count;
} primes;

void genprime(int n) {
  int i, s;
  s = (int)sqrt(n);
  for (i = 0; i < primes.count && primes.list[i] <= s; i++) {
    if (!(n % primes.list[i])) {
      return;
    }
  }
  primes.list[primes.count++] = n;
}

int isprime(int n) {
  for (int i = 0; i < primes.count && primes.list[i] <= n; i++) {
    if (primes.list[i] == n) {
      return 1;
    }
  }
  return 0;
}

int countprimes(int a, int b) {
  int count = 0;
  for (int n = 0; isprime((n * n) + (a * n) + b); n++) {
    count++;
  }
  return count;
}

int main(void) {
  int max, ma, mb, t;

  // generate list of primes
  primes.list[0] = 2; primes.list[1] = 3; primes.list[2] = 5;
  primes.count = 3;
  for (int i = 3; i <= LMAX; i += 2) {
    genprime(i);
  }

  max = 0;
  for (int a = -999; a < 1000; a++) {
    for (int b = 0; b <= 1000; b++) {
      if ((t = countprimes(a, b)) > max) {
        max = t; ma = a; mb = b;
      }
    }
  }
  printf("%d %d %d\n", max, ma, mb);
  printf("%d\n", ma * mb);
}
