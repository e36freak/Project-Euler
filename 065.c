#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "bignum.h"

#define TARGET 100

/*
K   FRACT   NUMER
1     1         2
2     2         3
3     1         8
4     1        11
5     4        19
6     1        87
7     1       109
8     6       193
9     1      1264
10    1      1457
*/

int main(void) {
  char numer[SIZE];
  char prev[SIZE];
  char tmp[SIZE];
  char tmp2[SIZE];

  bn_itoa(prev, 2);
  bn_itoa(numer, 3);

  int m = 1, fract = 2;
  for (int k = 3; k <= TARGET; k++) {
    bn_copy(tmp2, numer);
    bn_multint(tmp, numer, fract);
    bn_add(numer, tmp, prev);
    bn_copy(prev, tmp2);
    
    if ((k + 1) % 3 == 0) {
      fract = ++m * 2;
    } else {
      fract = 1;
    }
  }

  printf("%d\n", bn_sumdigits(numer));
}
