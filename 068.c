#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GON 5

typedef struct solution {
  int ring[GON][3];
  struct solution *prev;
} ring_t;

typedef struct {
  ring_t *end;
} stack_t;

const int max = GON * 2;

long ringtol(ring_t *sol) {
  int min = sol->ring[0][0];
  int minspoke = 0;
  long result = 0;
  int mult = 0;
  for (int spoke = 1; spoke < GON; spoke++) {
    if (sol->ring[spoke][0] < min) {
      min = sol->ring[spoke][0];
      minspoke = spoke;
    }
  }
  for (int spoke = GON + minspoke - 1; spoke >= minspoke; spoke--) {
    long tmp = 0;
    for (int node = 0; node < 3; node++) {
      tmp += sol->ring[spoke % GON][node] * (int)pow(10, (2-node));
    }
    result += tmp * (long)pow(10, mult);
    mult += (int)log10(tmp) + 1;
  }
  return result;
}

void push(stack_t *stack, int ring[][3]) {
  ring_t *sol = malloc(sizeof(ring_t));
  assert(sol != NULL);
  memcpy(sol->ring, ring, sizeof(int) * GON * 3);
  sol->prev = stack->end;
  stack->end = sol;
}

void populate(stack_t * sol, int ring[][3], int used[], int spoke, int node) {
  node = (node + 1) % 3;
  if (!node) {
    int target = 0, sum = 0;
    for (int i = 0; i < 3; i++) {
      target += ring[0][i];
      sum += ring[spoke][i];
    }
    if (sum != target) {
      return;
    }
    if (spoke == GON - 1) {
      push(sol, ring);
      return;
    }
    spoke++;
  }
  if (node == 1) {
    ring[spoke][node] = ring[spoke - 1][2];
    populate(sol, ring, used, spoke, node);
  } else if (spoke == GON - 1 && node == 2) {
    ring[spoke][node] = ring[0][1];
    populate(sol, ring, used, spoke, node);
  } else {
    for (int n = 0; n < max; n++) {
      if (used[n]) continue;
      ring[spoke][node] = n + 1;
      used[n] = 1;
      populate(sol, ring, used, spoke, node);
      used[n] = 0;
    }
  }
}

// start with max number (10 for 5-gon), work around n-gon recursively
int main(void) {
  int ring[GON][3] = {0};
  int used[max];
  stack_t solutions;
  solutions.end = NULL;

  for (int i = 0; i < max; i++) {
    used[i] = 0;
  }

  ring[0][0] = max;
  used[max-1] = 1;
  for (int n = 0; n < max - 1; n++) {
    used[n] = 1;
    ring[0][1] = n + 1;
    populate(&solutions, ring, used, 0, 1);
    used[n] = 0;
  }

  long ans = 0;
  ring_t *inc = solutions.end;
  ring_t *prev = NULL;
  while (inc != NULL) {
    long sorted = ringtol(inc);
//    printf("%ld\n", sorted);
    if (sorted > ans) {
      ans = sorted;
    }
    prev = inc;
    inc = inc->prev;
    free(prev);
  }
  printf("%ld\n", ans);
}
