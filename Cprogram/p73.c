#include<stdio.h>
main() {
	char inf[5][30]={{"1, Ichiro Suzuki, 0.348"},
		{"2, Ivan Rodriguez, 0.313"},
		{"3, Manny Ramirez, 0.335"},
		{"4, Bret Boone, 0.327"},
		{"5, Juan Gonzalez, 0.347"}};
	int i,j;
	FILE *fp;
	fp=fopen("p73.txt","w");
	if(fp==NULL) {
		printf("failed.");
	} else {
		printf("successfull.");
		for(i=0;i<5;i++) {
			for(j=0;j<30;j++){
				fprintf(fp,"%c",inf[i][j]);
				//if(inf[i][j]==`\0`) break;
			}
			fprintf(fp,"\n");
		}
	}
	fclose(fp);
}
