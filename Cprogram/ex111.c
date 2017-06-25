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
		printf("ファイル作成失敗 \n");
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
	
	printf("選手の名前を入れて下さい．\n");
	scanf("%s", buf);
	
	for(i=0;i<MaxNumber;i++){
		if(strcmp(AL[i].name, buf)==0){
			printf("名前：%s, 年齢：%d, 打率：%lf \n", 
				AL[i].name, AL[i].age, AL[i].daritsu);
			f=1;
		}
	}
	
	if(f==0) printf("選手が見つかりません \n");
	
}

int main(void)
{
	read_data("aleague.dat");
	search();
}