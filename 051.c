#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define FAMILY 8
#define MAX 1000000

int isprime[MAX];

struct primes {
  int list[MAX];
  int count;
} primes;

void gen_primes() {
  for (int i = 1; i < MAX; i++) {
    isprime[i] = 0;
  }
  isprime[2] = 1;
  primes.list[primes.count++] = 2;
  for (int i = 3; i < MAX; i++) {
    int s = sqrt(i);
    int flag = 0;
    for (int j = 0; j < primes.count && primes.list[j] <= s; j++) {
      if (!(i % primes.list[j])) {
        flag = 1;
        break;
      }
    }
    if (flag) {
      continue;
    }
    isprime[i] = 1;
    primes.list[primes.count++] = i;
  }
}

int count_prime_reps(char low[], char numstr[]) {
  int n = 0;
  int ret = 0;
  int flag = 0;
  char tmp[10];
  tmp[strlen(numstr)] = '\0';

  for (int i = 0; i < 10; i++) {
    if (i == 0 && numstr[0] == '*') {
      continue;
    }
    for (int c = 0; c < strlen(numstr); c++) {
      if (numstr[c] == '*') {
        tmp[c] = '0' + i;
      } else {
        tmp[c] = numstr[c];
      }
    }
    n = atoi(tmp);
    if (isprime[n]) {
      if (!flag) {
        strcpy(low, tmp);
        flag = 1;
      }
      ret++;
    }
  }
  return ret;
}

void dtomap(char map[], int dec) {
  int m = 0;
  while (dec > 0) {
    if (dec % 2) {
      map[m] = 1;
    } else {
      map[m] = 0;
    }
    m++;
    dec /= 2;
  }
}

int try_all_reps(char ret[], int num, int target) {
  char str[10], tmp[10];
  char map[10], low[10];
  int pri = 0;

  sprintf(str, "%d", num);
  int len = strlen(str);
  tmp[len] = '\0';
  for (int p = 1; p < (1 << (len - 1)); p++) {
    dtomap(map, p);
    for (int c = 0; c < len - 1; c++) {
      if (map[c] == 1) {
        tmp[c] = '*';
      } else {
        tmp[c] = str[c];
      }
    }
    tmp[len - 1] = str[len - 1];
    pri = count_prime_reps(low, tmp);
    if (pri >= target) {
      strcpy(ret, low);
      return 1;
    }
  }
  return 0;
}

int main(void) {
  char ret[10];
  gen_primes();
  for (int p = 0; p < primes.count; p++) {
    if (try_all_reps(ret, primes.list[p], FAMILY)) {
      printf("%s\n", ret);
      return 0;
    }
  }
  return 1;
}
