#include <stdio.h>

#define SIZE 256

// TODO handle negative numbers

void bn_zero(char a[]);
void bn_itoa(char dest[], long long num);
void bn_copy(char dest[], const char src[]);
void bn_print(const char num[]);
void bn_add(char dest[], const char a[], const char b[]);
void bn_sub(char dest[], const char a[], const char b[]);
void bn_mult(char dest[], const char a[], const char b[]);
void bn_div(char dest[], const char a[], const char b[]);
int bn_com(const char a[], const char b[]);
