#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define TARGET 1000000

void dump(int arr[], int size) {
  for (int i = 0; i < size; i++) {
    printf("%d", arr[i]);
  }
  printf("\n");
}

int permute(int arr[], int digits[], int s, int p, int * tot) {
  int seen;
  for (int i = 0; i < s; i++) {
    seen = 0;
    for (int j = p-1; j >= 0; j--) {
      if (digits[i] == arr[j]) {
        seen = 1;
        break;
      }
    }
    if (seen) {
      continue;
    }

    arr[p] = digits[i];

    if (p == s - 1) {
      (*tot)++;
      if (*tot == TARGET) {
        dump(arr, s);
        return 1;
      }
    } else {
      if (permute(arr, digits, s, p + 1, tot)) {
        return 1;
      }
    }
  }
  return 0;
}

int main(void) {
  int digits[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  int arr[10];
  int total = 0;

  return !permute(arr, digits, 10, 0, &total);
}
