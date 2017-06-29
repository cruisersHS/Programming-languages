#include<stdio.h>
#include<math.h>

#define TOTAL 35
#define INF 32767

/*
ver.0.3
先不管距离，试图正常切换位置（√） 
ver.0.35
已经可以正常切换位置，现在任务是完成广度优先搜索 
能够搜索完全部树吗？ 

有个理解上的错误，不是i点到邻接点的最短距离，而是起点到邻接点的最短距离
矩阵正是这么工作的（matrix[i][j]表示i点到j点的距离） 
而“visited”就是表示是否更新了distance（distance（start）从matrix中取值？） 

................. 
（v0.4目标：能够正常搜索到目标点）
（v0.5目标：能够完整显示从起点到所有点的距离）
（v0.6目标：能够寻找终点的最短距离）
（v0.7目标：能够显示最短路线经过的路点） 
我想着用queue来实现 
（v0.9目标：能够与glut程序结合，画出完整路径）
（v1.0目标：debug完成，完美运行程序） 
*/

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
	x1=YZ[start-1].pos[0];                 //注意，这个函数输入是加一的点！ 
	y1=YZ[start-1].pos[1];
	x2=YZ[end-1].pos[0];
	y2=YZ[end-1].pos[1];
	//double x1,double y1,double x2,double y2
	distance=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
	return (int)distance;
}

void BFS(Map_YZ YZ[]) {
	int head=0;
	int rear=0;
	int queue[TOTAL];                     //save the tree
	int visited[TOTAL];
	int i,j,k;
	for(i=0;i<TOTAL;i++) {
		visited[i]=0;
	}
	queue[head++]=-1;
	for(i=0;i<TOTAL;i++) {
		
	}
}

main() {
	int i,j,k,finalgoal;
	int start,end,step;                          //start point, end point, every step point
	int prev[TOTAL];                                 //是用来连接节点的！ tree的本体！ 
	int matrix[TOTAL][TOTAL];                         ////////////////////////////////
	int flag[TOTAL];                                      //judge if the point has been checked
	int distance[TOTAL];                        //record the distance from startpoint to every point
	int Qhead=0,Qrear=1;                          //Queue head & rear
	int visited[TOTAL];
	int mindist,tempdist;
	
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
	//input the start point
	printf("which point do you want to start? please input the number:\n");
	scanf("%d",&start);
	printf("and which point do you want to end? please input the number:\n");
	scanf("%d",&end);
	start-=1;                                //start has been -1
	end-=1;
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
		prev[i]=0;
		visited[i]=0;
	}
	//initialize the distance
	for(i=0;i<TOTAL;i++) {
		distance[i]=matrix[start][i];////////////////////////////////////
	}
	//initialize the start point
	flag[start]=1;
	prev[0]=-1;
	distance[start]=0;/////////////////////////////////////
	finalgoal=0;
	step=start;                            //step set to start first
	//build the tree
	visited[start]=1;
	for(i=1;i<TOTAL;i++) {
		for(j=0;j<YZ[step].numofnearby;j++) {
			if(visited[step]==0) {
				prev[Qrear++]=YZ[step].nearby[j]-1;
				visited[step]=1;
			}
		}
		step=
	}
}/*
	//next:check every point nearby
//	printf("START CHECKING...\n");
	for(i=1;i<TOTAL;i++) {
		mindist=INF;
		for(j=0;j<YZ[step].numofnearby;j++) {
			tempdist=dist_cal(step+1,YZ[step].nearby[j]);
			//add the distance to the matrix
			matrix[step][YZ[step].nearby[j]-1]=tempdist;/////////////////////////////////
			if((flag[YZ[step].nearby[j]-1]==0)&&(tempdist<mindist)) {           //check min
				mindist=tempdist;
				k=YZ[step].nearby[j]-1;
			}
		}                //这一步之后，理论上获取了最短距离点的地址k和距离mindist 
		flag[step]=1;     //step checked
		prev[i]=k;
		//update the distance from start point to the step nearby point(distance)
		for(j=0;j<YZ[step].numofnearby;j++) {
			
		}
		
		
		step=k;	
	}
	for(i=0;i<TOTAL;i++) {
		if(flag[i]==0) printf("boooooo\n");
	}
}
























