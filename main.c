#include"bignum.h"
extern char tmpstr_check;
int main( )
{
  struct Bignum num1, num2, result;
  char *num = NULL;
  num = malloc(sizeof(char) * MAXSIZE); /*TODO:make proper free*/
  memset(num, '\0', (sizeof(char) * MAXSIZE));

  printf("Input first bignum (with max %d digits)\n", MAXSIZE);
  bignum_input(&num1, num, MAXSIZE);
  bignum_print(&num1);

  memset(num, '\0', (sizeof(char) * MAXSIZE));
  printf("Input second bignum (with max %d digits)\n", MAXSIZE);
  bignum_input(&num2,num, MAXSIZE);
  bignum_print(&num2);
 // free(num); num = NULL;
 
  memset(num, '\0', (sizeof(char) * MAXSIZE));
  bignum_add(&num1, &num2, &result);
  bignum_print(&result);
 // convert_bignum_octal_str(&result, &tmpstr_check );
  //printf("res[%s] \n",tmpstr_check);
  
  
//  bignum_print(&num1);

  return 0;
}
