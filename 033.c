#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void) {
  int a1, a2, b1, b2;
  int n, d;
  double d1, d2;
  int anum = 1, aden = 1;

  for (int a = 11; a < 99; a++) {
    for (int b = a+1; b < 100; b++) {
      if (!(a % 10) || !(b % 10)) {
        continue;
      }
      d1 = (double)a / (double)b;

      a1 = a / 10; a2 = a % 10;
      b1 = b / 10; b2 = b % 10;
      if (a1 == b1) {
        n = a2; d = b2;
      } else if (a2 == b2) {
        n = a1; d = b1;
      } else if (a1 == b2) {
        n = a2; d = b1;
      } else if (a2 == b1) {
        n = a1; d = b2;
      } else {
        continue;
      }
      d2 = (double)n / (double)d;
      if (d1 == d2) {
        anum *= n; aden *= d;
      }
    }
  }
  for (int i = 2; i < sqrt(anum); i++) {
    while (!(anum % i) && !(aden % i)) {
      anum /= i; aden /= i;
    }
  }
  printf("%d\n", aden);
}
