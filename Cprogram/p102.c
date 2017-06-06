 /* p102.c */
 #include <stdio.h>
 
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

int main(void)
{
	int i;
	int maxi=0;
	double compare=0,sum=0;
	read_data("aleague.dat");             //Base on p101.c
	
	for(i=0;i<MaxNumber;i++)
		printf("���O�F%s, �N��F%d, �ŗ��F%lf \n", 
				AL[i].name, AL[i].age, AL[i].daritsu);
	for(i=0;i<MaxNumber;i++) {
		sum+=AL[i].daritsu;
		if (compare<AL[i].daritsu) {
				compare=AL[i].daritsu;
				maxi=i;
		}
	}
	printf("\nThe highest is %s!!\n",AL[maxi].name);
	printf("\nThe average daritsu is %lf\n",sum/MaxNumber);
}