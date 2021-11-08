#include<stdio.h>
long int main()
{
  long int n;
  printf("Bir sayı giriniz: ");
  scanf("%ld",&n);
  
  for(long int i=2;i<=n;i++)
  {  
    while(n%i==0)
    {
      if(i!=n)
        printf("%ld x ",i);      
      else
        printf("%ld ",i);      
      n=n/i;
    }
  }
  
  printf("\n");
}
