//p74.c
#include<stdio.h>
main(){
	char player[5][30];
	int datas[5],i,j;
	double avg,sum;
	FILE *f;
	sum=0;
	f=fopen("p73.txt","r");
	for(i=0;i<5;i++) {
		fscanf(f,"%[^,], %lf \n",&player[i][0],datas[i]);
		printf("Player: %s \tDaritsu: %lf \n",&player[i][0],&datas[i]);
		sum+=datas[i];
	}
	avg=sum/5;
	printf("Average=%lf",avg);
	fclose(f);
}