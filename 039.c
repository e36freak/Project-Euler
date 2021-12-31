#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX 1000

int main(void) {
  int maxp, max = 0;

  for (int p = 1; p <= MAX; p++) {
    int solutions = 0;
    for (int a = 1; a < p - 1; a++) {
      for (int b = a + 1; b < p; b++) {
        int c = p - (a + b);
        if ((a * a) + (b * b) == (c * c)) {
          solutions++;
        }
      }
    }
    if (solutions > max) {
      max = solutions;
      maxp = p;
    }
  }
  printf("%d\n", maxp);
}
