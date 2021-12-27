#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define UPPER_BOUND 28123

void clear_arr(int arr[]) {
  for (int i = 0; i < UPPER_BOUND; i++) {
    arr[i] = 0;
  }
}

int sum_divisors(int num) {
  int s, divsum;

  divsum = 1;
  s = (int)sqrt(num);
  for (int i = 2; i <= s; i++) {
    if (!(num % i)) {
      divsum += i;
      if (i != num / i) {
        divsum += (num / i);
      }
    }
  }

  return divsum;
}

int main(void) {
  int abundant[UPPER_BOUND];
  int ans = 0;
  int divsum;
  int is_sum;

  clear_arr(abundant);

  for (int i = 12; i < UPPER_BOUND; i++) {
    if ((divsum = sum_divisors(i)) > i) {
      abundant[i] = 1;
    }
  }

  for (int i = 1; i <= UPPER_BOUND; i++) {
    is_sum = 0;
    for (int j = 12; j <= i / 2; j++) {
      if (abundant[j] && abundant[i - j]) {
        is_sum = 1;
        break;
      }
    }
    if (!is_sum) {
      ans += i;
    }
  }

  printf("%d\n", ans);

}
