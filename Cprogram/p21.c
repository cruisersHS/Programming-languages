//p21.c
//二つ以上の数字をキーボードから読み込んで何か計算させ計算結果を表示するプログラムを書きなさい．
#include<stdio.h>
main() 
{
	double a,b;
	printf("input two numbers with a space between:\n");
	scanf("%lf %lf",&a,&b);
	printf("%lf * %lf = %lf\n",a,b,a*b);
}