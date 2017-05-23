//p53.c
#include<stdio.h>
main() {
	int a[3][3]={{1,2,3},{4,5,6},{7,8,9}};
	int b[3][3]={{3,4,5},{33,44,55},{6,66,7}};
	int i,j;
	for(i=0;i<3;i++) {
		printf("|\t");
		for(j=0;j<3;j++) {
			printf("%4d\t",a[i][j]+b[i][j]);
		}
		printf("|\n");
	}
	
}