#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10000
#define LIMIT 6

int inarr(int h[], int len, int n) {
  for (int i = 0; i < len; i++) {
    if (h[i] == n) {
      return 1;
    }
  }
  return 0;
}

int find_cycle(char *ispoly[], char haspoly[], int seen[], int slen, int num) {
  char ptmp[LIMIT] = {0};
  int suffix = num % 100;
  int ans;

  if (suffix < 11) {
    return 0;
  }
  if (slen == LIMIT) {
    if (suffix == (seen[0] / 100)) {
      ans = 0;
      for (int i = 0; i < LIMIT; i++) {
        printf("%d ", seen[i]);
        ans += seen[i];
      }
      printf("\n");
      return ans;
    }
    return 0;
  }

  for (int i = 10; i < 100; i++) {
    int combined = suffix * 100 + i;
    if (inarr(seen, slen, combined)) {
      continue;
    }
    for (int p = 0; p < LIMIT; p++) {
      if (haspoly[p]) {
        continue;
      }
      if (*(ispoly[p]+combined) == 1) {
        memcpy(ptmp, haspoly, LIMIT);
        ptmp[p] = 1;
        seen[slen] = combined;
        if ((ans = find_cycle(ispoly, ptmp, seen, slen + 1, combined))) {
          return ans;
        }
      }
    }
  }
  return 0;
}

int main(void) {
  int p;
  char istriangle[SIZE] = {0}; p = 0;
  for (int i = 1; (p = i * (i + 1) / 2) < SIZE; i++) {
    istriangle[p] = 1;
  }
  char issquare[SIZE] = {0}; p = 0;
  for (int i = 1; (p = i * i) < SIZE; i++) {
    issquare[p] = 1;
  }
  char ispenta[SIZE] = {0}; p = 0;
  for (int i = 1; (p = i * ((3 * i) - 1) / 2) < SIZE; i++) {
    ispenta[p] = 1;
  }
  char ishexa[SIZE] = {0}; p = 0;
  for (int i = 1; (p = i * ((2 * i) - 1)) < SIZE; i++) {
    ishexa[p] = 1;
  }
  char ishepta[SIZE] = {0}; p = 0;
  for (int i = 1; (p = i * ((5 * i) - 3) / 2) < SIZE; i++) {
    ishepta[p] = 1;
  }
  char isocta[SIZE] = {0}; p = 0;
  for (int i = 1; (p = i * ((3 * i) - 2)) < SIZE; i++) {
    isocta[p] = 1;
  }

  char *ispoly[LIMIT];
  ispoly[0] = istriangle; ispoly[1] = issquare;
  ispoly[2] = ispenta;    ispoly[3] = ishexa;
  ispoly[4] = ishepta;    ispoly[5] = isocta;

  char zeroes[LIMIT] = {0};
  char haspoly[LIMIT] = {0};
  int seen[LIMIT] = {0};
  int ans = 0;
  for (int i = 1111; i < 10000; i++) {
    for (int h = 0; h < LIMIT; h++) {
      if (*(ispoly[h]+i) == 1) {
        memcpy(haspoly, zeroes, LIMIT); // sizeof(char) is always 1
        haspoly[h] = 1;
        seen[0] = i;
        if ((ans = find_cycle(ispoly, haspoly, seen, 1, i))) {
          printf("%d\n", ans);
          return 0;
        }
      }
    }
  }
  return 1;
}
