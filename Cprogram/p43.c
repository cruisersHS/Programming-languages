/*打ち込んだ数字を次々に足し算するプログラムを書きなさい．0を打ち込んだら終了して，結果を表示させます．

ヒント：　while 文と　break文および if 文を使って実現できます．*/
#include<stdio.h>
main() 
{
	int sum,i,plus;
	sum=0; i=0;
	printf("Input a number, the sum will be added and printed, then the sum will be shown\nThis program will not end until you input 0\n");
	printf("Input a number: \n");
	while(1) 
	{
		scanf("%d",&plus);
		if(plus==0) 
		{
			break;
		}
		sum+=plus;
		printf("Sum=%d\nCount=%d\n",sum,++i);
	}
	printf("You inputed 0, you ended this program.\n");
}