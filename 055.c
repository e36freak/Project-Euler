#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "bignum.h"

int is_palindrome(char num[]) {
  int len = 0;
  for (int i = SIZE - 1; i >= 0; i--) {
    if (num[i] > 0) {
      len = i + 1;
      break;
    }
  }
  for (int i = 0; i < len / 2; i++) {
    if (num[i] != num[len-i-1]) {
      return 0;
    }
  }
  return 1;
}

void reverse(char dest[], char num[]) {
  bn_zero(dest);
  int len = 0;
  for (int i = SIZE - 1; i >= 0; i--) {
    if (num[i] > 0) {
      len = i + 1;
      break;
    }
  }
  int j = 0;
  for (int i = len - 1; i >= 0; i--) {
    dest[j++] = num[i];
  }
}

int main(void) {
  char tmp[SIZE], num[SIZE], rev[SIZE];
  int ans = 0;

  for (int i = 100; i < 10000; i++) {
    int palindrome = 0;
    bn_itoa(num, i);
    for (int j = 0; j < 50; j++) {
      reverse(rev, num);
      bn_add(tmp, num, rev);
      if (is_palindrome(tmp)) {
        palindrome = 1;
        break;
      }
      bn_copy(num, tmp);
    }
    if (!palindrome) {
      ans++;
    }
  }
  printf("%d\n", ans);
}
