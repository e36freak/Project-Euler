#include <stdio.h>
#include <math.h>

#define MAX 1000000

struct primes {
  int list[MAX];
  int count;
} primes;

int isprime(int num) {
  int s = sqrt(num);
  for (int i = 0; i < primes.count && primes.list[i] <= s; i++) {
    if (!(num % primes.list[i])) {
      return 0;
    }
  }
  primes.list[primes.count++] = num;
  return 1;
}

int main(void) {
  primes.list[0] = 2; primes.list[1] = 3; primes.list[2] = 5;
  primes.count = 3;
  int product = 30;

  for (int i = 7; i <= MAX; i += 2) {
    if (isprime(i)) {
      if (product * i > MAX) {
        printf("%d\n", product);
        return 0;
      }
      product *= i;
    }
  }
  return 1;
}
