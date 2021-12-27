#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

char *names[6000];

static int cmpstringp(const void *p1, const void *p2) {
  return strcmp(*(const char **) p1, *(const char **) p2);
}

int main(void) {
  char * line = NULL;
  size_t len = 0;
  int n = 0;
  int score, s;
  long total = 0;

  while (getdelim(&line, &len, ',', stdin) != -1) {
    names[n] = (char *) malloc(strlen(line) + 1);
    strcpy(names[n], line);
    n++;
  }

  qsort(&names[0], n, sizeof(char *), cmpstringp);

  for (int i = 0; i < n; i++) {
    score = 0;
    for (int c = 0; names[i][c] != '\0'; c++) {
      s = names[i][c] - 'A' + 1;
      if (s > 0 && s <= 26) {
        score += s;
      }
    }
    total += score * (i + 1);
    free(names[i]);
  }
  free(line);
  printf("%ld\n", total);
}
