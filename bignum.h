/*Contains headers for bignums*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>

#define SUCCESS 1
#define FAILURE 0
#define MAXSIZE 1000


struct Bignum
{
  unsigned int *a;
  unsigned   int n;
  char sign;
};

uint8_t bignum_print(struct Bignum *num);
uint8_t bignum_input(struct Bignum *num, char *numstr, int size);
uint8_t convert_octal_str_little_endian_str(char *numstr, int size);
uint8_t convert_octal_str_bignum(struct Bignum *num, char *numstr, int size);
uint8_t convert_bignum_octal_str(struct Bignum *num, char *numstr);
uint8_t bignum_add(struct Bignum *num1, struct Bignum *num2, struct Bignum *res);

