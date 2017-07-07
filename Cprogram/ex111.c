#include <stdio.h>
#include <string.h>

#define MaxNumber 5

typedef struct{
	double	daritsu;
	char	name[30];
	int		age;
} Player;

Player AL[MaxNumber];

void read_data(char *filename)
{
	FILE *fp;
	int i;
	
	fp = fopen(filename, "r");
	if (fp == NULL){			
		printf("�t�@�C���쐬���s \n");
	}
	
	for(i=0;i<MaxNumber;i++){
		fscanf(fp, "%lf, %[^,], %d", &AL[i].daritsu, AL[i].name, &AL[i].age);
	}
	 
	fclose(fp);

}

void search(void)
{
	int i;
	int f=0;
	char buf[30];
	
	printf("�I��̖��O�����ĉ������D\n");
	scanf("%s", buf);
	
	for(i=0;i<MaxNumber;i++){
		if(strcmp(AL[i].name, buf)==0){
			printf("���O�F%s, �N��F%d, �ŗ��F%lf \n", 
				AL[i].name, AL[i].age, AL[i].daritsu);
			f=1;
		}
	}
	
	if(f==0) printf("�I�肪������܂��� \n");
	
}

int main(void)
{
	read_data("aleague.dat");
	search();
}