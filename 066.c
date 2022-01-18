#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "bignum.h"

#define MAXD 1000

int issquare(int num) {
  int s = sqrt(num);
  if (s * s == (int)num) {
    return 1;
  }
  return 0;
}

int issolution(char x[], int d, char y[]) {
  char xsqr[SIZE] = {0};
  char ysqr[SIZE] = {0};
  char tmp[SIZE] = {0};
  char res[SIZE] = {0};
  char one[SIZE] = {0};
  bn_itoa(one, 1);

  bn_mult(xsqr, x, x);
  bn_mult(ysqr, y, y);
  bn_multint(tmp, ysqr, d);
  bn_sub(res, xsqr, tmp);

  return bn_comp(res, one) == 0;
}

void find_x(char dest[], int n) {
  int m = 0;
  int d = 1;
  int a0 = sqrt(n);

  int a = a0;
  char numer[SIZE] = {0};
  char prevn[SIZE] = {0};
  char denom[SIZE] = {0};
  char prevd[SIZE] = {0};
  char tmp[SIZE] = {0};
  char tmp2[SIZE] = {0};

  bn_itoa(numer, a0);
  bn_itoa(denom, 1);
  bn_itoa(prevn, 1);
  while (!issolution(numer, n, denom)) {
    m = d * a - m;
    d = (n - m * m) / d;
    a = (a0 + m) / d;

    bn_copy(tmp, numer);
    bn_multint(tmp2, numer, a);
    bn_add(numer, tmp2, prevn);
    bn_copy(prevn, tmp);

    bn_copy(tmp, denom);
    bn_multint(tmp2, denom, a);
    bn_add(denom, tmp2, prevd);
    bn_copy(prevd, tmp);
  }

  bn_copy(dest, numer);
}

int main(void) {
  int ans = 0;
  char xsol[SIZE] = {0};
  char max[SIZE] = {0};

  for (int d = 2; d <= MAXD; d++) {
    if (issquare(d)) {
      continue;
    }
    find_x(xsol, d);
    if (bn_comp(xsol, max) > 0) {
      bn_copy(max, xsol);
      ans = d;
    }
  }

  printf("%d\n", ans);
}
