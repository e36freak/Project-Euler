#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define SIZE 1024

void clear_arr(int arr[]) {
  for (int i = 0; i < SIZE; i++) {
    arr[i] = 0;
  }
}

void copy(int arr2[], int arr1[]) {
  clear_arr(arr2);
  for (int i = 0; i < SIZE; i++) {
    arr2[i] = arr1[i];
  }
}

void add(int a[], int b[], int c[]) {
  int r, s, t;

  clear_arr(c);
  r = 0;
  for (int i = 0; i < SIZE; i++) {
    t = a[i] + b[i] + r;
    s = t % 10; r = t / 10;
    c[i] = s;
  }
}

int count_digits(int a[]) {
  for (int i = SIZE - 1; i >= 0; i--) {
    if (a[i]) {
      return i + 1;
    }
  }
  return 0;
}

int main(void) {
  int a[SIZE], b[SIZE], c[SIZE];
  int index = 2;

  clear_arr(a); clear_arr(b);;
  a[0] = 1; b[0] = 1;

  while (count_digits(b) < 1000) {
    add(a, b, c);
    copy(a, b);
    copy(b, c);
    index++;
  }

  printf("%d\n", index);
}
