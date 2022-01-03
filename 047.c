#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX 1000000
#define CONS 4

typedef struct item {
  int num;
  struct item * next;
} item_t;

typedef struct {
  struct item * start;
  struct item * end;
} list_t;

void clear_list(list_t * list) {
  item_t * inc = list->start;
  item_t * prev = NULL;

  while (inc != NULL) {
    prev = inc;
    inc = inc->next;
    free(prev);
  }
}

void init_primes(list_t * primes) {
  item_t * n;
  item_t * p;
  int i;
  i = 2;
  n = malloc(sizeof(*n));
  primes->start = n;
  n->num = i;
  p = n;
  for (i = 3; i < 8; i += 2) {
    n = malloc(sizeof(*n));
    n->num = i;
    p->next = n;
    p = n;
  }
  primes->end = n;
  n->next = NULL;
}

int genprime(list_t * primes, int num) {
  int s;
  item_t * inc;
  item_t * new;
  if (num == 1) return 1;
  if (num == 2 || num == 3) {
    return 1;
  }

  inc = primes->start;
  s = sqrt(num);
  while (inc != NULL && inc->num <= s) {
    if (!(num % inc->num)) {
      return 0;
    }
    inc = inc->next;
  }
  new = malloc(sizeof(*new));
  new->num = num;
  primes->end->next = new;
  primes->end = new;
  new->next = NULL;
  return 1;
}

int count_prime_factors(list_t * primes, int num) {
  int ret = 0;
  item_t * inc = primes->start;
  while (num > 1 && inc != NULL && inc->num <= num) {
    if (!(num % inc->num)) {
      ret++;
      do {
        num /= inc->num;
      } while (!(num % inc->num));
    }
    inc = inc->next;
  }
  return ret;
}

int main(void) {
  list_t primes;
  init_primes(&primes);
  for (int i = 5; i <= MAX; i += 2) {
    genprime(&primes, i);
  }

  int buf[CONS];
  int count = 0;
  for (int i = 1; i <= MAX; i++) {
    if (count_prime_factors(&primes, i) == CONS) {
      buf[count] = i;
      if (++count == CONS) {
        break;
      }
    } else {
      count = 0;
    }
  }
  printf("%d\n", buf[0]);

  clear_list(&primes);
}
