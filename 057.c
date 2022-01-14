#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "bignum.h"

#define EXPANSIONS 1000

int main(void) {
  char numer[SIZE];
  char denom[SIZE];
  char tmp[SIZE], tmp2[SIZE];
  int ans = 0;

  bn_itoa(numer, 1);
  bn_itoa(denom, 2);

  for (int i = 0; i < EXPANSIONS; i++) {
    bn_add(tmp, denom, numer);
    if (bn_length(tmp) > bn_length(denom)) {
      ans++;
    }
    bn_copy(tmp2, denom);
    bn_multint(tmp, denom, 2);
    bn_add(denom, tmp, numer);
    bn_copy(numer, tmp2);
  }

  printf("%d\n", ans);
}
