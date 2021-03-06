#include <stdio.h>

#define SIZE 512

// TODO handle negative numbers

void bn_zero(char a[]);
void bn_itoa(char dest[], long long num);
void bn_copy(char dest[], const char src[]);
void bn_print(const char num[]);

void bn_add(char dest[], const char a[], const char b[]);
void bn_addint(char dest[], const char a[], int b);
void bn_sub(char dest[], const char a[], const char b[]);
void bn_subint(char dest[], const char a[], int b);
void bn_mult(char dest[], const char a[], const char b[]);
void bn_multint(char dest[], const char a[], int b);
void bn_div(char dest[], const char a[], const char b[]);

int bn_comp(const char a[], const char b[]);
int bn_length(const char a[]);
int bn_ispalindrome(const char a[]);
void bn_rev(char dest[], const char a[]);
int bn_sumdigits(const char a[]);

