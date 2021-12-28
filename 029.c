#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define SIZE 256

typedef struct num {
  int digits[SIZE];
  struct num * next;
} num_t;

typedef struct {
  struct num * start;
} list_t;

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

void create_list(list_t * list) {
  list->start = NULL;
}

void clear_list(list_t * list) {
  num_t * inc = list->start;
  num_t * prev = NULL;
  
  while (inc != NULL) {
    prev = inc;
    inc = inc->next;
    free(prev);
  }
}
  
int add_num(list_t * list, num_t * num) {
  num_t * inc = list->start;
  num_t * prev = NULL;

  num->next = NULL;
  if (inc == NULL) {
    list->start = num;
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
    list->start = num;
    num->next = inc;
    return 1;
  }
  num->next = inc;
  prev->next = num;
  return 1;
}

void power(int a, int b, int res[]) {
  int i, j, t, r;
  int tmp[SIZE];
  t = a;
  for (i = 0; i < SIZE; i++) {
    tmp[i] = t % 10;
    t /= 10;
  }
  for (int p = 1; p < b; p++) {
    for (i = 0; i < SIZE; i++) {
      res[i] = 0;
    }
    for (i = 0; i < SIZE; i++) {
      t = tmp[i] * a;
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
    arr_cpy(tmp, res);
  }
}

int main(void) {
  num_t * tmp;
  list_t powers;
  int ans = 0;

  create_list(&powers);

  for (int a = 2; a <= 100; a++) {
    for (int b = 2; b <= 100; b++) {
      tmp = (num_t *)malloc(sizeof(num_t));
      power(a, b, tmp->digits);
      if (add_num(&powers, tmp)) {
        ans++;
      }
    }
  }
  printf("%d\n", ans);
  clear_list(&powers);
}
