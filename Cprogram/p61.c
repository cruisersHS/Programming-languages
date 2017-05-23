//p61.c
#include<stdio.h>

double Avg(int length, int shulie[])
{
	int i=0;
	double sum=0;
	for(;i<length;i++) {
		sum+=shulie[i];
	}
	return(sum/length);
}

int Min(int length, int shulie[])
{
	int i=0;
	int min=10000;
	for(;i<length;i++) {
		if(min>shulie[i]) min=shulie[i];
	}
	return(min);
}

main() 
{
	int a[5]={5,3,7,8,45};
	double avg=Avg(5,a);
	int min=Min(5,a);
	printf("Average is %lf\nMinimum is %d",avg,min);
}
