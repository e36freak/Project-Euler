#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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

int is_goldbach(list_t * primes, int num) {
  item_t * inc = primes->start;
  while (inc != NULL && inc->num < num) {
    int sum = 0;
    for (int i = 1; (sum = inc->num + 2 * (i * i)) < num; i++);
    if (sum == num) {
      return 1;
    }
    inc = inc->next;
  }
  return 0;
}

int test_num(list_t * primes, int num) {
  int s;
  item_t * inc;
  item_t * new;
  if (num == 1) return 0;
  if (num == 2 || num == 3) {
    return 0;
  }

  inc = primes->start;
  s = sqrt(num);
  while (inc != NULL && inc->num <= s) {
    if (!(num % inc->num)) {
      return !is_goldbach(primes, num);
    }
    inc = inc->next;
  }
  new = malloc(sizeof(*new));
  new->num = num;
  primes->end->next = new;
  primes->end = new;
  new->next = NULL;
  return 0;
}

int main(void) {
  list_t primes;
  init_primes(&primes);
  int ans = 0;
  for (ans = 3; !test_num(&primes, ans); ans += 2);
  printf("%d\n", ans);
  clear_list(&primes);
}
