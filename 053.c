#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "bignum.h"

#define THRESH 1000000

char factorials[101][SIZE];

void gen_factorials() {
  char num[SIZE] = {0};

  bn_zero(factorials[0]);
  factorials[0][0] = 1;
  bn_zero(factorials[1]);
  factorials[1][0] = 1;

  for (int n = 2; n <= 100; n++) {
    bn_itoa(num, n);
    bn_mult(factorials[n], factorials[n-1], num);
  }
}
int main(void) {
  char thresh[SIZE] = {0};
  char nfact[SIZE], rfact[SIZE], tmp[SIZE], tmp2[SIZE];
  int ans = 0;
  bn_itoa(thresh, THRESH);
  gen_factorials();

  for (int n = 1; n <= 100; n++) {
    bn_copy(nfact, factorials[n]);
    for (int r = 0; r <= n; r++) {
      bn_copy(rfact, factorials[r]);
      bn_copy(tmp, factorials[n - r]);
      bn_mult(tmp2, tmp, rfact);
      bn_div(tmp, nfact, tmp2);

      if (bn_comp(tmp, thresh) > 0) {
        ans++;
      }
    }
  }
  printf("%d\n", ans);
}

