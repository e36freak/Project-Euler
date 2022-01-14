#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "bignum.h"

int isprime(int num) {
  if (!(num % 2)) {
    return 0;
  }
  int s = sqrt(num);
  for (int i = 3; i <= s; i += 2) {
    if (!(num % i)) {
      return 0;
    }
  }
  return 1;
}
  
int main(void) {
  int side_length = 1;
  int primecount = 0;

  do {
    side_length += 2;
    for (int i = 3; i > 0; i--) {
      int num = (side_length)*(side_length) - (i * (side_length - 1));
      if (isprime(num)) {
        primecount++;
      }
    }
  } while (((double)primecount / (((side_length-1)*2)+1)) >= 0.1);

  printf("%d\n", side_length);
}
