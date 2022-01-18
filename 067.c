#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define SIZE 100

int main(void) {
  int triangle[SIZE][SIZE] = {0};
  int num;
  
  int row = 0, col = 0;
  while (scanf("%d", &num) == 1) {
    triangle[row][col] = num;
    if (col++ == row) {
      row++;
      col = 0;
    }
  }

  for (row = SIZE - 2; row >= 0; row--) {
    for (col = 0; col <= row; col++) {
      if (triangle[row + 1][col] > triangle[row + 1][col + 1]) {
        triangle[row][col] += triangle[row + 1][col];
      } else {
        triangle[row][col] += triangle[row + 1][col + 1];
      }
    }
  }

  printf("%d\n", triangle[0][0]);
}
