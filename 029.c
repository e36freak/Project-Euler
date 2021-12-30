#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define SIZE 256
#define MAX SIZE * 10

typedef struct num {
  int digits[SIZE];
  struct num * next;
} num_t;

typedef struct {
  struct num * start;
} bucket_t;

typedef struct {
  bucket_t * map[MAX];
} hash_t;

void print(int num[]) {
  int flag = 0;
  for (int i = SIZE - 1; i >= 0; i--) {
    if (num[i]) {
      flag = 1;
    }
    if (flag) {
      printf("%d", num[i]);
    }
  }
  printf("\n");
}

void arr_cpy(int t[], int a[]) {
  for (int i = 0; i < SIZE; i++) {
    t[i] = a[i];
  }
}

int compare(num_t * a, num_t * b) {
  for (int i = 0; i < SIZE; i++) {
    if (a->digits[i] < b->digits[i]) {
      return -1;
    } else if (a->digits[i] > b->digits[i]) {
      return 1;
    }
  }
  return 0;
}

void create_map(hash_t * list) {
  bucket_t * bucket;
  for (int i = 0; i < MAX; i++) {
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
  for (int i = 0; i < MAX; i++) {
    clear_bucket(list->map[i]);
  }
}

int calc_hash(num_t * num) {
  int ret = 0;
  for (int i = 0; i < SIZE; i++) {
    ret += num->digits[i];
  }
  return ret;
}

int add_num(hash_t * list, num_t * num) {
  num_t * inc = NULL;
  num_t * prev = NULL;
  int hash;

  hash = calc_hash(num);
  inc = list->map[hash]->start;

  num->next = NULL;
  if (inc == NULL) {
    list->map[hash]->start = num;
    return 1;
  }
  while (inc != NULL && (compare(num, inc) < 0)) {
    prev = inc;
    inc = inc->next;
  }
  if (inc == NULL) {
    prev->next = num;
    return 1;
  }
  if (compare(num, inc) == 0) {
    free(num);
    return 0;
  }
  if (prev == NULL) {
    list->map[hash]->start = num;
    num->next = inc;
    return 1;
  }
  num->next = inc;
  prev->next = num;
  return 1;
}

void mult(int a[], int b, int res[]) {
  int t, i, j, r;
  for (i = 0; i < SIZE; i++) {
    res[i] = 0;
  }
  for (i = 0; i < SIZE; i++) {
    t = a[i] * b;
    j = 0;
    while (t > 0) {
      res[i + j] += t % 10;
      if ((r = res[i + j]) >= 10) {
        res[i + j] = r % 10;
        res[i + j + 1] += r / 10;
      }
      t /= 10;
      j++;
    }
  }
}

int main(void) {
  num_t * tmp;
  hash_t powers;
  int ans = 0;
  int num[SIZE], t;

  create_map(&powers);

  for (int a = 2; a <= 100; a++) {
    t = a;
    for (int i = 0; i < SIZE; i++) {
      num[i] = t % 10;
      t /= 10;
    }
    for (int b = 2; b <= 100; b++) {
      tmp = (num_t *)malloc(sizeof(num_t));
      mult(num, a, tmp->digits);
      arr_cpy(num, tmp->digits);
      if (add_num(&powers, tmp)) {
        ans++;
      }
    }
  }
  printf("%d\n", ans);
  clear_map(&powers);
}
