#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX 1000000

int isprime[MAX];

struct primes {
  int list[MAX];
  int count;
} primes;

void gen_primes() {
  for (int i = 1; i < MAX; i++) {
    isprime[i] = 0;
  }
  isprime[2] = 1;
  primes.list[primes.count++] = 2;
  for (int i = 3; i < MAX; i++) {
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

int main(void) {
  int max_len = 0;
  int ans;
  gen_primes();
  for (int p = 0; p < primes.count; p++) {
    int len = 0;
    int sum = primes.list[p];
    for (int n = p + 1; n < primes.count && sum <= MAX; n++) {
      sum += primes.list[n];
      len++;
      if (sum <= MAX && isprime[sum] && len > max_len) {
        max_len = len;
        ans = sum;
      }
    }
  }
  printf("%d\n", ans);
}
