#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define LIMIT 10000

int sum_divisors(int num) {
  int s, divsum;

  divsum = 1;
  s = (int)sqrt(num);
  for (int i = 2; i <= s; i++) {
    if (!(num % i)) {
      divsum += i;
      divsum += (num / i);
    }
  }

  return divsum;
}

int main(void) {
  int sum1, sum2, ans;

  ans = 0;
  for (int i=1; i<=LIMIT; i++) {
    sum1 = sum_divisors(i);
    sum2 = sum_divisors(sum1);
    if (sum2 == i && sum1 != i) {
      ans += i;
    }
  }
  printf("%d\n", ans);
}
