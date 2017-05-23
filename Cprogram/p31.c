//p31.c
#include<stdio.h>
main() 
{
	int a;
	printf("input a number:\n");
	scanf("%d",&a);
	if(a>0) printf("the number %d is positive\n",a);
	else if (a==0) printf("you input 0\n");
	else printf("the number %d is negative\n",a);
}