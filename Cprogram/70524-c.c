/*FILE *fopen(char *filename, char *mode)

int fclose(FILE *stream)
"r" ：読み出しモード．ファイルがなければエラーを返す．
"w" ：書き込みモード．ファイルがなければ新しく作る．同じファイル名があれば前のファイルは，消されます．
"a" ：追加モード．既にあるファイルの最後に続けて書き込めます．ファイルがなければ新しく作ります．
次に fclose() ですが，引数としてファイル型のアドレスを渡しています．
*/
//ex7.c
#include<stdio.h>

main(){
	char string[5]="abcde";
	double dbl[5]={1.2,3.4,5.6,7.8,9.1};
	int i;
	FILE *fps;
	
	fps=fopen("test01.txt","w");
	if(fps==NULL) {
		printf("failed.");
	} else {
		for(i=0;i<5;i++) fprintf(fps,"%c \n %lf \n ",string[i],dbl[i]);
		printf("successful.");
	}
	fclose(fps);
}

#include<stdio.h>
main() {
	char string[5];
	double dbl[5];
	int i;
	FILE *fp;
	fp=fopen("test01.txt","r");
	if(fp==NULL) {
		printf("failed.");
	} else {
		printf("successfull.\n");
		for(i=0;i<5;i++) {
			fscanf(fp,"%c \n %lf \n",&string[i],&dbl[i]);
			printf("%c \n %lf \n",string[i],dbl[i]);
		}
	}
	fclose(fp);
}

