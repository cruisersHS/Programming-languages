#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX 4
#define INF (~(0x1<<31))
/*
Ver.0.1
���л��� 
 


*/
typedef struct {     
	char name;
	int crosses[MAX];         //�������ţ����ǵ������� 
	int crossnum;
	int edgenum;
	int mat[MAX][MAX];       //�ڽӾ���,��ֱ�Ӱ�������λ����Ϣ�� 
}Graph, *PGraph ;

typedef struct _edge {        //�ߵ����� 
	int start;
	int end;                 //��һ          �ӵ����������ʱͳһ��һ 
	int weight;  
}Edge;

Graph* create_graph() {
	char vexs[]={'A','B','C','D'};
	int matrix[][9]={
		  /*A*/ /*B*/ /*C*/ /*D*/
	/*A*/{0,    3,    1,     INF},
	/*B*/{3,    0,  INF,     4  },
	/*C*/{1,  INF,    0,     2  },
	/*D*/{INF,  4,    2,     0  }
	};          //�����ڽӾ��� 
	

}             //λ�ø�ֵ 
    // 1. ��ʼ��"��"��Ȩֵ
/*    for (i = 0; i < pG->vexnum; i++)
    {
        for (j = 0; j < pG->vexnum; j++)
        {
            if (i==j)
                pG->matrix[i][j] = 0;
            else
                pG->matrix[i][j] = INF;
        }
    }     */

Edge E[4];               //����·��ֵ

/*void getG(void) {       //��ֵ������ 
	int i;
	G[0].name='A';
	G[1].name='B';
	G[2].name='C';
	G[3].name='D';
	G[0].crosses[0]=1;
	G[0].crosses[1]=2;
	G[1].crosses[0]=1;
	G[1].crosses[1]=4;
	G[2].crosses[0]=1;
	G[2].crosses[1]=4;
	G[3].crosses[0]=2;
	G[3].crosses[1]=3;           //��һ        �ӵ����������ʱͳһ��һ 
	G[0].mat[0][0]=2;//��һ���ص� 
	G[0].mat[0][1]=3;//��һ������ 
	G[0].mat[1][0]=3;
	G[0].mat[1][1]=1;
	G[1].mat[0][0]=1;
	G[1].mat[0][1]=3;
	G[1].mat[1][0]=4;
	G[1].mat[1][1]=4;
	G[2].mat[0][0]=1;
	G[2].mat[0][1]=1;
	G[2].mat[1][0]=4;
	G[2].mat[1][1]=2;
	G[3].mat[0][0]=2;
	G[3].mat[0][1]=4;
	G[3].mat[1][0]=3;
	G[3].mat[1][1]=2;    //�������ˣ��������� 
	for(i=0;i<4;i++) {
		G[i].edgenum=2;
		G[i].crossnum=2;       //������������ֱ��д��2�� 
	}                                                           
	E[0].start=1;
	E[0].end=3;
	E[0].weight=1;
	E[1].start=3;
	E[1].end=4;
	E[1].weight=2;
	E[2].start=1;
	E[2].end=2;	
	E[2].weight=3;
	E[3].start=2;
	E[3].end=4;
	E[3].weight=4;
}                                     */


main() {
	int flag[MAX];       //CT�ص㣬ָÿһ���ص��Ƿ��ȡ���·�� 
	int dist[MAX];       //��S���ϣ����ϴ���㵽���е����̾��� 
	int prev[MAX];
	int i,j,k;           //k
	int min;
	create_graph();
	for(i=0;i<MAX;i++) {         //�Ա�����ʼ�� 
		for(j=0;j<MAX;j++) {
			
		}
		flag[i]=0;
		dist[i]=G.mat[0][i];      //0����� 
		//dist[i]=E[i].weight;           
	}
	flag[0]=1;
	dist[0]=0;
	for(i=1;i<G[i].crossnum;i++) {    //ȷ����̵㣬Ҳ���ǵ�k���㣬�ǵ����������� 
		min=INF;
		for(j=0;j<G[i].crossnum;j++) {
			if(flag[j]==0&&G.mat[j][1]<min) {
				min=
				k=j;
			}
		}
		flag[k]=1;
		
	}
	printf("SAS");
}


















