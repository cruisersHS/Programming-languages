/*�ł����񂾐��������X�ɑ����Z����v���O�����������Ȃ����D0��ł����񂾂�I�����āC���ʂ�\�������܂��D

�q���g�F�@while ���Ɓ@break������� if �����g���Ď����ł��܂��D*/
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