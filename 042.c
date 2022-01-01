#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int get_wordvalue(char * word) {
  int val;
  int total = 0;
  for (; *word != '\0'; word++) {
    val = *word - 'A' + 1;
    if (val < 1 || val > 26) {
      continue;
    }
    total += val;
  }
  return total;
}

int is_triangle(int num) {
  int t = 0;
  int inc = 1;
  while (t < num) {
    t += inc++;
  }
  return num == t;
}

int main(void) {
  char * word = NULL;
  size_t len = 0;
  int ans = 0;
  int val;

  while (getdelim(&word, &len, ',', stdin) != -1) {
    val = get_wordvalue(word);
    if (is_triangle(val)) {
      ans++;
    }
  }
  free(word);
  printf("%d\n", ans);
}
