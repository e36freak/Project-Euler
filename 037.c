#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct num {
  int num;
  struct num * next;
} num_t;

typedef struct {
  struct num * start;
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
  n->next = NULL;
}

int isprime(list_t * primes, int num) {
  int s;
  num_t * inc;
  num_t * new;

  if (num == 1) return 0;
  if (num == 2 || num == 3) {
    return 1;
  }

  inc = primes->start;
  s = (int)sqrt(num);
  while (inc != NULL && inc->num <= s) {
    if (!(num % inc->num)) {
      return 0;
    }
    inc = inc->next;
  }
  while (inc->next != NULL) {
    if (inc->num == num) {
      return 1;
    }
    inc = inc->next;
  }
  new = (num_t *)malloc(sizeof(num_t));
  new->num = num;
  inc->next = new;
  new->next = NULL;
  return 1;
}

int is_truncatable(list_t * primes, int num) {
  int tmp, dig, div, f;

  tmp = num;
  while (tmp > 0) {
    if (!isprime(primes, tmp)) {
      return 0;
    }
    tmp /= 10;
  }
  tmp = num;
  while (tmp > 0) {
    if (!isprime(primes, tmp)) {
      return 0;
    }
    dig = (int)log10(tmp);
    div = (int)pow(10, dig);
    f = tmp / div;
    tmp -= f * div;
  }

  return 1;
}

int main(void) {
  list_t primes;
  int found = 0;
  int ans = 0;

  init_primes(&primes);

  for (int i = 11; found < 11; i += 2) {
    if (is_truncatable(&primes, i)) {
      ans += i;
      found++;
    }
  }

  printf("%d\n", ans);

  clear_list(&primes);
}
