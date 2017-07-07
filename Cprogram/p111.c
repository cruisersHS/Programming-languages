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
	char search[30];
	read_data("mape.dat");
	printf("NAMELIST:\n\n");
	for(i=0;i<TOTAL;i++) {
		printf("%s",YZ[i].name);
		for(j=0;j<YZ[i].numofnearby;j++) {
			printf(", %d",YZ[i].nearby[j]);
		}
		printf("\n");
	}
	printf("\n\nWhich point do you want to search?:\n");
	scanf("%s",search);
	for(i=0;i<TOTAL;i++) {
			if(strcmp(YZ[i].name,search)==0) {
				printf("\n\nThe place nearby %s is/are:\n",YZ[i].name);
				for(j=0;j<YZ[i].numofnearby;j++) {
					printf("%s, ",YZ[YZ[i].nearby[j]-1].name);
				}
				judge=1;
			}
	}
	if(judge==0) printf("\n\ncant fine this place.\n");
}