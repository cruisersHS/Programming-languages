//cygwin
//gcc -I/usr/include/opengl -o main.exe main.c -lglut32 -lglu32 -lopengl32 -lpthread

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
#include <windows.h>
#include <GL/glut.h>

#define TOTAL 35
#define INF 32767
#define DISTANCE(x1,y1,x2,y2)	((double)( sqrt(pow(x1 - x2, 2) + pow(y1 -  y2, 2)) ))

/*
*****************UPDTE LOG*********************** 
ver.0.3.��s�ǋ�?�C??�����?�ʒu�i��j 
ver.0.35. (��)
	��?�Ȑ����?�ʒu�C?�ݔC?���������x?��r�� 
	�\?�r�����S��?
	�L��������I??�C�s��i�_��?�ړ_�I�ŒZ��?�C�����N�_��?�ړ_�I�ŒZ��?
	��?����??�H��I�imatrix[i][j]�\��i�_��j�_�I��?�j 
	���gvisited�h�A���\������?����?���_?�ߓI�ŒZ��?�H�j 
ver.0.4.�\?����r������?�_ �i��j 
ver.0.45.��o���N�_���e���_�I��?�i��j 
	��A��?��??queue�I?��A�ȍX�V���L�Idistance 
ver.0.5.��?�F�\?����?�����N�_�����L�_�I��?�i��j 
ver.0.55.��?�F�\??�Q?�_�I�ŒZ��?(��)
	?���p?��?? 
ver.0.56.��o�ȋ��o�C��?�_�ŒZ��?�I�����i��?�꘢�_���Œ�I�j  �i��j 
	�ڑO�z�@�F?�Z?�_���C�ӈ�_�I��?�C�R�@���N�_?�n???���_�C?�Q�ŒZ��?
	prev�I��?�� 
ver.0.7.��?�F�\??���ŒZ�H???�I�H�_   �i��j 
ver.0.71. show the window�i��j
ver.0.73. show the lines�i��j
ver.0.8. show the complete map with glut�i��j
ver.0.9��?�F�\?�^OpenGL?���C��graph��?�s�o�����H�a�i��j
ver.0.91.debug the problem that the former route cant be refreshed in the next time


ver.1.0��?�Fdebug�C����?�s����
*/

double draw_speed = 6.0f; // �}�[�J�[�̈ړ����x
float cross_size = 8.0f; // �}�[�J�[�̑傫��
int draw_route[TOTAL]; // �ړI�n�܂ł̓���
int draw_counter; // �O�Օ`��p�J�E���^
int draw_route_num; // �O�Օ`��p�ԍ�
int drawing_route_flag; // �O�Օ`�撆�t���O

int matrix[TOTAL][TOTAL];               //DISTANCE READLIST 
int visited[TOTAL];                     //FLAG
int distanceE[TOTAL];						//record the distance from endpoint to every point
int queue[TOTAL];             //MAP READLIST
int prev[TOTAL];                                 //�O�꘢�_�Idizhi(queue)
int start,end;                          //start point, end point

typedef struct {                            //map
	char number[3];
	double pos[2];
	char name[30];
	int numofnearby;
	int nearby[7];
} Map_YZ;

Map_YZ YZ[TOTAL];                           //MAP

void read_data(char *filename) {            //read the map data(completed)
	FILE *fp=fopen(filename,"r");
	int i,j;
	if(fp==NULL) {
		printf("FAILED.\n");
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

// �O�Օ`��J�E���^������
//*****************************************
// route_draw_init()
//*****************************************
void route_draw_init()
{
	draw_counter = 0;
	draw_route_num = 0;
}

// ��ʕ`��
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

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		// �w�i�𔒂ɕ`��
	glMatrixMode(GL_MODELVIEW);		// ���f���r���[�ϊ��s���ݒ�
	glLoadIdentity();	// �s���P�ʍs��ŏ�����
	glOrtho(0, 1400, -1150, 250, -1.0, 1.0);	// �`��͈͂�ݒ�

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);	// �e�N�X�`���̐ݒ�

	// ���H�̕`��
	glColor3d(0.1, 0.5, 0.8);	// ��
	glLineWidth(3);
	glBegin(GL_LINES);
	for (i = 0; i<TOTAL; i++){
		for (j = 0; j<YZ[i].numofnearby; j++){
			next = YZ[i].nearby[j]-1;
			if (next < i) 	continue;	// ���ɕ`�悵�����H�̓X�L�b�v
			glVertex2d(YZ[i].pos[0], YZ[i].pos[1]);
			glVertex2d(YZ[next].pos[0], YZ[next].pos[1]);
		}
	}
	glEnd();
	
	// �����_�̕`��
	glColor3d(1.0, 0.0, 0.3);  // ��
	glBegin(GL_QUADS);
	for (i = 0; i<TOTAL; i++){
		glVertex2d(YZ[i].pos[0], YZ[i].pos[1] - cross_size);
		glVertex2d(YZ[i].pos[0] - cross_size, YZ[i].pos[1]);
		glVertex2d(YZ[i].pos[0], YZ[i].pos[1] + cross_size);
		glVertex2d(YZ[i].pos[0] - cross_size, YZ[i].pos[1]);
	}
	glEnd();
	
	// �����_���̕\��
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
	// �o���_����ړI�n�܂ł̃��[�g��`��
	glColor3d(0.0, 1.0, 0.0);  // ��
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
	
	// �n�}�`�� �}�[�J�[�Ƃ��̋O��
	if (draw_route[draw_route_num] != 0 && draw_route[draw_route_num + 1] != 0){
		// �ʉߍς݌����_�Ǝ��̌����_�A�Q�_�̍��W����}�[�J�[��\��������W���v�Z
		n = draw_route[draw_route_num]-1;
		next = draw_route[draw_route_num+1]-1;

		d = DISTANCE(YZ[n].pos[0], YZ[n].pos[1], YZ[next].pos[0], YZ[next].pos[1]);
		xx = (double)YZ[n].pos[0] + ((YZ[next].pos[0] - YZ[n].pos[0]) / d) * draw_speed * draw_counter;
		yy = (double)YZ[n].pos[1] + ((YZ[next].pos[1] - YZ[next].pos[1]) / d) * draw_speed * draw_counter;

		// �}�[�J�[���W�́A���̌����_��ʂ�z���ĕ`�悵�Ă��Ȃ����`�F�b�N
		if (d <  DISTANCE(YZ[n].pos[0], YZ[n].pos[1], xx, yy)){
			// �ʂ�z���Ă���ꍇ�́A�����_�܂ŕ`��
			xx = YZ[next].pos[0];
			yy = YZ[next].pos[1];
			draw_counter = 0;
			draw_route_num++;
		}

		// �}�[�J�[�̋O�Ղ�`��
		glColor3d(0.0, 1.0, 0.0);  // ��
		glLineWidth(3);
		glBegin(GL_LINES);
		glVertex2d(YZ[n].pos[0], YZ[n].pos[1]);
		glVertex2d(xx, yy);
		glEnd();

		// �}�[�J�[��`��
		glColor3d(0.0, 1.0, 0.0);  // ��
		glBegin(GL_QUADS);					// �}�[�J�[�̃J�^�`�͂����́�
		glVertex2d(xx- markerSize, yy+ markerSize);
		glVertex2d(xx+ markerSize, yy+ markerSize);
		glVertex2d(xx+ markerSize, yy- markerSize);
		glVertex2d(xx- markerSize, yy- markerSize);
		glEnd();
	}
	else{
		// �S�Ă̓����̕`��I������̂ŖړI�n�܂ł̃}�[�J�[�̕`��͏I���B
		// �ړI�n���͂�L���ɂ���
		drawing_route_flag = 0;
	}
	glutSwapBuffers();
}

// ��ʕ`��X�V�^�C�}
//*****************************************
// glut_timer(int value)
//*****************************************
void glut_timer(int value)
{
	glutPostRedisplay();	// �ĕ`��
	draw_counter++;
	glutTimerFunc(40, glut_timer, 0);	// ���g�̌ďo�� 40 msec��
}

//*****************************************
// dist_cal(int start, int end)
//*****************************************
int dist_cal(int start, int end) {          //calculate the distance and turn into int(completed)
	double x1,x2,y1,y2;
	double distance;
	x1=YZ[start-1].pos[0];                 //���ӁC?������?��������I�_�I 
	y1=YZ[start-1].pos[1];
	x2=YZ[end-1].pos[0];
	y2=YZ[end-1].pos[1];
	//double x1,double y1,double x2,double y2
	distance=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
	return (int)distance;
}

//*****************************************
// check_first (Map_YZ YZ[], int v)
//*****************************************
int check_first (Map_YZ YZ[], int v) {        //�S�s?��(completed)
	if(v<0) {
		return (-1);
	}else {
		return (YZ[v].nearby[0]-1);
	}
}

//*****************************************
// check_next (Map_YZ YZ[], int v, int w)
//*****************************************
int check_next (Map_YZ YZ[], int v, int w) {  //?��  w���O�꘢�_�C�ԉ�?�����꘢?�ߓ_�I�n�� (completed)
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

//*****************************************
// BFS(Map_YZ YZ[],int end)
//*****************************************
int BFS(Map_YZ YZ[],int end) {            //��?��queue(Z)�C???�_�C�ԉ�queue��-1
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
	return head;
}

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
	
	queuecount=BFS(YZ,end);                         //��?��queue�C???�_ 
	
	//running
	for(i=0;i<queuecount;i++) {           //?�Z����?�_�����L�_�I�ŒZ��? 
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

// �R���\�[�����͗p�̊֐��A�X���b�h����Ăяo��
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
		// �`��J�n
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
		
	// �R���\�[�����͗p�̃X���b�h���쐬�Dinput_thread()�֐����Ăяo��
	CreateThread(NULL, 0, input_thread, NULL, 0, NULL);
		
	// glut �������E�`��J�n
	glutInitWindowSize(1200, 800);	// �E�B���h�E�T�C�Y�̐ݒ�
	glutInit(&argc, argv);	// ������
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);	// �f�B�X�v���C���[�h��ݒ�
	glutCreateWindow("Car Navigation");		// �`��E�B���h�E����
	
	glClearColor(0.0, 0.2, 0.13, 1.0);	//��ʔw�i�ݒ�i���j
	glutDisplayFunc(glut_display);	// ��ʕ`��֐��o�^
	glutTimerFunc(100, glut_timer, 0);	// �^�C�}�[�֐��o�^ 100msec��Ɍďo��
	glutMainLoop();
	
	return 0;
}







