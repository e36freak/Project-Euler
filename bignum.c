#include <stdio.h>
#include "bignum.h"

// TODO handle negative numbers

void bn_zero(char a[]) {
  for (int i = 0; i < SIZE; i++) {
    a[i] = 0;
  }
}

void bn_itoa(char dest[], long long num) {
  for (int i = 0; i < SIZE; i++) {
    dest[i] = num % 10;
    num /= 10;
  }
}

void bn_copy(char dest[], const char src[]) {
  for (int i = 0; i < SIZE; i++) {
    dest[i] = src[i];
  }
}

void bn_print(const char num[]) {
  int flag = 0;
  for (int i = SIZE - 1; i >= 0; i--) {
    if (num[i] > 0) {
      flag = 1;
    }
    if (flag) {
      printf("%d", num[i]);
    }
  }
  printf("\n");
}

void bn_add(char dest[], const char a[], const char b[]) {
  bn_zero(dest);
  for (int i = 0; i < SIZE; i++) {
    int s = dest[i] + a[i] + b[i];
    int j = i;
    while (s > 0) {
      dest[j++] = s % 10;
      s /= 10;
    }
  }
}

void bn_addint(char dest[], const char a[], int b) {
  if (b < 0) {
    bn_subint(dest, a, 0-b);
    return;
  }
  bn_zero(dest);
  int sum = b, rem;
  for (int i = 0; i < SIZE; i++) {
    sum += a[i];
    rem = sum % 10;
    sum /= 10;
    dest[i] = rem;
  }
}

void bn_sub(char dest[], const char a[], const char b[]) {
  char tmp[SIZE];
  bn_zero(dest);
  bn_copy(tmp, a);
  for (int i = 0; i < SIZE; i++) {
    int s = tmp[i] - b[i];
    if (s < 0) {
      s += 10;
      tmp[i+1]--;
    }
    dest[i] = s;
  }
}

void bn_subint(char dest[], const char a[], int b) {
  if (b < 0) {
    bn_addint(dest, a, 0-b);
    return;
  }
  char tmp[SIZE];
  bn_itoa(tmp, b);
  bn_sub(dest, a, tmp);
}

void bn_mult(char dest[], const char a[], const char b[]) {
  bn_zero(dest);
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      int m = a[i] * b[j];
      int k = i + j;
      while (m > 0) {
        if ((dest[k] += m % 10) >= 10) {
          dest[k + 1] += dest[k] / 10;
          dest[k] %= 10;
        }
        k++;
        m /= 10;
      }
    }
  }
}

void bn_multint(char dest[], const char a[], int b) {
  int tmp = 0, j = 0, t = 0;
  bn_zero(dest);
  for (int i = 0; i < SIZE; i++) {
    tmp = a[i] * b;
    j = 0;
    while (tmp > 0) {
      dest[i + j] += tmp % 10;
      if (dest[i + j] >= 10) {
        t = dest[i + j];
        dest[i + j] = t % 10;
        dest[i + j + 1] += t / 10;
      }
      tmp /= 10;
      j++;
    }
  }
}

// return the length
static int div_rev(int dest[], const char n[]) {
  int flag = 0, s = 0;
  for (int i = SIZE - 1; i >= 0; i --) {
    if (n[i]) flag = 1;
    if (flag) {
      dest[s++] = n[i];
    }
  }
  return s;
}

static long long bn_atoi(const char num[]) {
  int mult = 1;
  long long ret = 0;
  long long prev = 0;
  for (int i = 0; i < SIZE; i++) {
    ret += (num[i] * mult);
    mult *= 10;
    if (ret < prev) { // detect overflow
      return -1;
    }
    prev = ret;
  }
  return ret;
}

static void bn_longdiv(char dest[], const char a[], const long long b) {
  int tmp, len;
  char c[SIZE] = {0}, de[SIZE] = {0};
  int d, i;

  tmp = 0; len = 0;
  for (i = SIZE - 1; i >= 0; i--) {
    if (a[i] > 0) len = i;
    if (len) c[i] = a[tmp++];
  }
  len++;
  d = 0; i = 0;
  tmp = c[i];
  while (i < len) {
    while (tmp < b && i < len - 1) {
      de[d++] = 0;
      tmp *= 10;
      tmp += c[++i];
    }
    de[d++] = tmp / b;
    tmp %= b;
    tmp *= 10;
    tmp += c[++i];
  }
  tmp = 0;
  for (i = d - 1; i >= 0; i--) {
    dest[tmp++] = de[i];
  }
}

static int div_round(double num) {
  int n;
  if (num < 0) {
    return (num - (n = (int)num)) < -0.5 ? n - 1 : n;
  } else {
    return (num - (n = (int)num)) >= 0.5 ? n + 1 : n;
  }
}

void bn_div(char dest[], const char a[], const char b[]) {
  bn_zero(dest);
  // try to divide normally first
  long long ai = bn_atoi(a);
  long long bi = bn_atoi(b);
  if (ai > 0 && bi > 0) {
    bn_itoa(dest, ai / bi);
    return;
  }
  // long division with smaller divisor
  if (bi > 0 && bi < 1000000000000) {
    bn_longdiv(dest, a, bi);
    return;
  }

  // fourier division
  int c[SIZE] = {0}, d[SIZE] = {0}; int o[SIZE] = {0};
  char build1[SIZE] = {0}, build2[SIZE] = {0};
  int tmp, rem, alen, blen, rlen, r;

  // determine number of digits in result (truncation)
  alen = div_rev(c, a); blen = div_rev(d, b);
  rlen = alen - blen;
  if (rlen < 0) {
    return;
  } else if (rlen == 0) {
    if (bn_comp(a, b) > 0) {
      rlen = 1;
    } else {
      return;
    }
  } else {
    rlen++;
    for (int i = 0; i < alen && i < blen; i++) {
      if (d[i] < c[i]) {
        break;
      } else if (d[i] > c[i]) {
        rlen -= 1;
        break;
      }
    }
  }
    
  for (int i = 0; i <= alen / 2; i++) {
    c[i] = (c[i*2] * 10) + c[(i*2)+1];
  }
  for (int i = alen / 2 + 1; i < SIZE; i++) {
    c[i] = 0;
  }
  for (int i = 0; i <= blen / 2; i++) {
    d[i] = (d[i*2] * 10) + d[(i*2)+1];
  }
  for (int i = blen / 2 + 1; i < SIZE; i++) {
    d[i] = 0;
  }

  tmp = (c[0] * 100) + c[1];
  o[0] = tmp / d[0];
  rem = tmp % d[0];

  for (int i = 1; i < SIZE; i++) {
    tmp = (rem * 100) + c[i + 1];
    for (int j = 1; j <= i; j++) {
      tmp -= o[i - j] * d[j];
    }
    r = div_round((double)tmp / d[0]);
    o[i] = r;
    rem = tmp - (r * d[0]);
  }

  // handle more than two digits in partial quotient, and negative numbers
  bn_itoa(build1, o[0]);
  for (int i = 1; i < rlen; i++) {
    bn_multint(build2, build1, 100);
    bn_addint(build1, build2, o[i]);
  }

  // truncate and assign to dest
  for (int i = SIZE - 1; i >= 0; i--) {
    if (build1[i] > 0) {
      for (int j = 0; j < rlen; j++) {
        dest[rlen - j - 1] = build1[i - j];
      }
      break;
    }
  }
}

int bn_comp(const char a[], const char b[]) {
  int alen = bn_length(a);
  int blen = bn_length(b);
  if (alen > blen) {
    return 1;
  } else if (alen < blen) {
    return -1;
  }
  for (int i = 0; i < SIZE; i++) {
    if (a[i] > b[i]) {
      return 1;
    } else if (a[i] < b[i]) {
      return -1;
    }
  }
  return 0;
}

int bn_length(const char num[]) {
  for (int i = SIZE - 1; i >= 0; i--) {
    if (num[i] > 0) {
      return i + 1;
    }
  }
  return 0;
}
