#include <stdio.h>
#include <math.h>

int is_triplet(int a, int b, int c) {
  return (a * a) + (b * b) == (c * c);
}

int main(void) {
  for (int c = 0; c < 1000; c++) {
    for (int b = 0; b < c; b++) {
      for (int a = 0; a < b; a++) {
        if (a + b + c != 1000) {
          continue;
        }
        if (is_triplet(a, b, c)) {
          printf("%d\n", a * b * c);
          return 0;
        }
      }
    }
  }
  return 1;
}
