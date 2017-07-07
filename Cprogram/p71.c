//ex7.c
#include<stdio.h>

main(){
	char string[5]="abcde";
	double dbl[5]={1.2,3.4,5.6,7.8,9.1};
	int i;
	FILE *fps;
	
	fps=fopen("test01.txt","w");
	if(fps==NULL) {
		printf("failed.");
	} else {
		for(i=0;i<5;i++) fprintf(fps,"%c \n %lf \n ",string[i],dbl[i]);
		printf("successful.");
	}
	fclose(fps);
}