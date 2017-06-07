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
		printf("SUCCESSFUL.\n");
	}
	fclose(fp);
}


main() {
	int i,j;
	read_data("map.dat");
	for(i=0;i<TOTAL;i++) {
		printf("\n%d, %1lf, %1lf, %s, %d",YZ[i].number,YZ[i].pos[0],YZ[i].pos[1],YZ[i].name,YZ[i].numofnearby);
		for(j=0;j<YZ[i].numofnearby;j++) {
			printf(", %d",YZ[i].nearby[j]);
		}
		printf("\n");
	}
}