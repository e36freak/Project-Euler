#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000000

void itos(int n, char * str) {
  while (n > 0) {
    *(str++) = '0' + (n % 10);
    n /= 10;
  }
  *str = '\0';
}

void itobs(int n, char * str) {
  while (n > 0) {
    *(str++) = '0' + (n % 2);
    n /= 2;
  }
  *str = '\0';
}

int is_palindrome(char str[]) {
  size_t len = strlen(str);
  for (int c = 0; c < len / 2; c++) {
    if (str[c] != str[len - c - 1]) {
      return 0;
    }
  }
  return 1;
}

int main(void) {
  char str[8];
  char bin[32];
  int ans = 0;

  for (int i = 1; i < MAX; i++) {
    itos(i, str);
    itobs(i, bin);
    if (is_palindrome(str) && is_palindrome(bin)) {
      ans += i;
    }
  }
  printf("%d\n", ans);
}
