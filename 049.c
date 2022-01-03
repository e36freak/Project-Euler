#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define SIZE 10000

int isprime[SIZE];

struct primes {
  int list[SIZE];
  int count;
} primes;

void gen_primes() {
  for (int i = 1; i < SIZE; i++) {
    isprime[i] = 0;
  }
  isprime[2] = 1;
  primes.list[primes.count++] = 2;
  for (int i = 3; i < SIZE; i++) {
    int s = sqrt(i);
    int flag = 0;
    for (int j = 0; j < primes.count && primes.list[j] <= s; j++) {
      if (!(i % primes.list[j])) {
        flag = 1;
        break;
      }
    }
    if (flag) {
      continue;
    }
    isprime[i] = 1;
    primes.list[primes.count++] = i;
  }
}

int is_permutation(int a, int b) {
  int list[10];
  for (int i = 0; i < 10; i++) {
    list[i] = 0;
  }
  while (a > 0) {
    list[a % 10]++;
    a /= 10;
  }
  while (b > 0) {
    if (--list[b % 10] < 0) {
      return 0;
    }
    b /= 10;
  }
  return 1;
}


int main(void) {
  gen_primes();
  for (int n = 1111; n < SIZE; n++) {
    if (!isprime[n] || n == 1487) {
      continue;
    }
    for (int a = 1; a < SIZE - n; a++) {
      int flag = 0;
      int num = n;
      for (int i = 0; i < 2; i++) {
        num += a;
        if (!isprime[num] || !is_permutation(n, num)) {
          flag = 1;
          break;
        }
      }
      if (!flag) {
        printf ("%d%d%d\n", n, n + a, n + a + a);
        return 0;
      }
    }
  }
}
