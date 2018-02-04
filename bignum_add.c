#include "bignum.h"
#include<inttypes.h>

uint8_t bignum_add(struct Bignum *num1, struct Bignum *num2, struct Bignum *res)
{
 int res_size = 0;
 int carry = 0,i =0, j=0;
 uint64_t sum;

 if(num1->n > num2->n)
   res->n = num1->n;
 else if (num2->n > num1->n)
   res->n = num2->n;
 else
   res->n = num1->n;

 res->a = (int*) malloc(sizeof(int) * (res->n+1));/*TODO proper free*/
 memset(res->a, 0, (sizeof(int) * res->n));
 //printf("bbb\n");
 //bignum_print(res);
 //printf("yyyy \n");
// printf("n= [%d] \n",res->a);
   for(i = res->n-1; i >=0; i--)
   {
   // printf("1a[i][%x] || 2a[i] [%x] \n", num1->a[i], num2->a[i]);
    
    sum = num1->a[i] + carry;
    sum += num2->a[i];
   // printf("[%x] | [%x] \n",sum,sum>>32);
    res->a[i] = sum;
    carry = (sum >> 32);
    
   // printf("carry[%x] \n", carry);
   // printf("[%d]==[%x] \n",i,res->a[i]);
   }

  if(carry) /*need to reorder ;-(, all shift by 32, a[0]= carry*/
  {
   unsigned int temp;
   for(i = res->n -1; i>=0; i--)
    {
      res->a[i+1] = res->a[i];
      res->a[i] = 0; /*making sure zero*/
    }
   res->a[0]= carry;
   res->n += 1;


 //   printf("carry[%x] \n", carry);
 //   printf("[%d]==[%x] \n",i-1,res->a[i]);
  }

return SUCCESS;
}


