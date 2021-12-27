#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define SIZE 20

long cache[SIZE+1][SIZE+1];

long paths(int x, int y) {
  if (cache[x][y]) {
    return cache[x][y];
  }
  if (x == 0 || y == 0) {
    return 1;
  }
  cache[x-1][y] = paths(x - 1, y);
  cache[x][y-1] = paths(x, y - 1);
  return cache[x-1][y] + cache[x][y-1];
}

int main(void) {
  for (int s = 2; s <= SIZE; s++) {
    printf("%d %ld\n", s, paths(s, s));
  }
}
