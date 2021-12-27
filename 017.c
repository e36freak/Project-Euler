#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define COUNT 1000 

int letters[1000];

void letters_init() {
  letters[0] = 3; letters[1] = 3; letters[2] = 5;
  letters[3] = 4; letters[4] = 4; letters[5] = 3;
  letters[6] = 5; letters[7] = 5; letters[8] = 4;
  letters[9] = 3;

  letters[10] = 6; letters[11] = 6; letters[12] = 8;
  letters[13] = 8; letters[14] = 7; letters[15] = 7;
  letters[16] = 9; letters[17] = 8; letters[18] = 8;

  letters[19] = 6; letters[29] = 6; letters[39] = 5;
  letters[49] = 5; letters[59] = 5; letters[69] = 7;
  letters[79] = 6; letters[89] = 6; letters[99] = 7;

  letters[999] = 8;
}

int sum_letters(int num) {
  int tens, hundreds, thousands;
  int sum = 0;

  // how many thousands?
  if ((thousands = num / 1000) > 0) {
    sum += letters[thousands - 1] + letters[999];
  }
  num = num % 1000;
  // how many hundreds?
  if ((hundreds = num / 100) > 0) {
    sum += letters[hundreds - 1] + letters[99];
  }
  num = num % 100;

  if (hundreds && num) {
    sum += 3; // "and"
  }

  // 1-20
  if (num <= 20) {
    return sum + letters[num - 1];
  }

  if ((tens = num / 10) > 0) {
    sum += letters[tens*10 - 1];
  }
  num = num % 10;

  return sum + letters[num - 1];
}

int main(void) {
  int sum = 0;

  letters_init();

  for (int i = 1; i <= COUNT; i++) {
    sum += sum_letters(i);
  }
  printf("%d\n", sum);
  return 0;
}
