#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define MAX 4
#define INF (~(0x1<<31))
/*
Ver.0.1
运行环节 
 


*/
typedef struct {     
	char name;
	int crosses[MAX];         //交叉点序号，不是当地名称 
	int crossnum;
	int edgenum;
	int mat[MAX][MAX];       //邻接矩阵,是直接包含所有位置信息的 
}Graph, *PGraph ;

typedef struct _edge {        //边的数据 
	int start;
	int end;                 //减一          从地名序号引用时统一减一 
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
	};          //构建邻接矩阵 
	

}             //位置赋值 
    // 1. 初始化"边"的权值
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

Edge E[4];               //对线路赋值

/*void getG(void) {       //赋值函数√ 
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
	G[3].crosses[1]=3;           //减一        从地名序号引用时统一减一 
	G[0].mat[0][0]=2;//第一个地点 
	G[0].mat[0][1]=3;//第一个距离 
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
	G[3].mat[1][1]=2;    //累死我了！！！！！ 
	for(i=0;i<4;i++) {
		G[i].edgenum=2;
		G[i].crossnum=2;       //顶点数，这里直接写成2了 
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
	int flag[MAX];       //CT地点，指每一个地点是否获取最短路径 
	int dist[MAX];       //即S集合，整合从起点到所有点的最短距离 
	int prev[MAX];
	int i,j,k;           //k
	int min;
	create_graph();
	for(i=0;i<MAX;i++) {         //对变量初始化 
		for(j=0;j<MAX;j++) {
			
		}
		flag[i]=0;
		dist[i]=G.mat[0][i];      //0是起点 
		//dist[i]=E[i].weight;           
	}
	flag[0]=1;
	dist[0]=0;
	for(i=1;i<G[i].crossnum;i++) {    //确定最短点，也就是第k个点，是到顶点的最近点 
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


















