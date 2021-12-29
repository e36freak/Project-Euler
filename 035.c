#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX 1000000

int cache[MAX];
struct primes {
  int list[MAX];
  int count;
} primes;

int isprime(int n) {
  int s;
  if (n <= 3) {
    return 1;
  }
  s = (int)sqrt(n);
  for (int i = 0; i < primes.count && primes.list[i] <= s; i++) {
    if (!(n % primes.list[i])) {
      return 0;
    }
  }
  primes.list[primes.count++] = n;
  return 1;
}

int getmult(int n) {
  int mult = MAX;
  while (n < mult) {
    mult /= 10;
  }
  return mult;
}

int main(void) {
  int r, d, t, m;
  int flag, ans;

  primes.list[0] = 2; primes.list[1] = 3; primes.list[2] = 5;
  primes.count = 3;
  for (int i = 2; i < MAX; i++) {
    cache[i] = isprime(i);
  }

  ans = 0;
  for (int n = 2; n < MAX; n++) {
    flag = 1;
    m = getmult(n); r = n;
    do {
      if (!cache[r]) {
        flag = 0;
        break;
      }
      d = r % 10; t = r / 10;
      r = (d * m) + t;
    } while (r != n);
    if (flag) {
      ans++;
    }
  }
  printf("%d\n", ans);
}
