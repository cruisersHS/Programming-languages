//p32.c
/*��L�̃v���O�������Q�l�ɂ��āC�A���t�@�x�b�ga�`d��ł����ނƓǂݕ��𓚂��Ă����v���O�����������Ȃ����D

�q���g�F�A���t�@�x�b�g�ł�����C�����^�̕ϐ����g���܂��Dex22.c ���Q�l�ɂ��ĉ������D*/
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