#include <stdio.h>
#include "bignum.h"

// TODO handle negative numbers

void bn_zero(char a[]) {
  for (int i = 0; i < SIZE; i++) {
    a[i] = 0;
  }
}

void bn_itoa(char dest[], long long num) {
  for (int i = 0; i < SIZE; i++) {
    dest[i] = num % 10;
    num /= 10;
  }
}

void bn_copy(char dest[], const char src[]) {
  for (int i = 0; i < SIZE; i++) {
    dest[i] = src[i];
  }
}

void bn_print(const char num[]) {
  int flag = 0;
  for (int i = SIZE - 1; i >= 0; i--) {
    if (num[i] > 0) {
      flag = 1;
    }
    if (flag) {
      printf("%d", num[i]);
    }
  }
  printf("\n");
}

void bn_add(char dest[], const char a[], const char b[]) {
  bn_zero(dest);
  for (int i = 0; i < SIZE; i++) {
    int s = a[i] + b[i];
    int j = i;
    while (s > 0) {
      dest[j++] += s % 10;
      s /= 10;
    }
  }
}

void bn_sub(char dest[], const char a[], const char b[]) {
  char tmp[SIZE];
  bn_zero(dest);
  bn_copy(tmp, a);
  for (int i = 0; i < SIZE; i++) {
    int s = tmp[i] - b[i];
    if (s < 0) {
      s += 10;
      tmp[i+1]--;
    }
    dest[i] = s;
  }
}

void bn_mult(char dest[], const char a[], const char b[]) {
  bn_zero(dest);
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      int m = a[i] * b[j];
      int k = i + j;
      while (m > 0) {
        if ((dest[k] += m % 10) >= 10) {
          dest[k + 1] += dest[k] / 10;
          dest[k] %= 10;
        }
        k++;
        m /= 10;
      }
    }
  }
}

void bn_div(char dest[], const char a[], const char b[]) {
  // TODO
}

int bn_comp(const char a[], const char b[]) {
  for (int i = 0; i < SIZE; i++) {
    if (a[i] > b[i]) {
      return 1;
    } else if (a[i] < b[i]) {
      return -1;
    }
  }
  return 0;
}

