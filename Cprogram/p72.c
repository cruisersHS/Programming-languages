#include<stdio.h>
main() {
	char string[5];
	double dbl[5];
	int i;
	FILE *fp;
	fp=fopen("test01.txt","r");
	if(fp==NULL) {
		printf("failed.");
	} else {
		printf("successfull.\n");
		for(i=0;i<5;i++) {
			fscanf(fp,"%c \n %lf \n",&string[i],&dbl[i]);
			printf("%c \n %lf \n",string[i],dbl[i]);
		}
	}
	fclose(fp);
}