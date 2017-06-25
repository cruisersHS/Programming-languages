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
// �Q�_�Ԃ̋��������߂�
#define DISTANCE(x1,y1,x2,y2)	((double)( sqrt(pow(x1 - x2, 2) + pow(y1 -  y2, 2)) ))

double draw_speed = 6.0f; // �}�[�J�[�̈ړ����x
float cross_size = 8.0f; // �}�[�J�[�̑傫��
int draw_route[MaxNumber]; // �ړI�n�܂ł̓���
int draw_counter; // �O�Օ`��p�J�E���^
int draw_route_num; // �O�Օ`��p�ԍ�
int drawing_route_flag; // �O�Օ`�撆�t���O

 typedef struct
{
	int id;
	double x, y;
	char name[30];
	int points;
	int next[5];
} Crossing;

Crossing cross[MaxNumber];

//�n�}�f�[�^�̓ǂݍ���
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

// �z�� cross����name�Ƃ������O�̕t���������_��T����id��Ԃ�
//*****************************************
// (char* name)
//*****************************************
int name2id(char* name)
{
	int i;
	
	for (i = 0; i<MaxNumber; i++)	if (strcmp(cross[i].name, name) == 0)	return cross[i].id;
	return -1;
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
	glColor3d(0.0, 0.0, 1.0);	// ��
	glLineWidth(3);
	glBegin(GL_LINES);
	for (i = 0; i<MaxNumber; i++){
		for (j = 0; j<cross[i].points; j++){
			next = cross[i].next[j]-1;
			if (next < i) 	continue;	// ���ɕ`�悵�����H�̓X�L�b�v
			glVertex2d(cross[i].x, cross[i].y);
			glVertex2d(cross[next].x, cross[next].y);
		}
	}
	glEnd();

	// �����_�̕`��
	glColor3d(1.0, 0.0, 0.0);  // ��
	glBegin(GL_QUADS);
	for (i = 0; i<MaxNumber; i++){
		glVertex2d(cross[i].x, cross[i].y - cross_size);
		glVertex2d(cross[i].x - cross_size, cross[i].y);
		glVertex2d(cross[i].x, cross[i].y + cross_size);
		glVertex2d(cross[i].x + cross_size, cross[i].y);
	}
	glEnd();

	// �����_���̕\��
	glColor3d(0.0, 0.0, 0.0);  // ��
	for (i = 0; i<MaxNumber; i++){
		glRasterPos2f(cross[i].x - 30, cross[i].y + 12);
		for (j = 0; j < 30; j++){
			glutBitmapCharacter(GLUT_BITMAP_9_BY_15, cross[i].name[j]);
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
		glVertex2d(cross[n].x, cross[n].y);
		glVertex2d(cross[next].x, cross[next].y);
	}
	glEnd();

	// �n�}�`�� �}�[�J�[�Ƃ��̋O��
	if (draw_route[draw_route_num] != 0 && draw_route[draw_route_num + 1] != 0){
		// �ʉߍς݌����_�Ǝ��̌����_�A�Q�_�̍��W����}�[�J�[��\��������W���v�Z
		n = draw_route[draw_route_num]-1;
		next = draw_route[draw_route_num+1]-1;

		d = DISTANCE(cross[n].x, cross[n].y, cross[next].x, cross[next].y);
		xx = (double)cross[n].x + ((cross[next].x - cross[n].x) / d) * draw_speed * draw_counter;
		yy = (double)cross[n].y + ((cross[next].y - cross[n].y) / d) * draw_speed * draw_counter;

		// �}�[�J�[���W�́A���̌����_��ʂ�z���ĕ`�悵�Ă��Ȃ����`�F�b�N
		if (d <  DISTANCE(cross[n].x, cross[n].y, xx, yy)){
			// �ʂ�z���Ă���ꍇ�́A�����_�܂ŕ`��
			xx = cross[next].x;
			yy = cross[next].y;
			draw_counter = 0;
			draw_route_num++;
		}

		// �}�[�J�[�̋O�Ղ�`��
		glColor3d(0.0, 1.0, 0.0);  // ��
		glLineWidth(3);
		glBegin(GL_LINES);
		glVertex2d(cross[n].x, cross[n].y);
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

// �����_����ID���R���\�[�����͂��Ă��炤
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

	n = atoi(buf);	// ������̐�����int�^�ɕϊ�
	if (n != 0)	id = n;
	else	id = name2id(buf);	// ���͂������_���̏ꍇ�͌����_�ԍ��֕ϊ�
	return id;
}

// �R���\�[�����͗p�̊֐��A�X���b�h����Ăяo��
//*****************************************
// input_thread(LPVOID args)
//*****************************************
DWORD WINAPI input_thread(LPVOID args)
{
	int start, goal, i;

	while (1)
	{
		// �n�}�̃}�[�J�[�ړ����I���̂�҂�
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

		// ���[�g������ �������ɊF����̃A���S���Y�������ĉ������D
		draw_route[0] = 1;
		draw_route[1] = 2;
		draw_route[2] = 30;
		draw_route[3] = 32;
		draw_route[4] = 31;
		draw_route[5] = 29;          //***************************************************************************

		// �`��J�n
		route_draw_init();
		drawing_route_flag = 1;
	}
}

									//gcc -I/usr/include/opengl -o main.exe main.c -lglut32 -lglu32 -lopengl32 -lpthread


// main�֐�
//*****************************************
// main(int argc, char *argv[])
//*****************************************
int main(int argc, char *argv[])
{
	int i;

	HANDLE console_thread;

	// �����_�f�[�^�ǂݍ���
	read_data("map.dat");

	// �R���\�[�����͗p�̃X���b�h���쐬�Dinput_thread()�֐����Ăяo��
	CreateThread(NULL, 0, input_thread, NULL, 0, NULL);

	// glut �������E�`��J�n
	glutInitWindowSize(800, 800);	// �E�B���h�E�T�C�Y�̐ݒ�
	glutInit(&argc, argv);	// ������
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);	// �f�B�X�v���C���[�h��ݒ�
	glutCreateWindow("Car Navigation");		// �`��E�B���h�E����

	glClearColor(1.0, 1.0, 1.0, 1.0);	//��ʔw�i�ݒ�i���j
	glutDisplayFunc(glut_display);	// ��ʕ`��֐��o�^
	glutTimerFunc(100, glut_timer, 0);	// �^�C�}�[�֐��o�^ 100msec��Ɍďo��
	glutMainLoop();
	return 0;
}