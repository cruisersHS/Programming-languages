//max in 5
#include<stdio.h>
int main()
{
	int a,max,i;
	max=0;
	printf("input 5 numbers:\n");
	for(i=1;i<=5;i++)
	{
		printf("input a number:\n");
		scanf("%d",&a);
		if(a>max) max=a;
	}
	printf("the maxium number is %d\n",max);
}