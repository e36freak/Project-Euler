#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define PERMUTATIONS 3628800

int isdivisible(int arr[]) {
  int primes[] = {2, 3, 5, 7, 11, 13, 17};
  int p = 0;

  for (int i = 1; i < 8; i++) {
    int num = arr[i] * 100 + arr[i+1] * 10 + arr[i+2];
    if (num % primes[p++]) {
      return 0;
    }
  }
  return 1;
}

long arrtoi(int arr[]) {
  long ret = 0;
  int mult = 0;
  for (int i = 9; i >= 0; i--) {
    ret += arr[i] * pow(10, mult++);
  }
  return ret;
}

void permute(int arr[], int digits[], int seen[], int p, long * tot) {
  int tmp[10];

  for (int i = 0; i < 10; i++) {
    if (seen[i]) {
      continue;
    }
    arr[p] = digits[i];
    if (p == 9) {
      if (isdivisible(arr)) {
        (*tot) += arrtoi(arr);
      }
    } else {
      for (int i = 0; i < 10; i++) {
        tmp[i] = seen[i];
      }
      tmp[digits[i]] = 1;
      permute(arr, digits, tmp, p+1, tot);
    }
  }
}

int main(void) {
  int num[10];
  int digits[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int seen[10];
  long ans = 0;
  for (int i = 0; i < 10; i++) {
    seen[i] = 0;
  }
  permute(num, digits, seen, 0, &ans);
  printf("%ld\n", ans);
}
