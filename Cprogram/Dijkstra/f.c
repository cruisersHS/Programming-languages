#include<stdio.h>
#include<math.h>

#define TOTAL 35
#define INF 32767

/*
ver.0.3
�Ȳ��ܾ��룬��ͼ�����л�λ�ã��̣� 
ver.0.35
�Ѿ����������л�λ�ã�������������ɹ���������� 
�ܹ�������ȫ������ 

�и�����ϵĴ��󣬲���i�㵽�ڽӵ����̾��룬������㵽�ڽӵ����̾���
����������ô�����ģ�matrix[i][j]��ʾi�㵽j��ľ��룩 
����visited�����Ǳ�ʾ�Ƿ������distance��distance��start����matrix��ȡֵ���� 

................. 
��v0.4Ŀ�꣺�ܹ�����������Ŀ��㣩
��v0.5Ŀ�꣺�ܹ�������ʾ����㵽���е�ľ��룩
��v0.6Ŀ�꣺�ܹ�Ѱ���յ����̾��룩
��v0.7Ŀ�꣺�ܹ���ʾ���·�߾�����·�㣩 
��������queue��ʵ�� 
��v0.9Ŀ�꣺�ܹ���glut�����ϣ���������·����
��v1.0Ŀ�꣺debug��ɣ��������г��� 
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
	x1=YZ[start-1].pos[0];                 //ע�⣬������������Ǽ�һ�ĵ㣡 
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
	int prev[TOTAL];                                 //���������ӽڵ�ģ� tree�ı��壡 
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
		}                //��һ��֮�������ϻ�ȡ����̾����ĵ�ַk�;���mindist 
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
























