#include "bignum.h"


uint8_t bignum_print(struct Bignum *num)
{
  int i =0;

  if(num->sign == 1)
  {
    printf("*-"); 
  }

  for(i = 0; i < num->n; i++)
  {
   printf("%x", num->a[i]);  
  }
  printf("\n");
  return SUCCESS;

}

char tmpstr[MAXSIZE] = {'\0'}; /*TODO:don't use global*/
char tmpstr_check[MAXSIZE] = {'\0'}; /*TODO:don't use global*/

uint8_t convert_octal_str_little_endian_str(char *numstr, int size)
{
//  char tmpstr[MAXSIZE]= {'\0'};
  int i =0, j=0, k=0;
  char swp_tmp1, swp_tmp2, swp_tmp3;
  
  for(i=size; i>=0; i-=2)
  {
    swp_tmp1 = numstr[i];
    swp_tmp2 = numstr[i-1];
    for(; j<= size; j+2)
    {
      tmpstr[j] = swp_tmp2;
      tmpstr[j+1] =swp_tmp1;
      j +=2;
      break;
    }
  
  }

 if(size%2 ==0)
 {
  tmpstr[size] = numstr[0];
  tmpstr[size+1] = '\0';
 }
 //printf("%s \n" , tmpstr);
 return SUCCESS;
}

uint8_t convert_octal_str_bignum(struct Bignum *num, char *numstr, int size)
{
 int i =0, j=0, k=0, l =0, m = 0;
// printf("size[%d] jn[%d]\n",size, num->n);
 
 for(i=0,j=0; i<= size; i+=8,j++)
 {
 
//    printf("i [%d] \n",i);  
    for(l = (size - i),k =28, m=0; (l>= 0 && k >= 0 &&m <= 8); l--, k-=4,m++)
    {
      //printf("l [%d] \n",l);
      num->a[j] |= ((numstr[i+m] - '0') << k);
     // printf("a[j] [%u] \n",num->a[j]);
      if(size-i == 0)
       num->a[j+1] = '\0';
    }   

#if 0
    num->a[j] |= ((numstr[i+0] - '0') << 28);   /*as 4 bits a enough to carry a int value from 0-9*/                            
    num->a[j] |= ((numstr[i+1] -'0') << 24);		   			 /*preserve little-endian */
    num->a[j] |= ((numstr[i+2] - '0') << 20);
    num->a[j] |= ((numstr[i+3] - '0') << 16);
    num->a[j] |= ((numstr[i+4] - '0') << 12);
    num->a[j] |= ((numstr[i+5] - '0') << 8);
    num->a[j] |= ((numstr[i+6] - '0') << 4);
    num->a[j] |= ((numstr[i+7] - '0') << 0);
#endif    
   // printf("num[%u] [%u] i[%d]\n",j, num->a[j],i);
    
 }
 num->n = j; /*very important*/
 printf("n= [%d] \n",num->n);
  return SUCCESS;
}



uint8_t convert_bignum_octal_str(struct Bignum *num, char *numstr)
{
 int i =0, j =0 , k=0 , l=0, m=0; 
 int temp_hex=0;
 printf("n [%d] *4[%d]\n",num->n, num->n*4);
 memset(tmpstr, 0 , MAXSIZE);/*as global variables ar reused hence make contain previus value, so zeroing out*/
 for(i=0, j=0; (i< (num->n *4) && j< num->n); i+=8, j++) /* char = 1*4 bytes, as int is 4 bytes*/
 {
   for(k=28, l=0; (k>=0 && l<8) ; k-=4,l++)
   {
     temp_hex = ((num->a[j] & (0xF << k)) >> k);
     printf("temp_hex = [%x] \n",temp_hex);
     numstr[i+l] = temp_hex;
     printf("bn2str[%x] \n",numstr[i+l]);
   }   
 }
 
// printf("numstr[%x] \n",numstr); /*TODO: Need to fix extra zeroes while converting to str ha ha ha, why laugh ?*/
 return SUCCESS;
}





uint8_t bignum_input(struct Bignum *num, char *numstr, int size)
{
  int bignum_size = (size/4); /*considering int to be 4 bytes*/
  int i =0, j=0;
  int ret = 0;
  num->n = bignum_size;
  num->sign = 0; 
  num->a = malloc(sizeof(int) * num->n);/*TODO:make proper free*/ 
  memset(num->a, 0, num->n);
  printf("enter bignum: ");
  if(!fgets(numstr, size, stdin)) 
    return FAILURE;
  
  numstr[(strlen(numstr)-1)] = '\0';/*fgets last character new line*/
  printf("%s*** \n",numstr);
  //convert_octal_str_little_endian_str(numstr, (strlen(numstr)-1)); /*no need as we are not storing as integer does*/
  //printf("%s \n",tmpstr);
  convert_octal_str_bignum(num, numstr, (strlen(numstr)-1)); /*puting hex valuses in 2bytes , 1 int contains = 4*4->16 bytes*/
 // memset(tmpstr, 0 , MAXSIZE);/*as global variables ar reused hence make contain previus value, so zeroing out*/
 // convert_bignum_octal_str(num, tmpstr_check);
  return SUCCESS;
}
