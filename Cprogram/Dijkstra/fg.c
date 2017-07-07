//cygwin
//gcc -I/usr/include/opengl -o fg.exe fg.c -lglut32 -lglu32 -lopengl32 -lpthread
/*
*****************UPDTE LOG*********************** 

///ALPHA (Dijkstra Arithmetics)///
ver.0.3.Just try to change the cross address in the map(for searching). (completed)
ver.0.35. (completed)
	Code the part of BFS(Breadth First Search).
ver.0.4.Use BFS to visit every cross in the map(from the goalpoint). (completed)
ver.0.5.Update the distance from goal point to all the other crosses(distanceE[TOTAL]). (completed)
ver.0.55.Find the shortest distance to any point inputed by users. (completed)
ver.0.56.Code the part of tree waypoints(prev[TOTAL]). (completed)
ver.0.7.Show every waypoints from start point to goal point inputed by user. (completed)

///BETA (OpenGL Graphics)///
ver.0.71. show the window（completed）
ver.0.73. show the lines（completed）
ver.0.8. show the complete map with glut（completed）
ver.0.9.Run and draw the route in the graphics (completed)

///Debug///
ver.0.91.debug the problem that the former route cant be refreshed in the next time


ver.1.0目?：debug，成功?行程序
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <windows.h>
#include <GL/glut.h>

#define TOTAL 35    //Define the total number of the crosses
#define INF 32767   //Define a infinite number
#define DISTANCE(x1,y1,x2,y2)	((double)( sqrt(pow(x1 - x2, 2) + pow(y1 -  y2, 2)) ))  //Calculate the distance between two points

double draw_speed = 6.0f; // マーカーの移動速度
float cross_size = 8.0f; // マーカーの大きさ
int draw_route[TOTAL]; // 目的地までの道順
int draw_counter; // 軌跡描画用カウンタ
int draw_route_num; // 軌跡描画用番号
int drawing_route_flag; // 軌跡描画中フラグ

int matrix[TOTAL][TOTAL];               //Read the distance between two points (Adjacency matrix)
int visited[TOTAL];                     //Judge if the crosses has been visited
int distanceE[TOTAL];			//Record the shortest distance from endpoint to every point
int queue[TOTAL];            		//A queue for recording the search list
int prev[TOTAL];                        //Record the previous crosses in the waypoint
int start,end;                          //start point, end point

typedef struct {                  	
	char number[3];			//Cross number
	double pos[2];			//Cross position
	char name[30];			//Cross name
	int numofnearby;		//Number of nearby points
	int nearby[7];			//Every point address nearby
} Map_YZ;

Map_YZ YZ[TOTAL];                       //MAP

void read_data(char *filename) {        //read the map data
	FILE *fp=fopen(filename,"r");	//Read the file
	int i,j;
	if(fp==NULL) {
		printf("FAILED.\n");	//If the reading has failed, print"FAILED."
	} else {
		for(i=0;i<TOTAL;i++) {
			fscanf(fp,"%[^,], %lf, %lf, %[^,], %d",YZ[i].number,&YZ[i].pos[0],&YZ[i].pos[1],YZ[i].name,&YZ[i].numofnearby);
			for(j=0;j<YZ[i].numofnearby;j++) {
				fscanf(fp,", %d",&YZ[i].nearby[j]);
			}
		}
		printf("SUCCESSFUL.\n\n");
	}
	fclose(fp);
}

// 軌跡描画カウンタ初期化
//*****************************************
// route_draw_init()
//*****************************************
void route_draw_init()
{
	draw_counter = 0;
	draw_route_num = 0;
}

// 画面描画
//*****************************************
// glut_display(void)
//*****************************************
void glut_display(void)
{
	int i, j, n, next;
	int markerSize = 10;
	double d;
	double xx;
	double yy;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// 背景を白に描画
	glMatrixMode(GL_MODELVIEW);					// モデルビュー変換行列を設定
	glLoadIdentity();						// 行列を単位行列で初期化
	glOrtho(0, 1400, -1150, 250, -1.0, 1.0);			// 描画範囲を設定

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	// テクスチャの設定

	// 道路の描画
	glColor3d(0.1, 0.5, 0.8);					// 青
	glLineWidth(3);
	glBegin(GL_LINES);
	for (i = 0; i<TOTAL; i++){
		for (j = 0; j<YZ[i].numofnearby; j++){
			next = YZ[i].nearby[j]-1;
			if (next < i) 	continue;			// 既に描画した道路はスキップ
			glVertex2d(YZ[i].pos[0], YZ[i].pos[1]);	
			glVertex2d(YZ[next].pos[0], YZ[next].pos[1]);
		}
	}
	glEnd();
	
	// 交差点の描画
	glColor3d(1.0, 0.0, 0.3);  					// 赤
	glBegin(GL_QUADS);
	for (i = 0; i<TOTAL; i++){
		glVertex2d(YZ[i].pos[0], YZ[i].pos[1] - cross_size);
		glVertex2d(YZ[i].pos[0] - cross_size, YZ[i].pos[1]);
		glVertex2d(YZ[i].pos[0], YZ[i].pos[1] + cross_size);
		glVertex2d(YZ[i].pos[0] - cross_size, YZ[i].pos[1]);
	}
	glEnd();
	
	// 交差点名の表示
	glColor3d(1.0, 1.0, 1.0);  // white
	for(i=0;i<100;i++) {
		glRasterPos2f(50+10*i,50);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, i);
	}
	for (i = 0; i<TOTAL; i++){
		glRasterPos2f(YZ[i].pos[0] - 30, YZ[i].pos[1] + 12);
		for (j = 0; j < 30; j++){
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, YZ[i].name[j]);
		}
	}
	// 出発点から目的地までのルートを描画
	glColor3d(0.0, 1.0, 0.0); 					 // 緑
	glLineWidth(3);
	glBegin(GL_LINES);
	for (i=0;i<draw_route_num;i++){
		if (draw_route[i]==0 || draw_route[i + 1]==0)	break;
		n = draw_route[i]-1;
		next = draw_route[i+1]-1;
		glVertex2d(YZ[n].pos[0], YZ[n].pos[1]);
		glVertex2d(YZ[next].pos[0], YZ[next].pos[1]);
	}
	glEnd();
	
	// 地図描画 マーカーとその軌跡
	if (draw_route[draw_route_num] != 0 && draw_route[draw_route_num + 1] != 0){
		// 通過済み交差点と次の交差点、２点の座標からマーカーを表示する座標を計算
		n = draw_route[draw_route_num]-1;
		next = draw_route[draw_route_num+1]-1;

		d = DISTANCE(YZ[n].pos[0], YZ[n].pos[1], YZ[next].pos[0], YZ[next].pos[1]);
		xx = (double)YZ[n].pos[0] + ((YZ[next].pos[0] - YZ[n].pos[0]) / d) * draw_speed * draw_counter;
		yy = (double)YZ[n].pos[1] + ((YZ[next].pos[1] - YZ[next].pos[1]) / d) * draw_speed * draw_counter;

		// マーカー座標は、次の交差点を通り越して描画していないかチェック
		if (d <  DISTANCE(YZ[n].pos[0], YZ[n].pos[1], xx, yy)){
			// 通り越している場合は、交差点まで描画
			xx = YZ[next].pos[0];
			yy = YZ[next].pos[1];
			draw_counter = 0;
			draw_route_num++;
		}

		// マーカーの軌跡を描画
		glColor3d(0.0, 1.0, 0.0);  // 緑
		glLineWidth(3);
		glBegin(GL_LINES);
		glVertex2d(YZ[n].pos[0], YZ[n].pos[1]);
		glVertex2d(xx, yy);
		glEnd();

		// マーカーを描画
		glColor3d(0.0, 1.0, 0.0);  // 緑
		glBegin(GL_QUADS);					// マーカーのカタチはただの■
		glVertex2d(xx- markerSize, yy+ markerSize);
		glVertex2d(xx+ markerSize, yy+ markerSize);
		glVertex2d(xx+ markerSize, yy- markerSize);
		glVertex2d(xx- markerSize, yy- markerSize);
		glEnd();
	}
	else{
		// 全ての道程の描画終わったので目的地までのマーカーの描画は終了。
		// 目的地入力を有効にする
		drawing_route_flag = 0;
	}
	glutSwapBuffers();
}

// 画面描画更新タイマ
//*****************************************
// glut_timer(int value)
//*****************************************
void glut_timer(int value)
{
	glutPostRedisplay();			// 再描画
	draw_counter++;
	glutTimerFunc(40, glut_timer, 0);	// 自身の呼出し 40 msec後
}

//Calculate the distance between two points by inputing the address,to weight the shortest distance
//*****************************************
// dist_cal(int start, int end)
//*****************************************
int dist_cal(int start, int end) {          			//calculate the distance and turn into integer(completed)
	double x1,x2,y1,y2;
	double distance;
	x1=YZ[start-1].pos[0]; 	
	y1=YZ[start-1].pos[1];
	x2=YZ[end-1].pos[0];
	y2=YZ[end-1].pos[1];
	//double x1,double y1,double x2,double y2
	distance=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));		//distance=(δx^2+δy^2)^(1/2)
	return (int)distance;					//For easier comparation, the result has been truned into int
}

//Used in BFS, to check the first search point in a root point.(Input the root address, return the first nearby address.)
//*****************************************
// check_first (Map_YZ YZ[], int v)
//*****************************************
int check_first (Map_YZ YZ[], int v) {        	//Address minus 1(completed)
	if(v<0) {
		return (-1);
	}else {
		return (YZ[v].nearby[0]-1);	//The first point among the nearby addresses.
	}
}

//Used in BFS, to check the next search point in a root point. (Input the root address and the former address, return the next nearby address)
//*****************************************
// check_next (Map_YZ YZ[], int v, int w)
//*****************************************
int check_next (Map_YZ YZ[], int v, int w) {  		//Address minus 1 (completed)
	int i;
	for(i=0;i<YZ[v].numofnearby;i++) {
		if((YZ[v].nearby[i]-1)==w) {
			break;				//count i, which is the "i"th nearby address of v
		} else {
		}
	}
	if(v<0||w<0) {
		return -1;
	} else {
		if((i+1)<YZ[v].numofnearby) {
			return (YZ[v].nearby[i+1]-1);	
		} else {
			return -1;			//If i reached the last nearby point of v, end searching
		}
	}
}

//Breadth First Search function, start from the goal point, search all the point and build a data tree.
//*****************************************
// BFS(Map_YZ YZ[],int end)
//*****************************************
int BFS(Map_YZ YZ[],int end) {            		//The function of queue[i] is recording the search order.
	int head=0;					//head of the queue(queue out)
	int rear=1;					//rear of the queue(queue in)
	int i,j,k;
	for(i=0;i<TOTAL;i++) {
		visited[i]=0;				//Initialize the visit mark to 0.(0 means "not visited", 1 means "visited")
	}
	visited[end]=1;					//The first point has marked as "visited"
	j=end;
	queue[0]=end;
	while(head<=rear) {				//loop to record the queue list
		for(k=check_first(YZ,j);k>=0;k=check_next(YZ,j,k)) {
			if(visited[k]==0) {
				visited[k]=1;
				queue[rear++]=k;
			}
		}
		j=queue[head++];
	}
	return head;					//Return the times of searching(in case of overflow)
}

//
//*****************************************
// RECDIST(Map_YZ YZ[])
//*****************************************
void RECDIST(Map_YZ YZ[]) {
	int i,j;
	int mindist,tempdist,queuecount;
	//initialize the matrix 
	for(i=0;i<TOTAL;i++) {
		prev[i]=0;
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
	printf("which point do you want to start? please input the number:(If you want to quit,input 99)\n");
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
	
	queuecount=BFS(YZ,end);                         //存?了queue，???点 
	
	//running
	for(i=0;i<queuecount;i++) {           //?算了从?点到所有点的最短距? 
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
}

// コンソール入力用の関数、スレッドから呼び出し
//*****************************************
// input_thread(LPVOID args)
//*****************************************
DWORD WINAPI input_thread(LPVOID args) {
	int i,j;
	while(1){
		
		RECDIST(YZ);
		
		if ((!(start == 98) && !(start >= 0 && start <= TOTAL))){
			printf("I cannot find the point.\n\n");
			continue;
		}
		else if(start == 98) exit(0);
		i=start;
		printf("ROUTE:\n");
		printf("%d",start+1);
		draw_route[0]=i+1;
		j=1;
		while(1) {
			printf("---> %d",prev[i]+1);
			draw_route[j++]=prev[i]+1;
			if(prev[i]==end) break;
			i=prev[i];
		}
		printf("\n");
		// 描画開始
		route_draw_init();
		drawing_route_flag = 1;
	}
}

//gcc -I/usr/include/opengl -o fg.exe fg.c -lglut32 -lglu32 -lopengl32 -lpthread
int main(int argc, char *argv[]) {
	int i,j;
	//list the points
	read_data("mape.dat");
/*	printf("NAMELIST:\n\n");
	for(i=0;i<TOTAL;i++) {
		printf("%d:%s",YZ[i].number,YZ[i].name);
		for(j=0;j<YZ[i].numofnearby;j++) {
			printf(", %d",YZ[i].nearby[j]);
		}
		printf("\n");
	}*/
		
	HANDLE console_thread;
		
	// コンソール入力用のスレッドを作成．input_thread()関数を呼び出し
	CreateThread(NULL, 0, input_thread, NULL, 0, NULL);
		
	// glut 初期化・描画開始
	glutInitWindowSize(1200, 800);	// ウィンドウサイズの設定
	glutInit(&argc, argv);	// 初期化
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);	// ディスプレイモードを設定
	glutCreateWindow("Car Navigation");		// 描画ウィンドウ生成
	
	glClearColor(0.0, 0.2, 0.13, 1.0);	//画面背景設定（白）
	glutDisplayFunc(glut_display);	// 画面描画関数登録
	glutTimerFunc(100, glut_timer, 0);	// タイマー関数登録 100msec後に呼出し
	glutMainLoop();
	
	return 0;
}







