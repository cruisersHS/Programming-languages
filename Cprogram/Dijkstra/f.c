#include<stdio.h>
#include<math.h>

#define TOTAL 35
#define INF 32767

/*

*****************UPDTE LOG*********************** 

ver.0.3.�Ȳ��ܾ��룬��ͼ�����л�λ�ã��̣� 
ver.0.35. (��)
	�Ѿ����������л�λ�ã�������������ɹ���������� 
	�ܹ�������ȫ����
	�и�����ϵĴ��󣬲���i�㵽�ڽӵ����̾��룬������㵽�ڽӵ����̾���
	����������ô�����ģ�matrix[i][j]��ʾi�㵽j��ľ��룩 
	����visited�����Ǳ�ʾ�Ƿ�����������ڽ�����̾��룿�� 
ver.0.4.�ܹ�����������Ŀ��� ���̣� 
ver.0.45.��������㵽������ľ��루�̣� 
	Ҳ����ÿ�����queue��ʱ��Ϳ��Ը������е�distance 
ver.0.5.Ŀ�꣺�ܹ�������ʾ����㵽���е�ľ��루�̣� 
ver.0.55.Ŀ�꣺�ܹ�Ѱ���յ����̾���(��)
	�����ö�����ʵ�� 
ver.0.56.���������������������̾���ĺ�������ʵһ�����ǹ̶��ģ�  ���̣� 
	Ŀǰ�뷨�������յ㵽����һ��ľ��룬Ȼ�����㿪ʼ����ÿ���㣬Ѱ����̾���
	prev�ĺ����� 
ver.0.7Ŀ�꣺�ܹ���ʾ���·�߾�����·��   ���̣� 


ver.0.9Ŀ�꣺�ܹ���OpenGL��ϣ���graph�����г�����·��
��ver.1.0Ŀ�꣺debug���ɹ����г���*************************�� 
*/

typedef struct {                            //map
	int number;
	double pos[2];
	char name[30];
	int numofnearby;
	int nearby[7];
} Map_YZ;

Map_YZ YZ[TOTAL];                           //MAP
int matrix[TOTAL][TOTAL];               //DISTANCE READLIST 
int visited[TOTAL];                     //FLAG
int distanceE[TOTAL];						//record the distance from endpoint to every point
int queue[TOTAL];             //MAP READLIST

int min(int a, int b) {
	if(a>=b) {
		return(b);
	} else {
		return(a);
	}
}

void read_data(char *filename) {            //read the map data(completed)
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

int check_first (Map_YZ YZ[], int v) {        //ȫ����һ(completed)
	if(v<0) {
		return (-1);
	}else {
		return (YZ[v].nearby[0]-1);
	}
}

int check_next (Map_YZ YZ[], int v, int w) {  //��һ  w��ǰһ���㣬����ֵ����һ���ڽ���ĵ�ַ (completed)
	int i;
	for(i=0;i<YZ[v].numofnearby;i++) {
		if((YZ[v].nearby[i]-1)==w) {
			break;
		} else {
		}
	}
	if(v<0||w<0) {
		return -1;
	} else {
		if((i+1)<YZ[v].numofnearby) {
			return (YZ[v].nearby[i+1]-1);
		} else {
			return -1;
		}
	}
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

int BFS(Map_YZ YZ[],int end) {            //�洢��queue(Z)������ڵ㣬����queue��-1
	int head=0;
	int rear=1;
	int i,j,k;
	for(i=0;i<TOTAL;i++) {
		visited[i]=0;
	}
	visited[end]=1;
	j=end;
	queue[0]=end;
	while(head<=rear) {
		for(k=check_first(YZ,j);k>=0;k=check_next(YZ,j,k)) {
			if(visited[k]==0) {
				visited[k]=1;
				queue[rear++]=k;
			}
		}
		j=queue[head++];
	}
	for(i=0;i<TOTAL;i++) {
		printf("queue(%d)=%d\n",i+1,queue[i]+1);
	}
	return head;
}


void RECDIST(Map_YZ YZ[]) {
	int i,j;
	int start,end;                          //start point, end point, every step point
	int prev[TOTAL];                                 //ǰһ�����dizhi(queue)
	int mindist,tempdist,queuecount;
	int finalgoal=0;
	//initialize the matrix 
	for(i=0;i<TOTAL;i++) {
		for(j=0;j<TOTAL;j++) {
			if(i==j) {
				matrix[i][j]=0;
			} else {
				matrix[i][j]=INF;
			}
		}
		for(j=0;j<YZ[i].numofnearby;j++) {
			matrix[i][YZ[i].nearby[j]-1]=dist_cal(i+1,YZ[i].nearby[j]);
		}
	}
	//input the start point
	printf("which point do you want to start? please input the number:\n");
	scanf("%d",&start);
	printf("and which point do you want to end? please input the number:\n");
	scanf("%d",&end);
	start-=1;                                //start has been -1
	end-=1;
	//initialize the distance
	for(i=0;i<TOTAL;i++) {
		distanceE[i]=matrix[end][i];
	}
	//initialize the start&end point
	distanceE[end]=0;
	prev[end]=-1;
	
	queuecount=BFS(YZ,end);                         //�洢��queue������ڵ� 
	//running
	for(i=0;i<queuecount;i++) {           //�����˴��յ㵽���е����̾��� 
		for(j=0;j<YZ[queue[i]].numofnearby;j++) {
			tempdist=distanceE[queue[i]]+matrix[queue[i]][YZ[queue[i]].nearby[j]-1];
			if(tempdist<=distanceE[YZ[queue[i]].nearby[j]-1]) {
				distanceE[YZ[queue[i]].nearby[j]-1]=tempdist;
				prev[YZ[queue[i]].nearby[j]-1]=queue[i];
			}
			//distanceE[YZ[queue[i]].nearby[j]-1]=min(distanceE[YZ[queue[i]].nearby[j]-1],tempdist);
			//claculate the shortest distance and make sure the waypoint
		}
	}
	for(i=0;i<TOTAL;i++) {
		printf("prev(%d)=%d\n",i+1,prev[i]+1);
	}
	i=start;
	printf("ROUTE:\n");
	while(1) {
		printf("%d ---> ",prev[i]+1);
		if(prev[i]==end) break;
		i=prev[i];
	}
}

main() {
	int i,j;
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
	
	RECDIST(YZ);	
}
























