//p54.c
#include<stdio.h>
main() {
	int a[3][3]={{1,2,3},{4,5,6},{7,8,9}};
	int b[3][3]={{3,4,5},{33,44,55},{6,66,7}};
	int c[3][3],i,j,k;
	for(i=0;i<3;i++) {
		for(j=0;j<3;j++) {
			c[i][j]=0;
		}
	}
	for(i=0;i<3;i++) {
		printf("|\t");
		for(j=0;j<3;j++) {
			for(k=0;k<3;k++) {
				c[i][j]+=a[i][k]*b[k][j];
			}
			printf("%4d\t",c[i][j]);
		}
		printf("|\n");
	}
	
}