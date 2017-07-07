//p32.c
/*上記のプログラムを参考にして，アルファベットa～dを打ち込むと読み方を答えてくれるプログラムを書きなさい．

ヒント：アルファベットですから，文字型の変数を使います．ex22.c を参考にして下さい．*/
#include<stdio.h>
main() 
{
	char afb;
	printf("please input a letter (a,b,c,d):\n");
	scanf("%c",&afb);
	switch(afb) 
	{
		case 'a': printf("yes, this is a\n");
			break;
		case 'b': printf("ah, this is b!\n");
			break;
		case 'c': printf("well, this is c\n");
			break;
		case 'd': printf("ok, this could be d\n");
			break;
		default: printf("you didn`t input a-d, you inputed %c",afb);
	}
}