//p91.c
#include<stdio.h>
#define MaxNumber 10    // �f�[�^�̌�

double data[MaxNumber][2];

void read_data(char *filename)
{
	FILE *fp;
	int i;
	
	fp = fopen(filename, "r");  // �t�@�C���̃I�[�v��
	if (fp == NULL){			
		printf("�t�@�C���쐬���s \n");
	}
	
	for(i=0;i<MaxNumber;i++){
		fscanf(fp, "%lf, %lf", &data[i][0], &data[i][1]);
	}
	
	fclose(fp);
}

int max(void)         //average
{
	int i,j=0;
	double m;
	
	m = 0;
	for(i=0;i<MaxNumber;i++){
		if(m<=data[i][1]) {
			m=data[i][1];
			j=i+1;
		}
	}
	
	return(j);
}

main() {
	int m,i;
	read_data("daritsu.dat");
	m=max();
	printf("The highest is No.%d competitor!",m);
}

/*���� ����܂ł̕��K

�P. �֐��̒��Ńt�@�C����ǂݍ���

 1: // ���91.c
 2: #include <stdio.h>
 3: 
 4: #define MaxNumber 10    // �f�[�^�̌� 
 5: 
 6: double data[MaxNumber][2];
 7: 
 8: void read_data(char *filename)
 9: {
10: 	FILE *fp;
11: 	int i;
12: 	
13: 	fp = fopen(filename, "r");  // �t�@�C���̃I�[�v�� 
14: 	if (fp == NULL){			
15: 		printf("�t�@�C���쐬���s \n");
16: 	}
17: 	
18: 	for(i=0;i<MaxNumber;i++){
19: 		fscanf(fp, "%lf, %lf", &data[i][0], &data[i][1]);
20: 	}
21: 	
22: 	fclose(fp);
23: }
24: 
25: double heikin(void)
26: {
27: 	int i;
28: 	double a;
29: 	
30: 	a = 0;
31: 	for(i=0;i<MaxNumber;i++){
32: 		a += data[i][1];
33: 	}
34: 	a /= MaxNumber;
35: 	
36: 	return(a);
37: }
38: 
39: int main(void)
40: {
41: 	int i;
42: 	double average;
43: 	
44: 	read_data("daritsu.dat");   // �����Ńt�@�C�������w�� 
45: 	average = heikin();
46: 	
47: 	for(i=0;i<MaxNumber;i++)
48: 		printf("%6.0lf: %6.3lf \n", data[i][0], data[i][1]);   �����̏������ɒ��� 
49: 	printf("\n �ŗ��̕��ς� %lf �ł��D\n", average);
50: }
�f�[�^�t�@�C���́C���� daritsu.dat

���K�X�|�P

��L�̃v���O�������Q�l�ɂ��āC�ŗ�����ԍ����l�̔ԍ����o�͂���v���O�����������Ȃ����D

���Ԃ��l�͈�ԍ����l�ł͂Ȃ��āC��ԍ����ŗ��̔ԍ��ł��邱�Ƃɒ��ӂ��邱�ƁD�l�͂������狁�߂邱�Ƃ��ł��܂��D*/