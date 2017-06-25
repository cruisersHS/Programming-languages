//cygwin
//gcc -I/usr/include/opengl -o main.exe main.c -lglut32 -lglu32 -lopengl32 -lpthread

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <windows.h>
#include <GL/glut.h>

#define MaxNumber 35
// ２点間の距離を求める
#define DISTANCE(x1,y1,x2,y2)	((double)( sqrt(pow(x1 - x2, 2) + pow(y1 -  y2, 2)) ))

double draw_speed = 6.0f; // マーカーの移動速度
float cross_size = 8.0f; // マーカーの大きさ
int draw_route[MaxNumber]; // 目的地までの道順
int draw_counter; // 軌跡描画用カウンタ
int draw_route_num; // 軌跡描画用番号
int drawing_route_flag; // 軌跡描画中フラグ

 typedef struct
{
	int id;
	double x, y;
	char name[30];
	int points;
	int next[5];
} Crossing;

Crossing cross[MaxNumber];

//地図データの読み込み
//*****************************************
// read_data(char *filename)
//*****************************************
void read_data(char *filename)
{
	FILE *fp;
	int i, j;

	fp = fopen(filename, "r");
	if (fp == NULL){
		printf("fail to create the file \n");
	}

	for (i = 0; i<MaxNumber; i++){
		fscanf(fp, "%d, %lf, %lf, %[^,], %d", &cross[i].id, &cross[i].x, &cross[i].y, cross[i].name, &cross[i].points);
		for (j = 0; j<cross[i].points; j++){
			fscanf(fp, ", %d", &cross[i].next[j]);
		}
	}
	
	fclose(fp);
}

// 配列 crossからnameという名前の付いた交差点を探してidを返す
//*****************************************
// (char* name)
//*****************************************
int name2id(char* name)
{
	int i;
	
	for (i = 0; i<MaxNumber; i++)	if (strcmp(cross[i].name, name) == 0)	return cross[i].id;
	return -1;
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
	glMatrixMode(GL_MODELVIEW);		// モデルビュー変換行列を設定
	glLoadIdentity();	// 行列を単位行列で初期化
	glOrtho(0, 1400, -1150, 250, -1.0, 1.0);	// 描画範囲を設定

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	// テクスチャの設定

	// 道路の描画
	glColor3d(0.0, 0.0, 1.0);	// 青
	glLineWidth(3);
	glBegin(GL_LINES);
	for (i = 0; i<MaxNumber; i++){
		for (j = 0; j<cross[i].points; j++){
			next = cross[i].next[j]-1;
			if (next < i) 	continue;	// 既に描画した道路はスキップ
			glVertex2d(cross[i].x, cross[i].y);
			glVertex2d(cross[next].x, cross[next].y);
		}
	}
	glEnd();

	// 交差点の描画
	glColor3d(1.0, 0.0, 0.0);  // 赤
	glBegin(GL_QUADS);
	for (i = 0; i<MaxNumber; i++){
		glVertex2d(cross[i].x, cross[i].y - cross_size);
		glVertex2d(cross[i].x - cross_size, cross[i].y);
		glVertex2d(cross[i].x, cross[i].y + cross_size);
		glVertex2d(cross[i].x + cross_size, cross[i].y);
	}
	glEnd();

	// 交差点名の表示
	glColor3d(0.0, 0.0, 0.0);  // 黒
	for (i = 0; i<MaxNumber; i++){
		glRasterPos2f(cross[i].x - 30, cross[i].y + 12);
		for (j = 0; j < 30; j++){
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, cross[i].name[j]);
		}
	}

	// 出発点から目的地までのルートを描画
	glColor3d(0.0, 1.0, 0.0);  // 緑
	glLineWidth(3);
	glBegin(GL_LINES);
	for (i=0;i<draw_route_num;i++){
		if (draw_route[i]==0 || draw_route[i + 1]==0)	break;
		n = draw_route[i]-1;
		next = draw_route[i+1]-1;
		glVertex2d(cross[n].x, cross[n].y);
		glVertex2d(cross[next].x, cross[next].y);
	}
	glEnd();

	// 地図描画 マーカーとその軌跡
	if (draw_route[draw_route_num] != 0 && draw_route[draw_route_num + 1] != 0){
		// 通過済み交差点と次の交差点、２点の座標からマーカーを表示する座標を計算
		n = draw_route[draw_route_num]-1;
		next = draw_route[draw_route_num+1]-1;

		d = DISTANCE(cross[n].x, cross[n].y, cross[next].x, cross[next].y);
		xx = (double)cross[n].x + ((cross[next].x - cross[n].x) / d) * draw_speed * draw_counter;
		yy = (double)cross[n].y + ((cross[next].y - cross[n].y) / d) * draw_speed * draw_counter;

		// マーカー座標は、次の交差点を通り越して描画していないかチェック
		if (d <  DISTANCE(cross[n].x, cross[n].y, xx, yy)){
			// 通り越している場合は、交差点まで描画
			xx = cross[next].x;
			yy = cross[next].y;
			draw_counter = 0;
			draw_route_num++;
		}

		// マーカーの軌跡を描画
		glColor3d(0.0, 1.0, 0.0);  // 緑
		glLineWidth(3);
		glBegin(GL_LINES);
		glVertex2d(cross[n].x, cross[n].y);
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
	glutPostRedisplay();	// 再描画
	draw_counter++;
	glutTimerFunc(40, glut_timer, 0);	// 自身の呼出し 40 msec後
}

// 交差点名かIDをコンソール入力してもらう
//*****************************************
// scan_id()
//*****************************************
int scan_id()
{
	int n, id, ret;
	char buf[10];

	ret = scanf("%s", buf);
	if (ret == EOF) {
		printf("scanf error\n");
		return -1;
	}

	n = atoi(buf);	// 文字列の数字をint型に変換
	if (n != 0)	id = n;
	else	id = name2id(buf);	// 入力が交差点名の場合は交差点番号へ変換
	return id;
}

// コンソール入力用の関数、スレッドから呼び出し
//*****************************************
// input_thread(LPVOID args)
//*****************************************
DWORD WINAPI input_thread(LPVOID args)
{
	int start, goal, i;

	while (1)
	{
		// 地図のマーカー移動が終わるのを待つ
		while (drawing_route_flag){};

		printf("\nPlease input the start point. For quit, input 99 \n\nStart Point>> ");
		start = scan_id();
		if (!(start == 99) && !(start >= 1 && start <= MaxNumber)){
			printf("I cannot find the point.\n\n");
			continue;
		}
		else if(start == 99) exit(0);

		printf("\nPlease input the goal point. \n\nGoal Point>> ");
		goal = scan_id();
		if (goal < 1 || goal > MaxNumber){
			printf("\nI cannot find the goal point. Restart again.\n");
			continue;
		}

		// ルートを決定 ※ここに皆さんのアルゴリズムを入れて下さい．
		draw_route[0] = 1;
		draw_route[1] = 2;
		draw_route[2] = 30;
		draw_route[3] = 32;
		draw_route[4] = 31;
		draw_route[5] = 29;          //***************************************************************************

		// 描画開始
		route_draw_init();
		drawing_route_flag = 1;
	}
}

									//gcc -I/usr/include/opengl -o main.exe main.c -lglut32 -lglu32 -lopengl32 -lpthread


// main関数
//*****************************************
// main(int argc, char *argv[])
//*****************************************
int main(int argc, char *argv[])
{
	int i;

	HANDLE console_thread;

	// 交差点データ読み込み
	read_data("map.dat");

	// コンソール入力用のスレッドを作成．input_thread()関数を呼び出し
	CreateThread(NULL, 0, input_thread, NULL, 0, NULL);

	// glut 初期化・描画開始
	glutInitWindowSize(800, 800);	// ウィンドウサイズの設定
	glutInit(&argc, argv);	// 初期化
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);	// ディスプレイモードを設定
	glutCreateWindow("Car Navigation");		// 描画ウィンドウ生成

	glClearColor(1.0, 1.0, 1.0, 1.0);	//画面背景設定（白）
	glutDisplayFunc(glut_display);	// 画面描画関数登録
	glutTimerFunc(100, glut_timer, 0);	// タイマー関数登録 100msec後に呼出し
	glutMainLoop();
	return 0;
}