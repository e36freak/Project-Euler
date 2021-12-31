#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX 7654321

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

int isprime(list_t * primes, int num) {
  int s;
  num_t * inc;
  num_t * new;

  inc = primes->start;
  s = (int)sqrt(num);
  while (inc != NULL && inc->num <= s) {
    if (!(num % inc->num)) {
      return 0;
    }
    inc = inc->next;
  }
  new = (num_t *)malloc(sizeof(num_t));
  new->num = num;
  primes->end->next = new;
  primes->end = new;
  new->next = NULL;
  return 1;
}

int ispandigital(int num) {
  int len = (int)log10(num) + 1;
  int digits[len];
  int d;
  for (int i = 0; i < len; i++) {
    digits[i] = 0;
  }
  while (num > 0) {
    d = num % 10;
    if (!d || d > len || digits[d-1]++) {
      return 0;
    }
    num /= 10;
  }
  return 1;
}

int main(void) {
  list_t primes;
  int ans;

  init_primes(&primes);

  for (int n = 11; n <= MAX; n += 2) {
    if (isprime(&primes, n) && ispandigital(n)) {
      ans = n;
    }
  }
  printf("%d\n", ans);

  clear_list(&primes);
}
