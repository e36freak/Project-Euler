#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define SIZE 10000

typedef struct num {
  int index;
  int value;
  struct num * next;
} num_t;

typedef struct {
  struct num * start;
} bucket_t;

typedef struct {
  bucket_t * map[SIZE];
} hash_t;

void create_map(hash_t * list) {
  bucket_t * bucket;
  for (int i = 0; i < SIZE; i++) {
    bucket = (bucket_t *)malloc(sizeof(bucket_t));
    list->map[i] = bucket;
    bucket->start = NULL;
  }
}

void clear_bucket(bucket_t * bucket) {
  num_t * inc = bucket->start;
  num_t * prev = NULL;

  while (inc != NULL) {
    prev = inc;
    inc = inc->next;
    free(prev);
  }
  free(bucket);
}

void clear_map(hash_t * list) {
  for (int i = 0; i < SIZE; i++) {
    clear_bucket(list->map[i]);
  }
}

int compare(num_t * a, num_t * b) {
  if (a->index < b->index) {
    return -1;
  } else if (a->index > b->index) {
    return 1;
  }
  return 0;
}

int calc_hash(int num) {
  return num % SIZE;
}

void add_penta(hash_t * list, num_t * num) {
  num_t * inc = NULL;
  num_t * prev = NULL;
  int hash;

  hash = calc_hash(num->index);
  inc = list->map[hash]->start;
  num->next = NULL;
  if (inc == NULL) {
    list->map[hash]->start = num;
    return;
  }
  while (inc != NULL && (compare(num, inc) < 0)) {
    prev = inc;
    inc = inc->next;
  }
  if (inc == NULL) {
    prev->next = num;
    return;
  }
  if (compare(num, inc) == 0) {
    free(num);
    return;
  }
  if (prev == NULL) {
    list->map[hash]->start = num;
    num->next = inc;
    return;
  }
  num->next = inc;
  prev->next = num;
}

int get_value(hash_t * list, int index) {
  num_t * inc;
  int hash = calc_hash(index);

  inc = list->map[hash]->start;
  while (inc != NULL && index < inc->index) {
    inc = inc->next;
  }
  if (inc == NULL) {
    return 0;
  }
  if (index == inc->index) {
    return inc->value;
  }
  return 0;
}

int ispenta(int penta[], int num) {
  int i;
  for (i = 1; penta[i] < num; i++);
  return penta[i] == num;
}

int main(void) {
  int pnums[SIZE];
  hash_t penta;
  create_map(&penta);
  num_t * num;

  for (int n = 1; n < SIZE; n++) {
    int p = (n * ((3 * n) - 1)) / 2;
    pnums[n] = p;
    num = (num_t *)malloc(sizeof(num_t));
    num->index = p;
    num->value = 1;
    add_penta(&penta, num);
  }

  for (int n = 2; n < SIZE; n++) {
    int a = pnums[n];
    for (int i = n - 1; i > 0; i--) {
      int b = pnums[i];
      if (get_value(&penta, a - b) && get_value(&penta, b + a)) {
        printf("%d\n", a - b);
        return 0;
      }
    }
  }
  return 1;
}
