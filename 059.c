#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "bignum.h"

void decrypt(char dest[], char src[], int len, char a, char b, char c) {
  for (int i = 0; i < len; i += 3) {
    dest[i] = src[i] ^ a;
    dest[i+1] = src[i+1] ^ b;
    dest[i+2] = src[i+2] ^ c;
  }
}

int add_ascii(char message[], int len) {
  int ret = 0;
  for (int i = 0; i < len; i++) {
    ret += message[i];
  }
  return ret;
}

void print(char message[], int len) {
  for (int i = 0; i < len; i++) {
    printf("%c", message[i]);
  }
  printf("\n");
}

int is_english(char message[], int len) {
  int freqs[128] = {0};
  int common[5];
  for (int i = 0; i < len; i++) {
    char c = message[i];
    if (c < ' ' || c == 127) {
      return 0;
    }
    freqs[(int)message[i]]++;
  }
  for (int i = 0; i < 5; i++) {
    char maxc = 0;
    for (int c = 0; c < 128; c++) {
      if (freqs[c] > freqs[(int)maxc]) {
        maxc = c;
      }
    }
    common[i] = maxc;
    freqs[(int)maxc] = 0;
  }

  if (common[0] == ' ' && common[1] == 'e' && common[2] == 't' && 
      (common[3] == 's' || common[3] == 'a' || common[3] == 'i')) {
    return 1;
  }
  return 0;
}

int main(void) {
  char * field = NULL;
  size_t len = 0;
  int mlen = 0;
  char message[2048];
  char decoded[2048] = {0};

  while (getdelim(&field, &len, ',', stdin) != -1) {
    message[mlen++] = atoi(field);
  }
  free(field);

  for (char a = 'a'; a <= 'z'; a++) {
    for (char b = 'a'; b <= 'z'; b++) {
      for (char c = 'a'; c <= 'z'; c++) {
        decrypt(decoded, message, mlen, a, b, c);
        if (is_english(decoded, mlen)) {
          is_english(decoded, mlen);
          print(decoded, mlen);
          printf("%d\n", add_ascii(decoded, mlen));
          return 0;
        }
      }
    }
  }
  return 1;
}
