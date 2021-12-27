#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define SIZE 256
#define FACTORIAL 100

void clear_arr(int arr[]) {
  for (int i = 0; i < SIZE; i++) {
    arr[i] = 0;
  }
}

void arr_cpy(int arr2[], int arr1[]) {
  clear_arr(arr2);
  for (int i = 0; i < SIZE; i++) {
    arr2[i] = arr1[i];
  }
}

void print(int arr[]) {
  int flag = 0;
  for (int i = SIZE-1; i >= 0; i--) {
    if (arr[i]) {
      flag = 1;
    }
    if (flag) {
      printf("%d", arr[i]);
    }
  }
  printf("\n");
}

void mult(int arr[], int m, int res[]) {
  int tmp = 0, j = 0, a = 0;
  clear_arr(res);
  for (int i = 0; i < SIZE; i++) {
    tmp = arr[i] * m;
    j = 0;
    while (tmp > 0) {
      res[i + j] += tmp % 10;
      if (res[i + j] >= 10) {
        a = res[i + j];
        res[i + j] = a % 10;
        res[i + j + 1] += a / 10;
      }
      tmp /= 10;
      j++;
    }
  }
}

int main(void) {
  int fact[SIZE];
  int res[SIZE];
  int ans = 0;

  clear_arr(fact);
  fact[0] = 1;
  for (int i = 1; i <= FACTORIAL; i++) {
    mult(fact, i, res);
    arr_cpy(fact, res);
  }
//  print(fact);
  for (int i = 0; i < SIZE; i++) {
    ans += fact[i];
  }
  printf("%d\n", ans);
}
