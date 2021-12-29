#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int cache[10000];

int count_digits(int digits[], int num) {
  int d;
  while (num > 0) {
    d = num % 10;
    if (digits[d]++) {
      return 0;
    }
    num /= 10;
  }
  return 1;
}
  
int is_pandigital(int a, int b, int c) {
  int digits[] = {1, 0, 0, 0, 0, 0, 0, 0, 0, 0};

  if (!count_digits(digits, a)) return 0;
  if (!count_digits(digits, b)) return 0;
  if (!count_digits(digits, c)) return 0;
  for (int i = 0; i < 10; i++) {
    if (digits[i] != 1) return 0;
  }
  return 1;
}

int main(void) {
  int t, ans = 0, p;
  for (int i = 0; i < 10000; i++) {
    cache[i] = 0;
  }
  for (int a = 1; a < 9876; a++) {
    for (int b = a + 1; b < 9876; b++) {
      if ((t = a * b) > 9876) continue;
      p = is_pandigital(a, b, t);
      if (p) {
        cache[t] = p;
        printf("%d * %d = %d\n", a, b, t);
      }
    }
  }
  for (int i = 0; i < 10000; i++) {
    if (cache[i]) ans += i;
  }
  printf("%d\n", ans);
}
