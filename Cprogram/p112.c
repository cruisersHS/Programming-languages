#include<stdio.h>

#define TOTAL 35

typedef struct {
	int number;
	double pos[2];
	char name[30];
	int numofnearby;
	int nearby[7];
} Map_YZ;

Map_YZ YZ[TOTAL];

void read_data(char *filename) {
	FILE *fp=fopen(filename,"r");
	int i,j;
	if(fp==NULL) {
		printf("FAILED.\n");
	} else {
		for(i=0;i<TOTAL;i++) {
			fscanf(fp,"%d, %lf, %lf, %[^,], %d",&YZ[i].number,&YZ[i].pos[0],&YZ[i].pos[1],YZ[i].name,&YZ[i].numofnearby);
			for(j=0;j<YZ[i].numofnearby;j++) {
				fscanf(fp,", %d",&YZ[i].nearby[j]);
			}
		}
		printf("SUCCESSFUL.\n\n");
	}
	fclose(fp);
}


main() {
	int i,j,judge=0;
	int search;
	read_data("mape.dat");
	printf("NAMELIST:\n\n");
	for(i=0;i<TOTAL;i++) {
		printf("%d:%s",YZ[i].number,YZ[i].name);
		for(j=0;j<YZ[i].numofnearby;j++) {
			printf(", %d",YZ[i].nearby[j]);
		}
		printf("\n");
	}
	printf("\n\nWhich point do you want to search? Please input the number:\n");
	scanf("%d",&search);
	printf("\n\nThe place nearby %s is/are:\n",YZ[search-1].name);
	for(i=0;i<YZ[search-1].numofnearby;i++) {
		printf("%s, ",YZ[YZ[search-1].nearby[i]-1].name);
	}
//	for(i=0;i<TOTAL;i++) {
//				printf("\n\nThe place nearby %s is/are:\n",YZ[i].name);
//				for(j=0;j<YZ[i].numofnearby;j++) {
//					printf("%s, ",YZ[YZ[i].nearby[j]-1].name);
//				}
//				judge=1;
//	}
//	if(judge==0) printf("\n\ncant fine this place.\n");
}