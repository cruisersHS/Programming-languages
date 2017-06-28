#include<stdio.h>
#include<math.h>

#define TOTAL 35
#define INF 32767

typedef struct {                            //map
	int number;
	double pos[2];
	char name[30];
	int numofnearby;
	int nearby[7];
} Map_YZ;

typedef struct {                        //road???????????????????
	int number;
	int start;
	int end;
	int weight;
} road;

Map_YZ YZ[TOTAL];                           //MAP
road R[TOTAL];                           //ROAD

void read_data(char *filename) {            //read the map data
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

int dist_cal(int start, int end) {          //calculate the distance and turn into int(completed)
	double x1,x2,y1,y2;
	double distance;
	x1=YZ[start-1].pos[0];
	y1=YZ[start-1].pos[1];
	x2=YZ[end-1].pos[0];
	y2=YZ[end-1].pos[1];
	//double x1,double y1,double x2,double y2
	distance=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
	return (int)distance;
}

main() {
	int i,j,k;
	int start,end;
	int prev[TOTAL];                                 /////////////////////////////////
	int matrix[TOTAL][TOTAL];                         ////////////////////////////////
	int flag[TOTAL];                                      //judge if the point has been checked
	double distance[7];
	
	//list the points
	read_data("mape.dat");
	printf("NAMELIST:\n\n");
	for(i=0;i<TOTAL;i++) {
		printf("%d:%s",YZ[i].number,YZ[i].name);
		for(j=0;j<YZ[i].numofnearby;j++) {
			printf(", %d",YZ[i].nearby[j]);
		}
		printf("\n");
	}
	//initialize the matrix
	for(i=0;i<TOTAL;i++) {
		for(j=0;j<TOTAL;j++) {
			if(i==j) {
				matrix[i][j]=0;
			} else {
				matrix[i][j]=INF;
			}
		}
		flag[i]=0;
	}
	//input the start point
	printf("which point do you want to start? please input the number:\n");
	scanf("%d",&start);
	start-=1;                                //start has been -1
	flag[start]=1;
	prev[start]=0;
	
	//next:check every point nearby
}