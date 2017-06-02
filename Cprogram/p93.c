//p92.c
#include<stdio.h>
#include<math.h>
#define MAX 12

double pos[MAX][3];

void scanner(char *filename) {
	FILE *fp;
	int i=0;
	fp=fopen(filename, "r");
	if (fp==NULL) {
		printf("LOAD FAILED.\n");
	} else {
		for(;i<MAX;i++) {
			fscanf(fp,"%lf,%lf,%lf",&pos[i][0],&pos[i][1],&pos[i][2]);
		}
	}
	fclose(fp);
}

void farest_pos(void) {
	double maxpos=0,dist;
	int i,j=0;
	double data1[MAX][2];
	FILE *fp=fopen("save.dat","w");
	for(i=0;i<MAX;i++) {
		dist=sqrt(pos[i][1]*pos[i][1]+pos[i][2]*pos[i][2]);
		data1[i][0]=i+1;
		data1[i][1]=dist;
		fprintf(fp,"%d, %lf\n",(int)data1[i][0],data1[i][1]);
		if(maxpos<=dist) {
			maxpos=dist;
			j=i;
		}
	}
	printf("The farest record is created by No.%d competitor!\nHis distance is %lf!\n",j,maxpos);
}

void save_data(char *filename) {
	FILE *fp;
	int i=0;
	fp=fopen(filename, "w");
}

main() {
	scanner("xy.dat");
	farest_pos();
}





/*1,3.2,4.0
2,6.3,2.1
3,8.3,1.2
4,0.9,2.3
5,10.3,3.2
6,2.6,5.6
7,1.9,2.3
8,8.5,9.3
9,4.9,12.6
10,2.5,6.4
11,3.4,19.0
12,2.9,5.1*/