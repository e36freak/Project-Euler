#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define SIZE 1001

int main(void) {
  int sum;
  int dif = 0;
  int cur = 1;

  sum = cur;
  for (int i = 0; i < SIZE / 2; i++) {
    dif += 2;
    for (int c = 0; c < 4; c++) {
      cur += dif;
      sum += cur;
    }
  }
  printf("%d\n", sum);
}
