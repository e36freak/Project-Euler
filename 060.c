#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10000
#define LEN 5

typedef struct num {
  int num;
  struct num * next;
} num_t;

typedef struct {
  struct num * start;
  struct num * end;
} list_t;

void clear_list(list_t * list) {
  num_t * inc = list->start;
  num_t * prev = NULL;

  while (inc != NULL) {
    prev = inc;
    inc = inc->next;
    free(prev);
  }
}

void init_primes(list_t * primes) {
  num_t * n;
  num_t * p;
  int i;
  i = 2;
  n = (num_t *)malloc(sizeof(num_t));
  primes->start = n;
  n->num = i;
  p = n;
  for (i = 3; i < 8; i += 2) {
    n = (num_t *)malloc(sizeof(num_t));
    n->num = i;
    p->next = n;
    p = n;
  }
  primes->end = n;
  n->next = NULL;
}

void addprime(list_t * primes, int num) {
  int s;
  num_t * inc;
  num_t * new;

  inc = primes->start;
  s = (int)sqrt(num);
  while (inc != NULL && inc->num <= s) {
    if (!(num % inc->num)) {
      return;
    }
    inc = inc->next;
  }
  new = (num_t *)malloc(sizeof(num_t));
  new->num = num;
  primes->end->next = new;
  primes->end = new;
  new->next = NULL;
}

int isprime(list_t * primes, int num) {
  num_t * inc = primes->start;
  int s = sqrt(num);
  while (inc != NULL && inc->num <= s) {
    if (!(num % inc->num)) {
      return 0;
    }
    inc = inc->next;
  }
  return 1;
}

int concat_prime(list_t * primes, int a, int b) {
  if (!isprime(primes, a * (int)pow(10, (int)log10(b) + 1) + b)) {
    return 0;
  }
  return isprime(primes, b * (int)pow(10, (int)log10(a) + 1) + a);
}

int concat_with_all(list_t * primes, int cprimes[], int len, int num) {
  for (int i = 0; i < len; i++) {
    if (!concat_prime(primes, cprimes[i], num)) {
      return 0;
    }
  }
  return 1;
}

int find_concats(list_t * primes, int cprimes[], int len, num_t * start) {
  if (len == LEN) {
    int ans = 0;
    for (int i = 0; i < LEN; i++) {
      printf("%d ", cprimes[i]);
      ans += cprimes[i];
    }
    printf("\n");
    printf("%d\n", ans);
    return 1;
  }

  num_t * inc = start;
  int tmp[LEN] = {0};
  memcpy(tmp, cprimes, sizeof(int) * len);

  while (inc != NULL) {
    if (concat_with_all(primes, cprimes, len, inc->num)) {
      tmp[len] = inc->num;
      if (find_concats(primes, tmp, len + 1, inc)) {
        return 1;
      }
    }
    inc = inc->next;
  }
  return 0;
}


int main(void) {
  list_t primes;
  int cprimes[LEN] = {0};
  init_primes(&primes);
  for (int i = 11; i < MAX; i++) {
    addprime(&primes, i);
  }

  num_t * a = primes.start;
  while (a != NULL) {
    cprimes[0] = a->num;
    if (find_concats(&primes, cprimes, 1, primes.start)) {
      break;
    }
    a = a->next;
  }

  clear_list(&primes);
}
