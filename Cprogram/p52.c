//p52.c
#include<stdio.h>
main() {
	int i;
	double group[5]={4.5,4,5,6.7,6},avg=0,max;
	printf("Input 5 numbers:\n");
	for(i=0;i<5;i++) {
		printf("%3lf\t",group[i]);
		avg+=group[i];
		if(group[i]>max) max=group[i];
	}
	printf("\naverage=%3lf\nmax=%3lf",avg/5,max);
	
}