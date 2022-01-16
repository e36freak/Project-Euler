#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define PERMUTATIONS 5

typedef struct num {
  long num;
  long perms[PERMUTATIONS];
  int plen;
  struct num * prev;
} num_t;

typedef struct {
  struct num * end;
} list_t;

void clear_list(list_t * list) {
  num_t * inc = list->end;
  num_t * prev = NULL;

  while (inc != NULL) {
    prev = inc;
    inc = inc->prev;
    free(prev);
  }
}

num_t * add_num(list_t * list, long n) {
  num_t * new = malloc(sizeof(num_t));
  new->num = n;
  new->plen = 1;
  new->perms[0] = n;
  new->prev = NULL;

  if (list->end == NULL) {
    list->end = new;
  } else {
    new->prev = list->end;
    list->end = new;
  }
  return new;
}

int ispermutation(long a, long b) {
  int digits[10] = {0};
  while (a > 0) {
    digits[a % 10]++;
    a /= 10;
  }
  while (b > 0) {
    if (--digits[b % 10] < 0) {
      return 0;
    }
    b /= 10;
  }
  for (int i = 0; i < 10; i++) {
    if (digits[i]) {
      return 0;
    }
  }
  return 1;
}

int main(void) {
  list_t cubes;
  num_t * cur;
  num_t * inc;
  long num = 300;
  long cube;
  
  cubes.end = NULL;
  while ((cube = num * num * num) <= LONG_MAX) {
    cur = add_num(&cubes, cube);
    inc = cur->prev;
    while (inc != NULL) {
      if (ispermutation(inc->num, cur->num)) {
        for (int i = 0; i < inc->plen; i++) {
          cur->perms[i + cur->plen] = inc->perms[i];
        }
        cur->plen += inc->plen;
        break;
      }
      inc = inc->prev;
    }
    if (cur->plen >= PERMUTATIONS) {
      for (int i = 0; i < cur->plen; i++) {
        printf("%ld ", cur->perms[i]);
      }
      printf("\n%ld\n", cur->perms[cur->plen-1]);
      clear_list(&cubes);
      return 0;
    }
    num++;
  }
  clear_list(&cubes);
  return 1;
}
