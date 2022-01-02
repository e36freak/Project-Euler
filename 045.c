#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(void) {
  long t = 40755, p = 40755, h = 40755;
  long tn = 285, pn = 165, hn = 143;

  while (1) {
    tn++;
    t = (tn * (tn + 1)) / 2;
    while (p < t) {
      pn++;
      p = (pn * (3 * pn - 1)) / 2;
    }
    if (p != t) {
      continue;
    }
    while (h < t) {
      hn++;
      h = (hn * (2 * hn -1));
    }
    if (h != t) {
      continue;
    }
    printf("%ld\n", t);
    return 0;
  }
}
