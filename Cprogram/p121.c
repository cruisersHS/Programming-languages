#include<stdio.h>
#include<math.h>
#define TOTAL 35


typedef struct {
	int number;
	double pos[2];
	char name[30];
	int numofnearby;
	int nearby[7];
} Map_YZ;

typedef struct {
	char w[30];
} tempw;

Map_YZ YZ[TOTAL];

tempw tpname[7];

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

double dist(double x1,double y1,double x2,double y2) {
	double distance;
	distance=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
	return distance;
}


main() {
	int i,j;
	int search,mark;
	double distance[7],temp,maxdist=0;
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
		distance[i]=dist(YZ[search-1].pos[0],YZ[search-1].pos[1],YZ[YZ[search-1].nearby[i]-1].pos[0],YZ[YZ[search-1].nearby[i]-1].pos[1]);
		printf("%s, %lf\n",YZ[YZ[search-1].nearby[i]-1].name,distance[i]);
	}
	for(i=0;i<YZ[search-1].numofnearby;i++) {
		for(j=YZ[search-1].numofnearby-1;j>=i;j--) {
			if(maxdist<distance[j]) {
				maxdist=distance[j];
				mark=j;
			}
//			printf("\ni=%d,j=%d,maxdist=%lf\n",i,j,maxdist);
		}
		maxdist=0;
		temp=distance[mark];
		distance[mark]=distance[i];
		distance[i]=temp;
//		tpname[i].w=&YZ[YZ[search-1].nearby[i]-1].name;
		//if no.i is bigger than
	}
	for(i=0;i<YZ[search-1].numofnearby;i++) {
		printf("%lf\n",distance[i]);
	}
}